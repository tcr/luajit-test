------------------------------------------------------------------------------
-- DynASM ARM module.
--
-- Copyright (C) 2005-2013 Mike Pall. All rights reserved.
-- See dynasm.lua for full copyright notice.
------------------------------------------------------------------------------

-- Module information:
local _info = {
  arch =  "thumb",
  description = "DynASM ARM Thumb2 module",
  version = "1.3.0",
  vernum =   10300,
  release = "2011-05-05",
  author =  "Mike Pall",
  license = "MIT",
}

-- Exported glue functions for the arch-specific module.
local _M = { _info = _info }

-- Cache library functions.
local type, tonumber, pairs, ipairs = type, tonumber, pairs, ipairs
local assert, setmetatable, rawget = assert, setmetatable, rawget
local _s = string
local sub, format, byte, char = _s.sub, _s.format, _s.byte, _s.char
local match, gmatch, gsub = _s.match, _s.gmatch, _s.gsub
local concat, sort, insert = table.concat, table.sort, table.insert
local bit = bit or require("bit")
local band, shl, shr, sar = bit.band, bit.lshift, bit.rshift, bit.arshift
local ror, tohex = bit.ror, bit.tohex

-- Inherited tables and callbacks.
local g_opt, g_arch
local wline, werror, wfatal, wwarn

-- Action name list.
-- CHECK: Keep this in sync with the C code!
local action_names = {
  "STOP", "SECTION", "ESC", "REL_EXT",
  "ALIGN", "REL_LG", "LABEL_LG",
  "REL_PC", "LABEL_PC", "IMM", "IMM12", "IMM16", "IMML8", "IMML12", "IMMV8",
}

-- Maximum number of section buffer positions for dasm_put().
-- CHECK: Keep this in sync with the C code!
local maxsecpos = 25 -- Keep this low, to avoid excessively long C lines.

-- Action name -> action number.
local map_action = {}
for n,name in ipairs(action_names) do
  map_action[name] = ((n-1) * 0x1000)
end

-- Action list buffer.
local actlist = {}

-- Argument list for next dasm_put(). Start with offset 0 into action list.
local actargs = { 0 }

-- Current number of section buffer positions for dasm_put().
local secpos = 1

------------------------------------------------------------------------------

-- Dump action names and numbers.
local function dumpactions(out)
  out:write("DynASM encoding engine action codes:\n")
  for n,name in ipairs(action_names) do
    local num = map_action[name]
    out:write(format("  %-10s %02X  %d\n", name, num, num))
  end
  out:write("\n")
end

-- Write action list buffer as a huge static C array.
local function writeactions(out, name)
  local nn = #actlist
  if nn == 0 then nn = 1; actlist[0] = map_action.STOP end
  out:write("static const uint16_t ", name, "[", nn, "] = {\n")
  for i = 1,nn-1 do
    assert(out:write("0x", tohex(actlist[i], 4), ",\n"))
  end
  -- assert(out:write("0x", tohex(actlist[nn], 4), "\n};\n\n"))
  assert(out:write("0x", tohex(map_action.STOP, 4), "\n};\n\n"))
end

------------------------------------------------------------------------------

-- Add word to action list.
local function wputxw(n)
  assert(n >= 0 and n <= 0xffffffff and n % 1 == 0, "word out of range")
  -- TCR_LOG('WROTE ACTION', n)
  actlist[#actlist+1] = n
end

-- Add action to list with optional arg. Advance buffer pos, too.
local function waction(action, val, a, num)
  -- TCR_LOG('action->', action);
  local w = assert(map_action[action], "bad action name `"..action.."'")
  wputxw(0xffff)
  wputxw(w + (val or 0))
  if a then actargs[#actargs+1] = a end
  if a or num then secpos = secpos + (num or 1) end
end

-- Flush action list (intervening C code or buffer pos overflow).
local function wflush(term)
  if #actlist == actargs[1] then return end -- Nothing to flush.
  if not term then waction("STOP") end -- Terminate action list.
  wline(format("dasm_put(Dst, %s);", concat(actargs, ", ")), true)
  actargs = { #actlist } -- Actionlist offset is 1st arg to next dasm_put().
  secpos = 1 -- The actionlist offset occupies a buffer position, too.
end

-- Put escaped word.
local function wputw(n)
  if n <= 0x000fffff then waction("ESC") end
  wputxw(n)
end

-- Reserve position for word.
local function wpos()
  local pos = #actlist+1
  -- TCR_LOG('WROTE ACTION', "''")
  actlist[pos] = ""
  return pos
end

-- Store word to reserved position.
local function wputpos(pos, n)
  assert(n >= 0 and n <= 0xffffffff and n % 1 == 0, "word out of range")
  -- TCR_LOG('WROTE reserved ACTION', n)
  actlist[pos] = band(n, 0xffff)
  -- n = map_action.ESC * 0x10000
end

------------------------------------------------------------------------------

-- Global label name -> global label number. With auto assignment on 1st use.
local next_global = 20
local map_global = setmetatable({}, { __index = function(t, name)
  if not match(name, "^[%a_][%w_]*$") then werror("bad global label") end
  local n = next_global
  if n > 2047 then werror("too many global labels") end
  next_global = n + 1
  t[name] = n
  return n
end})

-- Dump global labels.
local function dumpglobals(out, lvl)
  local t = {}
  for name, n in pairs(map_global) do t[n] = name end
  out:write("Global labels:\n")
  for i=20,next_global-1 do
    out:write(format("  %s\n", t[i]))
  end
  out:write("\n")
end

-- Write global label enum.
local function writeglobals(out, prefix)
  local t = {}
  for name, n in pairs(map_global) do t[n] = name end
  out:write("enum {\n")
  for i=20,next_global-1 do
    out:write("  ", prefix, t[i], ",\n")
  end
  out:write("  ", prefix, "_MAX\n};\n")
end

-- Write global label names.
local function writeglobalnames(out, name)
  local t = {}
  for name, n in pairs(map_global) do t[n] = name end
  out:write("static const char *const ", name, "[] = {\n")
  for i=20,next_global-1 do
    out:write("  \"", t[i], "\",\n")
  end
  out:write("  (const char *)0\n};\n")
end

------------------------------------------------------------------------------

-- Extern label name -> extern label number. With auto assignment on 1st use.
local next_extern = 0
local map_extern_ = {}
local map_extern = setmetatable({}, { __index = function(t, name)
  -- No restrictions on the name for now.
  local n = next_extern
  if n > 2047 then werror("too many extern labels") end
  next_extern = n + 1
  t[name] = n
  map_extern_[n] = name
  return n
end})

-- Dump extern labels.
local function dumpexterns(out, lvl)
  out:write("Extern labels:\n")
  for i=0,next_extern-1 do
    out:write(format("  %s\n", map_extern_[i]))
  end
  out:write("\n")
end

-- Write extern label names.
local function writeexternnames(out, name)
  out:write("static const char *const ", name, "[] = {\n")
  for i=0,next_extern-1 do
    out:write("  \"", map_extern_[i], "\",\n")
  end
  out:write("  (const char *)0\n};\n")
end

------------------------------------------------------------------------------

-- Arch-specific maps.

-- Ext. register name -> int. name.
local map_archdef = { sp = "r13", lr = "r14", pc = "r15", }

-- Int. register name -> ext. name.
local map_reg_rev = { r13 = "sp", r14 = "lr", r15 = "pc", }

local map_type = {}   -- Type name -> { ctype, reg }
local ctypenum = 0    -- Type number (for Dt... macros).

-- Reverse defines for registers.
function _M.revdef(s)
  return map_reg_rev[s] or s
end

local map_shift = { lsl = 0, lsr = 1, asr = 2, ror = 3, }

local map_cond = {
  eq = 0, ne = 1, cs = 2, cc = 3, mi = 4, pl = 5, vs = 6, vc = 7,
  hi = 8, ls = 9, ge = 10, lt = 11, gt = 12, le = 13, al = 14,
  hs = 2, lo = 3,
}

------------------------------------------------------------------------------

-- Template strings for ARM instructions.
local map_op = {
  ["adc.w_3"] = {
    {"sdni", "11110H01010snnnn", "0HHHddddHHHHHHHH"},
    {"sdnmT", "11101011010snnnn", "0iiiddddiiTTmmmm"}
  },
  ["adc.w_4"] = {
    {"sdnmT", "11101011010snnnn", "0iiiddddiiTTmmmm"}
  },
  ["adc_2"] = {
    {"sdm", "0100000101mmmddd"}
  },
  ["add_3"] = {
    {"sdni", "0001110iiinnnddd"},
    {"sdnm", "0001100mmmnnnddd"},
    {"sdpi", "10101dddiiiiiiii"}
  },
  ["add_2"] = {
    {"sdi", "00110dddiiiiiiii"},
    {"sdm", "01000100dmmmmddd"},
    {"spi", "101100000iiiiiii"}
  },
  ["add.w_3"] = {
    {"sdni", "11110H01000snnnn", "0HHHddddHHHHHHHH"},
    {"sdnmT", "11101011000snnnn", "0iiiddddiiTTmmmm"},
  },
  ["add.w_4"] = {
    {"sdnmT", "11101011000snnnn", "0iiiddddiiTTmmmm"}
  },
  ["addw_3"] = {
    {"dni", "11110H100000nnnn", "0HHHddddHHHHHHHH"}
  },
  ["adr_2"] = {
    {"dB", "10100dddiiiiiiii"}
  },
  ["adr.w_2"] = {
    {"dB", "11110H1010101111", "0HHHddddHHHHHHHH"},
    {"dB", "11110H1000001111", "0HHHddddHHHHHHHH"}
  },
  ["and.w_3"] = {
    {"sdni", "11110H00000snnnn", "0HHHddddHHHHHHHH"},
    {"sdnmT", "11101010000snnnn", "0iiiddddiiTTmmmm"}
  },
  ["and.w_4"] = {
    {"sdnmT", "11101010000snnnn", "0iiiddddiiTTmmmm"}
  },
  ["and_2"] = {
    {"sdm", "0100000000mmmddd"}
  },
  ["asr_3"] = {
    {"sdmi", "00010iiiiimmmddd"}
  },
  ["asr.w_3"] = {
    {"sdmi", "11101010010s1111", "0iiiddddii10mmmm"},
    {"sdnm", "11111010010snnnn", "1111dddd0000mmmm"}
  },
  ["asr_2"] = {
    {"sdm", "0100000100mmmddd"}
  },

  ["b_1"] = {
    {"B", "1101cccciiiiiiii"},
    {"B", "11100iiiiiiiiiii"}
  },
  ["b.w_1"] = {
    {"sB",  "11110scccciiiiii", "10j0kiiiiiiiiiii"},
    {"sB",  "11110siiiiiiiiii", "10j1kiiiiiiiiiii"}
  },

  ["bfc_3"] = {
    {"dim", "1111001101101111", "0iiiddddii0mmmmm"}
  },
  ["bfi_4"] = {
    {"dnim", "111100110110nnnn", "0iiiddddii0mmmmm"}
  },
  ["bic.w_3"] = {
    {"sdni", "11110H00001snnnn", "0HHHddddHHHHHHHH"},
    {"sdnmT", "11101010001snnnn", "0iiiddddiiTTmmmm"}
  },
  ["bic.w_4"] = {
    {"sdnmT", "11101010001snnnn", "0iiiddddiiTTmmmm"}
  },
  ["bic_2"] = {
    {"sdm", "0100001110mmmddd"}
  },
  ["bkpt_1"] = {
    {"i", "10111110iiiiiiii"}
  },
  ["blx_1"] = {
    {"m", "010001111mmmm000"}
  },
  ["bx_1"] = {
    {"m", "010001110mmmmooo"}
  },
  ["bl_1"] = {
    {"sB", "11110siiiiiiiiii", "11J1Kiiiiiiiiiii"}
  },
  ["cbz_2"] = {
    {"ni", "1011o0i1iiiiinnn"}
  },
  -- ["cdp_6"] = {
  --   {"CoCdCnCm{O}", "111t1110oooonnnn", "ddddCCCCOOO0mmmm"}
  -- },
  ["clrex_0"] = {
    {"", "1111001110111111", "1000111100101111"}
  },
  ["clz_2"] = {
    {"dm", "111110101011mmmm", "1111dddd1000xxxx"}
  },
  ["cmn.w_2"] = {
    {"ni", "11110H010001nnnn", "0HHH1111HHHHHHHH"},
    {"nmT", "111010110001nnnn", "0iii1111iiTTmmmm"}
  },
  ["cmn.w_3"] = {
    {"nmT", "111010110001nnnn", "0iii1111iiTTmmmm"}
  },
  ["cmn_2"] = {
    {"nm", "0100001011mmmnnn"}
  },
  ["cmp_2"] = {
    {"ni", "00101nnniiiiiiii"},
    {"nm", "0100001010mmmnnn"},
    {"nm", "01000101nmmmmnnn"}
  },
  ["cmp.w_2"] = {
    {"ni", "11110H011011nnnn", "0HHH1111HHHHHHHH"},
    {"nmT", "111010111011nnnn", "0iii1111iiTTmmmm"}
  },
  ["cmp.w_3"] = {
    {"nmT", "111010111011nnnn", "0iii1111iiTTmmmm"}
  },
  ["dbg_1"] = {
    {"h", "1111001110101111", "100000001111hhhh"}
  },
  ["dmb_1"] = {
    {"y", "1111001110111111", "100011110101oooo"}
  },
  ["dsb_1"] = {
    {"y", "1111001110111111", "100011110100oooo"}
  },
  ["eor.w_3"] = {
    {"sdni", "11110H00100snnnn", "0HHHddddHHHHHHHH"},
    {"sdnmT", "11101010100snnnn", "0iiiddddiiTTmmmm"}
  },
  ["eor.w_4"] = {
    {"sdnmT", "11101010100snnnn", "0iiiddddiiTTmmmm"}
  },
  ["eor_2"] = {
    {"sdm", "0100000001mmmddd"}
  },
  ["isb_1"] = {
    {"y", "1111001110111111", "100011110110oooo"}
  },


  ["it_1"] = {
    {"cM", "10111111cccc1000"}
    -- {"cm", "10111111ccccmmmm"}
  },
  ["ite_1"] = {
    {"cM", "10111111cccc0100"}
    -- {"cm", "10111111ccccmmmm"}
  },


  -- ["ldc_4"] = {
  --   {"CCd{n}{i}", "111t110puDw1nnnn", "ddddCCCCiiiiiiii"}
  -- },
  ["ldm_2"] = {
    {"nr", "11001nnnrrrrrrrr"}
  },
  -- ["ldm.w_2"] = {
  --   {"n<Hw:!>r", "1110100010w1nnnn", "rrrrrrrrrrrrrrrr"}
  -- },
  -- ["ldmdb_2"] = {
  --   {"n<Hw:!>r", "1110100100w1nnnn", "rrrrrrrrrrrrrrrr"}
  -- },

  ["ldr_2"] = {
    {"tL", "01101fffffnnnttt"},
    {"tL", "10011tttffffffff"},
    {"tL", "0101100mmmnnnttt"},
    {"tB", "01001tttiiiiiiii"},
  },

  ["ldr.w_2"] = {
    {"tL",  "111110001101nnnn", "ttttiiiiiiiiiiii"},
    {"tL",  "111110000101nnnn", "tttt1PUWiiiiiiii"},
    {"tL",  "111110000101nnnn", "tttt000000iimmmm"},
    {"tB",  "11111000u1011111", "ttttiiiiiiiiiiii"},
  },
  ["ldr.w_3"] = {
    {"tL",  "111110000101nnnn", "tttt1PUWiiiiiiii"},
  },
  ["ldrb_2"] = {
    {"tL", "01111iiiiinnnttt"},
    {"tL", "0101110mmmnnnttt"},
  },
  ["ldrb.w_3"] = {
    {"tL", "111110000001nnnn", "tttt1PUWiiiiiiii"},
    {"tL", "111110000001nnnn", "tttt000000iimmmm"}
  },
  ["ldrb.w_2"] = {
    {"tL", "111110000001nnnn", "tttt1PUWiiiiiiii"},
    {"tL", "111110001001nnnn", "ttttiiiiiiiiiiii"},
    {"tB", "11111000u0011111", "ttttiiiiiiiiiiii"}
  },
  ["ldrbt_2"] = {
    {"tL", "111110000001nnnn", "tttt1110iiiiiiii"}
  },
  ["ldrex_2"] = {
    {"tL", "111010000101nnnn", "tttt1111iiiiiiii"}
  },
  ["ldrexb_2"] = {
    {"tL", "111010001101nnnn", "tttt111101001111"}
  },
  ["ldrexh_2"] = {
    {"tL",   "111010001101nnnn", "tttt111101011111"}
  },
  ["ldrd_4"] = {
    {"tdL",  "1110100PU1W1nnnn", "ttttddddffffffff"}
  },
  ["ldrd_3"] = {
    {"tdLi", "1110100PU1W1nnnn", "ttttddddffffffff"},
    {"tdB",  "1110100PU1W11111", "ttttddddiiiiiiii"}
  },
  ["ldrh_2"] = {
    {"tL", "10001iiiiinnnttt"},
    {"tL", "0101101mmmnnnttt"}
  },
  ["ldrh_3"] = {
    {"tL", "10001iiiiinnnttt"},
    {"tL", "0101101mmmnnnttt"}
  },
  ["ldrh.w_3"] = {
    {"tL", "111110001011nnnn", "ttttiiiiiiiiiiii"},
    {"tL", "111110000011nnnn", "tttt1PUWiiiiiiii"},
    {"tL", "111110000011nnnn", "tttt000000iimmmm"}
  },
  ["ldrh.w_2"] = {
    {"tL", "111110001011nnnn", "ttttiiiiiiiiiiii"},
    {"tL", "111110000011nnnn", "tttt1PUWiiiiiiii"},
    {"tL", "111110000011nnnn", "tttt000000iimmmm"},
    {"tB", "11111000u0111111", "ttttiiiiiiiiiiii"},
  },
  ["ldrht_2"] = {
    {"tL", "111110000011nnnn", "tttt1110iiiiiiii"}
  },
  ["ldrht_3"] = {
    {"tL", "111110000011nnnn", "tttt1110iiiiiiii"}
  },
  ["ldrsb.w_3"] = {
    {"tL", "111110011001nnnn", "ttttiiiiiiiiiiii"},
    {"tL", "111110010001nnnn", "tttt1PUWiiiiiiii"},
    {"tL", "111110010001nnnn", "tttt000000iimmmm"}
  },
  ["ldrsb.w_2"] = {
    {"tL", "111110010001nnnn", "tttt1PUWiiiiiiii"},
    {"tB", "11111001u0011111", "ttttiiiiiiiiiiii"}
  },
  ["ldrsb_3"] = {
    {"tL", "0101011mmmnnnttt"}
  },
  ["ldrsbt_3"] = {
    {"tL", "111110010001nnnn", "tttt1110iiiiiiii"}
  },
  ["ldrsh.w_3"] = {
    {"tL", "111110010011nnnn", "tttt1PUWiiiiiiii"},
  },
  ["ldrsh.w_2"] = {
    {"tL", "111110011011nnnn", "ttttiiiiiiiiiiii"},
    {"tL", "111110010011nnnn", "tttt1PUWiiiiiiii"},
    {"tL", "111110010011nnnn", "tttt000000iimmmm"},
    {"tB", "11111001u0111111", "ttttiiiiiiiiiiii"},
  },
  ["ldrsh_3"] = {
    {"tL", "0101111mmmnnnttt"}
  },
  ["ldrsht_2"] = {
    {"tL", "111110010011nnnn", "tttt1110iiiiiiii"}
  },
  ["ldrsht_3"] = {
    {"tL", "111110010011nnnn", "tttt1110iiiiiiii"}
  },
  ["ldrt_2"] = {
    {"tL", "111110000101nnnn", "tttt1110iiiiiiii"}
  },
  ["lsl_3"] = {
    {"sdmi", "00000iiiiimmmddd"}
  },
  ["lsl.w_3"] = {
    {"sdmi", "11101010010s1111", "0iiiddddii00mmmm"},
    {"sdnm", "11111010000snnnn", "1111dddd0000mmmm"}
  },
  ["lsl_2"] = {
    {"sdm", "0100000010mmmddd"}
  },
  ["lsr_3"] = {
    {"sdmi", "00001iiiiimmmddd"}
  },
  ["lsr.w_3"] = {
    {"sdmi", "11101010010s1111", "0iiiddddii01mmmm"},
    {"sdnm", "11111010001snnnn", "1111dddd0000mmmm"}
  },
  ["lsr_2"] = {
    {"sdm", "0100000011mmmddd"}
  },
  -- ["mcr_6"] = {
  --   {"CotCnCm{p}", "11101110ooo0nnnn", "ttttCCCCppp1mmmm"}
  -- },
  -- ["mcr2_6"] = {
  --   {"CotCnCm{p}", "11111110ooo0nnnn", "ttttCCCCppp1mmmm"}
  -- },
  -- ["mcrr_5"] = {
  --   {"cotucm", "111011000100uuuu", "ttttccccoooommmm"}
  -- },
  -- ["mcrr2_5"] = {
  --   {"cotucm", "111111000100uuuu", "ttttccccoooommmm"}
  -- },
  ["mla_4"] = {
    {"dnma", "111110110000nnnn", "aaaadddd0000mmmm"}
  },
  ["mls_4"] = {
    {"dnma", "111110110000nnnn", "aaaadddd0001mmmm"}
  },
  ["mov_2"] = {
    {"sdi", "00100dddiiiiiiii"},
    {"sdm", "01000110dmmmmddd"}
  },
  ["mov.w_2"] = {
    {"sdi", "11110H00010s1111", "0HHHddddHHHHHHHH"},
    {"sdm", "11101010010s1111", "0000dddd0000mmmm"}
  },
  ["movw_2"] = {
    {"di", "11110H100100kkkk", "0HHHddddHHHHHHHH"}
  },
  ["movt_2"] = {
    {"di", "11110H101100kkkk", "0HHHddddHHHHHHHH"}
  },
  -- ["mrc_6"] = {
  --   {"CotCnCm{p}", "11101110ooo1nnnn", "ttttCCCCppp1mmmm"}
  -- },
  -- ["mrc2_6"] = {
  --   {"CotCnCm{p}", "11111110ooo1nnnn", "ttttCCCCppp1mmmm"}
  -- },
  -- ["mrrc_5"] = {
  --   {"CotuCm", "111011000101uuuu", "ttttccccoooommmm"}
  -- },
  -- ["mrrc2_5"] = {
  --   {"CotuCm", "111111000101uuuu", "ttttCCCCoooommmm"}
  -- },
  ["mrs_2"] = {
    {"dz", "1111001111101111", "1000ddddssssssss"}
  },
  ["msr_2"] = {
    {"yn", "111100111000nnnn", "1000mm00ssssssss"}
  },
  ["mul_3"] = {
    {"snmn", "0100001101nnnmmm"}
  },
  ["mul.w_3"] = {
    {"dnm", "111110110000nnnn", "1111dddd0000mmmm"}
  },
  ["mvn.w_2"] = {
    {"sdi", "11110H00011s1111", "0HHHddddHHHHHHHH"},
    {"sdmT", "11101010011s1111", "0iiiddddiiTTmmmm"}
  },
  ["mvn.w_3"] = {
    {"sdmT", "11101010011s1111", "0iiiddddiiTTmmmm"}
  },
  ["mvn_2"] = {
    {"sdm", "0100001111mmmddd"}
  },
  ["nop_0"] = {
    {"", "1011111100000000"}
  },
  ["orn_3"] = {
    {"sdni", "11110H00011snnnn", "0HHHddddHHHHHHHH"},
    {"sdnmT", "11101010011snnnn", "0iiiddddiiTTmmmm"}
  },
  ["orn_4"] = {
    {"sdnmT", "11101010011snnnn", "0iiiddddiiTTmmmm"}
  },
  ["orr.w_3"] = {
    {"sdni", "11110H00010snnnn", "0HHHddddHHHHHHHH"},
    {"sdnmT", "11101010010snnnn", "0iiiddddiiTTmmmm"}
  },
  ["orr.w_4"] = {
    {"sdnmT", "11101010010snnnn", "0iiiddddiiTTmmmm"}
  },
  ["orr_2"] = {
    {"sdm", "0100001100mmmddd"}
  },
  -- ["pld_2"] = {
  --   {"{ni}", "111110001001nnnn", "1111iiiiiiiiiiii"},
  --   {"{ni}", "111110000001nnnn", "11111100iiiiiiii"},
  --   {"{nmt}", "111110000001nnnn", "1111000000ssmmmm"}
  -- },
  -- ["pld_1"] = {
  --   {"B", "11111000u0011111", "1111iiiiiiiiiiii"}
  -- },
  -- ["pli_2"] = {
  --   {"{ni}", "111110011001nnnn", "1111iiiiiiiiiiii"},
  --   {"{ni}", "111110010001nnnn", "11111100iiiiiiii"},
  --   {"{nmt}", "111110010001nnnn", "1111000000ssmmmm"}
  -- },
  -- ["pli_1"] = {
  --   {"B", "11111001u0011111", "1111iiiiiiiiiiii"}
  -- },
  ["pop_1"] = {
    {"r", "1011110prrrrrrrr"}
  },
  ["pop.w_1"] = {
    {"r", "1110100010111101", "rrrrrrrrrrrrrrrr"},
    {"t", "1111100001011101", "tttt101100000100"}
  },
  ["push_1"] = {
    {"r", "1011010mrrrrrrrr"}
  },
  ["push.w_1"] = {
    {"r", "1110100100101101", "rrrrrrrrrrrrrrrr"},
    {"t", "1111100001001101", "tttt110100000100"}
  },
  ["rbit_2"] = {
    {"dm", "111110101001mmmm", "1111dddd1010xxxx"}
  },
  ["rev_2"] = {
    {"dm", "1011101000mmmddd"}
  },
  ["rev.w_2"] = {
    {"dm", "111110101001mmmm", "1111dddd1000xxxx"}
  },
  ["rev16_2"] = {
    {"dm", "1011101001mmmddd"}
  },
  ["rev16.w_2"] = {
    {"dm", "111110101001mmmm", "1111dddd1001xxxx"}
  },
  ["revsh_2"] = {
    {"dm", "1011101011mmmddd"}
  },
  ["revsh.w_2"] = {
    {"dm", "111110101001mmmm", "1111dddd1011xxxx"}
  },
  ["ror.w_3"] = {
    {"sdmi", "11101010010s1111", "0iiiddddii11mmmm"},
    {"sdnm", "11111010011snnnn", "1111dddd0000mmmm"}
  },
  ["ror_2"] = {
    {"sdm", "0100000111mmmddd"}
  },
  ["rrx_2"] = {
    {"sdm", "11101010010s1111", "0000dddd0011mmmm"}
  },
  ["rsb_3"] = {
    {"sdn0", "0100001001nnnddd"},
    {"sdnmT", "11101011110snnnn", "0iiiddddiiTTmmmm"}
  },
  ["rsb_4"] = {
    {"sdnmT", "11101011110snnnn", "0iiiddddiiTTmmmm"}
  },
  ["rsb.w_3"] = {
    {"sdni", "11110H01110snnnn", "0HHHddddHHHHHHHH"}
  },
  ["sbc.w_3"] = {
    {"sdni", "11110H01011snnnn", "0HHHddddHHHHHHHH"},
    {"sdnmT", "11101011011snnnn", "0iiiddddiiTTmmmm"}
  },
  ["sbc.w_4"] = {
    {"sdnmT", "11101011011snnnn", "0iiiddddiiTTmmmm"}
  },
  ["sbc_2"] = {
    {"sdm", "0100000110mmmddd"}
  },
  ["sbfx_4"] = {
    {"sdniw", "111100110100nnnn", "0iiiddddii0wwwww"}
  },
  ["sdiv_3"] = {
    {"dnm", "111110111001nnnn", "1111dddd1111mmmm"}
  },
  ["sel_3"] = {
    {"dnm", "111110101010nnnn", "1111dddd1000mmmm"}
  },
  ["smlal_4"] = {
    {"lhnm", "111110111100nnnn", "llllhhhh0000mmmm"}
  },
  ["smull_4"] = {
    {"lhnm", "111110111000nnnn", "llllhhhh0000mmmm"}
  },
  ["ssat_3"] = {
    {"dknf", "1111001100f0nnnn", "0iiiddddii0kkkkk"}
  },
  ["stc_4"] = {
    {"CCd{n}{i}", "1110110puNw0nnnn", "ddddCCCCiiiiiiii"}
  },
  ["stc2_4"] = {
    {"CCd{n}{i}", "1111110puNw0nnnn", "ddddCCCCiiiiiiii"}
  },
  -- ["stm_2"] = {
  --   {"n!{r}", "11000nnnrrrrrrrr"}
  -- },
  -- ["stm.w_2"] = {
  --   {"n<Hw:!>{r}", "1110100010w0nnnn", "rrrrrrrrrrrrrrrr"}
  -- },
  -- ["stmdb_2"] = {
  --   {"n<Hw:!>{r}", "1110100100w0nnnn", "rrrrrrrrrrrrrrrr"}
  -- },
  ["str_2"] = {
    {"tL", "01100iiiiinnnttt"},
    {"tL", "10010tttiiiiiiii"},
    {"tL", "0101000mmmnnnttt"}
  },
  ["str.w_2"] = {
    {"tL", "111110001100nnnn", "ttttiiiiiiiiiiii"},
    {"tL", "111110000100nnnn", "tttt1PUWiiiiiiii"},
    {"tL", "111110000100nnnn", "tttt000000iimmmm"}
  },
  ["str.w_3"] = {
    {"tL", "111110000100nnnn", "tttt1PUWiiiiiiii"},
  },
  ["strb_2"] = {
    {"tL", "01110iiiiinnnttt"},
    {"tL", "0101010mmmnnnttt"}
  },
  ["strb.w_3"] = {
    {"tL", "111110000000nnnn", "tttt1PUWiiiiiiii"},
  },
  ["strb.w_2"] = {
    {"tL", "111110001000nnnn", "ttttiiiiiiiiiiii"},
    {"tL", "111110000000nnnn", "tttt1PUWiiiiiiii"},
    {"tL", "111110000000nnnn", "tttt000000iimmmm"},
  },
  ["strbt_3"] = {
    {"tL", "111110000000nnnn", "tttt1110iiiiiiii"}
  },
  ["strex_3"] = {
    {"dtL", "111010000100nnnn", "ttttddddiiiiiiii"}
  },
  ["strexb_3"] = {
    {"dtL", "111010001100nnnn", "tttt11110100dddd"}
  },
  ["strexh_3"] = {
    {"dtL", "111010001100nnnn", "tttt11110101dddd"}
  },
  ["strd_3"] = {
    {"tdL", "1110100PU1W0nnnn", "ttttddddiiiiiiii"},
  },
  ["strd_4"] = {
    {"tdL", "1110100PU1W0nnnn", "ttttddddiiiiiiii"},
  },
  ["strh_3"] = {
    {"tL", "10000iiiiinnnttt"},
    {"tL", "0101001mmmnnnttt"}
  },
  ["strh.w_3"] = {
    {"tL", "111110001010nnnn", "ttttiiiiiiiiiiii"},
    {"tL", "111110000010nnnn", "tttt1PUWiiiiiiii"}
  },
  ["strht_3"] = {
    {"tL", "111110000010nnnn", "tttt1110iiiiiiii"}
  },
  ["strt_3"] = {
    {"tL", "111110000100nnnn", "tttt1110iiiiiiii"}
  },
  ["sub_3"] = {
    {"sdni", "0001111iiinnnddd"},
    {"sdnm", "0001101mmmnnnddd"}
  },
  ["sub_2"] = {
    {"sdi", "00111dddiiiiiiii"},
    {"sppi", "101100001fffffff"}
  },
  ["sub.w_3"] = {
    {"sdni",  "11110H01101snnnn", "0HHHddddHHHHHHHH"},
    {"sdnmT", "11101011101snnnn", "0iiiddddiiTTmmmm"}
  },
  ["sub.w_4"] = {
    {"sdnmT", "11101011101snnnn", "0iiiddddiiTTmmmm"}
  },
  ["subw_3"] = {
    {"dni", "11110H101010nnnn", "0HHHddddHHHHHHHH"}
  },
  ["svc_1"] = {
    {"i", "11011111iiiiiiii"}
  },
  ["sxtb_2"] = {
    {"dm", "1011001001mmmddd"}
  },
  ["sxtb.w_2"] = {
    {"dmr", "1111101001001111", "1111dddd10rrmmmm"}
  },
  ["sxth_2"] = {
    {"dm", "1011001000mmmddd"}
  },
  ["sxth.w_2"] = {
    {"dmr", "1111101000001111", "1111dddd10rrmmmm"}
  },
  ["teq_2"] = {
    {"ni", "11110H001001nnnn", "0HHH1111HHHHHHHH"},
    {"nmT", "111010101001nnnn", "0iii1111iiTTmmmm"}
  },
  ["teq_3"] = {
    {"nmT", "111010101001nnnn", "0iii1111iiTTmmmm"}
  },
  -- TODO
  -- ["tb_4"] = {
  --   {"{nm<Hh:lsl#1>}", "111010001101nnnn", "11110000000hmmmm"}
  -- },
  ["tst.w_2"] = {
    {"ni", "11110H000001nnnn", "0HHH1111HHHHHHHH"},
    {"nmT", "111010100001nnnn", "0iii1111iiTTmmmm"}
  },
  ["tst.w_3"] = {
    {"nmT", "111010100001nnnn", "0iii1111iiTTmmmm"}
  },
  ["tst_2"] = {
    {"nm", "0100001000mmmnnn"}
  },
  ["ubfx_4"] = {
    {"dniw", "111100111100nnnn", "0iiiddddii0wwwww"}
  },
  ["udiv_3"] = {
    {"dnm", "111110111011nnnn", "1111dddd1111mmmm"}
  },
  ["umlal_4"] = {
    {"lhnm", "111110111110nnnn", "llllhhhh0000mmmm"}
  },
  ["umull_4"] = {
    {"lhnm", "111110111010nnnn", "llllhhhh0000mmmm"}
  },
  ["usat_3"] = {
    {"dknf", "1111001110f0nnnn", "0iiiddddii0kkkkk"}
  },
  ["uxtb_2"] = {
    {"dm", "1011001011mmmddd"}
  },
  ["uxtb.w_2"] = {
    {"dmr", "1111101001011111", "1111dddd10rrmmmm"}
  },
  ["uxth_2"] = {
    {"dm", "1011001010mmmddd"}
  },
  ["uxth.w_2"] = {
    {"dmr", "1111101000011111", "1111dddd10rrmmmm"}
  },
}

function TCR_LOG (...)
  for k,i in pairs({...}) do
    io.stderr:write(i)
    io.stderr:write(' ')
  end
  io.stderr:write('\n')
end

-- adds 's' varants
do
  local addt = {}
  for k,v in pairs(map_op) do
    local s = k:gsub("([.]?w?)(_%d+)$", "s%1%2")
    for _, i in pairs(v) do
      if i[1]:find('s') then
        local t = {i[1]}
        for j=2,#i do
          local word = i[j]:gsub('s', '1')
          table.insert(t, word);
        end
        if #t > 1 then
          if not addt[s] then
            addt[s] = {}
          end
          table.insert(addt[s], t)
        end
      end
    end
  end
  for k,v in pairs(addt) do
    map_op[k] = v
  end
end

function tobitstr (num)
    local t={}
    while num>0 do
        rest=num%2
        table.insert(t,1,rest)
        num=(num-rest)/2
    end
    return table.concat(t)
end

-- .w is an alias for most non-.w instructions
do
  for k,v in pairs(map_op) do
    if k:match("[.]w_(%d+)$") then
      local s = k:gsub("[.]w_(%d+)$", "_%1")
      if not map_op[s] then
        map_op[s] = {}
      end
      for _, i in pairs(v) do
        table.insert(map_op[s], i)
      end
    end
  end
end

-- adds conditional varants
do
  local addt = {}
  for cond,c in pairs(map_cond) do
    for k,v in pairs(map_op) do
      local s = k:gsub("([.]?w?)(_%d+)$", cond .. "%1%2")
      for _, i in pairs(v) do
        local t = {i[1]}
        for j=2,#i do
          local word = i[j]:gsub('cccc', ('0000' .. tobitstr(c)):sub(-4))
          table.insert(t, word);
        end
        if #t > 1 then
          if not addt[s] then
            addt[s] = {}
          end
          table.insert(addt[s], t)
        end
      end
    end
  end
  for k,v in pairs(addt) do
    map_op[k] = v
  end
end


-- Add mnemonics for "s" variants.
-- do
--   local t = {}
--   for k,v in pairs(map_op) do
--     if sub(v, -1) == "s" then
--       local v2 = {}
--       t[sub(k, 1, -3).."s"..sub(k, -2)] = v2
--     end
--   end
--   for k,v in pairs(t) do
--     map_op[k] = v
--   end
-- end

------------------------------------------------------------------------------

local function parse_gpr(expr)
  local tname, ovreg = match(expr, "^([%w_]+):(r1?[0-9])$")
  local tp = map_type[tname or expr]
  if tp then
    local reg = ovreg or tp.reg
    if not reg then
      werror("type `"..(tname or expr).."' needs a register override")
    end
    expr = reg
  end
  local r = match(expr, "^r(1?[0-9])$")
  if r then
    r = tonumber(r)
    if r <= 15 then return r, tp end
  end
  werror("bad register name `"..expr.."'")
end

local function parse_gpr_pm(expr)
  local pm, expr2 = match(expr, "^([+-]?)(.*)$")
  return parse_gpr(expr2), (pm == "-")
end

local function parse_reglist(reglist)
  reglist = match(reglist, "^{%s*([^}]*)}$")
  if not reglist then werror("register list expected") end
  local rr = 0
  for p in gmatch(reglist..",", "%s*([^,]*),") do
    local rbit = shl(1, parse_gpr(gsub(p, "%s+$", "")))
    if band(rr, rbit) ~= 0 then
      werror("duplicate register `"..p.."'")
    end
    rr = rr + rbit
  end
  return rr
end

local function parse_imm(imm, bits, shift, scale, signed)
  imm = match(imm, "^#(.*)$")
  if not imm then werror("expected immediate operand") end
  local n = tonumber(imm)
  if n then
    local m = sar(n, scale)
    if shl(m, scale) == n then
      if signed then
        local s = sar(m, bits-1)
        if s == 0 then return shl(m, shift)
        elseif s == -1 then return shl(m + shl(1, bits), shift) end
      else
       if sar(m, bits) == 0 then return shl(m, shift) end
      end
    end
    werror("out of range immediate `"..imm.."'")
  else
    waction("IMM", (signed and 32768 or 0)+scale*1024+bits*32+shift, imm)
    return 0
  end
end

local function parse_imm_simple(imm)
  local n = tonumber(imm)
  if n then
    -- local m = band(n)
    -- for i=0,-15,-1 do
    --   if shr(m, 8) == 0 then TCR_LOG(' ... ', m + shl(band(i, 15), 8)); return m + shl(band(i, 15), 8) end
    --   m = ror(m, 2)
    -- end
    return band(n)
    -- TCR_LOG(' ... NO SIR!');
    -- werror("out of range immediate `"..imm.."'")
  else
    waction("IMM12", 0, imm)
    return 0
  end
end

local function parse_imm_load(imm, ext)
  local n = tonumber(imm)
  if n then
    if ext > 0 and n > math.pow(2, ext) then
      werror("out of range immediate `"..imm.."' larger than "..ext.." bits")
    end
    return n
  else
    -- TODO 5
    waction(ext == 8 and "IMML8" or "IMML12", 32768 + shl(ext and 8 or 12, 5), imm)
    return 0
  end
end

local function parse_shift(shift, gprok)
  if shift == "rrx" then
    return 3 * 32
  else
    local s, s2 = match(shift, "^(%S+)%s*(.*)$")
    s = map_shift[s]
    if not s then werror("expected shift operand") end
    if sub(s2, 1, 1) == "#" then
      return parse_imm(s2, 5, 0, 0, false), s
    else
      if not gprok then werror("expected immediate shift operand") end
      return parse_gpr(s2), s
    end
  end
end

local function parse_label(label, def)
  local prefix = sub(label, 1, 2)
  -- =>label (pc label reference)
  if prefix == "=>" then
    return "PC", 0, sub(label, 3)
  end
  -- ->name (global label reference)
  if prefix == "->" then
    return "LG", map_global[sub(label, 3)]
  end
  if def then
    -- [1-9] (local label definition)
    if match(label, "^[1-9]$") then
      return "LG", 10+tonumber(label)
    end
  else
    -- [<>][1-9] (local label reference)
    local dir, lnum = match(label, "^([<>])([1-9])$")
    if dir then -- Fwd: 1-9, Bkwd: 11-19.
      return "LG", lnum + (dir == ">" and 0 or 10)
    end
    -- extern label (extern label reference)
    local extname = match(label, "^extern%s+(%S+)$")
    if extname then
      return "EXT", map_extern[extname]
    end
  end
  werror("bad label `"..label.."'")
end

------------------------------------------------------------------------------

function parse_op_word (word, bits) 
  for i=1,#word do
    local bit = word:sub(i, i)
    bits[bit] = (bits[bit] or 0) + 1
  end
end

function populate_op_word (word, values)
  local op = 0
  for i=#word,1,-1 do
    local bit = word:sub(i, i)
    if bit == '1' then
      op = op + shl(1, #word)
    elseif bit ~= '0' then
      op = op + shl(band(values[bit] or 0, 1), #word)
      values[bit] = shr(values[bit] or 0, 1)
    end
    op = shr(op, 1)
  end
  return op
end

local function parse_template_new_subset(bits, values, params, templatestr, nparams)
  local n = 1
  -- TCR_LOG('PARSETEMPLATE: ' .. templatestr)
  for k,p in pairs(params) do
    -- TCR_LOG(' ..> ', k, p)
  end
  local pidx = 1
  while pidx <= #templatestr and n <= #params do
    local p = templatestr:sub(pidx, pidx)

    -- TCR_LOG('match ' .. p .. ' against ' .. tostring(params[n]) .. ' in ' .. templatestr .. ' ' .. templatestr)

    -- Immediate values
    if p == 'i' then
      local imm = match(params[n], "^#(.*)$")
      if not imm then
        werror('bad immediate (i) operand')
      end
      if bits['i'] then
        values[p] = parse_imm_simple(imm)
        if values[p] >= math.pow(2, bits[p]) then
          werror('immediate operand larger than ' .. bits[p] .. ' bits')
        end
      elseif bits['H'] then
        -- fun encoding time!
        local val = parse_imm_simple(imm)
        local a = shr(band(val, 0x80), 7)
        local _bcdefgh = 0x80 + band(val, 0x7F)
        local abcdefgh = band(val, 0xFF);
        local ABCDE = 00000

        -- Table A5-11 in ARM handbook
        if val == abcdefgh then
          -- 00000000 00000000 00000000 abcdefgh
          ABCDE = 0 + a
        elseif val == shl(abcdefgh, 16) + abcdefgh then
          -- 00000000 abcdefgh 00000000 abcdefgh
          ABCDE = 2 + a
        elseif val == shl(abcdefgh, 24) + shl(abcdefgh, 8) then
          -- abcdefgh 00000000 abcdefgh 00000000
          ABCDE = 4 + a
        elseif val == shl(abcdefgh, 24) + shl(abcdefgh, 16) + shl(abcdefgh, 8) + abcdefgh then
          -- abcdefgh abcdefgh abcdefgh abcdefgh
          ABCDE = 6 + a
        else
          -- 1bcdefgh 00000000 00000000 00000000
          -- ...
          -- 00000000 00000000 00000001 bcdefgh0
          ABCDE = 8;
          for i = 24,0,-1 do 
            if val == shl(_bcdefgh, i) then
              break;
            end
            ABCDE = ABCDE + 1
          end
          if i == 0 then
            werror('bad thumb expanded immediate ' + val)
          end
        end

        values['H'] = shl(ABCDE, 7) + band(val, 0x7F)
      end
      n = n + 1

    elseif p == 'U' then
      local imm = match(params[n], "^#(.*)$")
      if imm then
        local val = parse_imm_new(imm)
        if val >= math.pow(2, bits[p]) then
          werror('signed immediate operand larger than ' .. bits[p] .. ' bits')
        end
        values['i'] = math.abs(val)
        values['U'] = tonumber(val >= 0)
      else
        werror('bad signed immediate operand')
      end
      n = n + 1

    -- Immediate values with lower two bits empty
    elseif p == 'f' then
      local imm = match(params[n], "^#(.*)$")
      if imm then
        values[p] = parse_imm_simple(imm)
      else
        werror('bad immediate operand')
      end
      if values[p] % 4 ~= 0 then
        werror('lower two bits of immediate value not empty')
      end
      values['i'] = shr(values[p], 2)
      n = n + 1

    elseif p == 'd' then
      values[p] = parse_gpr(params[n])
      n = n + 1
    elseif p == 'n' then
      values[p] = parse_gpr(params[n])
      n = n + 1
    elseif p == 'm' then
      values[p] = parse_gpr(params[n])
      n = n + 1
    elseif p == 't' then
      values[p] = parse_gpr(params[n])
      n = n + 1
    elseif p == 'l' then
      values[p] = parse_gpr(params[n])
      n = n + 1
    elseif p == 'h' then
      values[p] = parse_gpr(params[n])
      n = n + 1

    elseif p == 'T' then
      local i, t = parse_shift(params[n], true)
      values['i'] = i
      values['t'] = t
      n = n + 1

    elseif p == "B" then
      local mode, n2, s = parse_label(params[n], false)
      waction("REL_"..mode, n2, s, 1)
      values['u'] = tonumber(n2 >= 10)
      n = n + 1

    elseif p == 'c' then
      if params[n] == "le" then
        values[p] = 0xD
        n = n + 1
      else
        werror('invalid conditional')
      end

    -- expect literals
    elseif p == 'p' then
      if params[n] ~= 'sp' then
        werror('expecting SP register')
      end
      n = n + 1
    elseif p == '0' then
      if params[n] ~= '#0' then
        werror('expecting #0 literal')
      end
      n = n + 1

    elseif p == 'M' then
      n = n + 1
    elseif p == 's' then
      -- skip

    elseif p == 'r' then
      values[p] = parse_reglist(params[n])
      n = n + 1

    elseif p == 'L' then

      local pn = params[n]
      local p1, wb = match(pn, "^%[%s*(.-)%s*%](!?)$")
      local p2 = params[n+1]

      values['P'] = 0
      values['U'] = 1
      values['W'] = 0
      local ldrd = false
      local ext = bits['i'] == 8

      if not p1 then
        if p2 then
          werror("expected address operand")
        end
        if match(pn, "^[<>=%-]") or match(pn, "^extern%s+") then
          local mode, n, s = parse_label(pn, false)
          waction("REL_"..mode, n + (ext and 0x1800 or 0x0800), s, 1)
          -- op = op + 15 * 65536 + 0x01000000 + (ext and 0x00400000 or 0)
        else
          local reg, tailr = match(pn, "^([%w_:]+)%s*(.*)$")
          if not (reg and tailr ~= "") then
            werror("expected address operand")
          end
          local d, tp = parse_gpr(reg)
          if not tp then
            werror("expected address operand")
          end
          waction(ext and "IMML8" or "IMML12", 32768 + 32*(ext and 8 or 12),
          format(tp.ctypefmt, tailr))
          -- op = op + shl(d, 16) + 0x01000000 + (ext and 0x00400000 or 0)
        end

        n = n + 1
      else
        if p2 then
          values['P'] = 0
          values['W'] = 1

          if wb == "!" then werror("bad use of '!'") end
          local p3 = params[n+2]
          values['n'] = parse_gpr(p1)
          local imm = match(p2, "^#(.*)$")
          if imm then
            if p3 then werror("too many parameters") end
            local bitlen = bits['i'] or shl(bits['f'] or 0, 2)
            local m = parse_imm_load(imm, bitlen)
            if m < 0 and not bits['U'] then
              werror('negative immediate')
            elseif not bits['i'] and not bits['f'] then
              werror('immediate not supported')
            elseif bits['f'] and m % 4 ~= 0 then
              werror('immediate must have lowest two bits cleared')
            elseif math.abs(m) >= math.pow(2, bitlen) then
              werror('immediate operand larger than ' .. bitlen .. ' bits')
            end
            values['U'] = tonumber(m >= 0)
            values['i'] = math.abs(m)
            values['f'] = shr(math.abs(m), 2)
            -- op = op + m + (ext and 0x00400000 or 0)
          else
            local m, neg = parse_gpr_pm(p2)
            values['U'] = tonumber(not neg)
            if p3 then values['i'] = parse_shift(p3) end
            -- if ldrd and (m == d or m-1 == d) then werror("register conflict") end
          end

          n = n + 2
        else
          values['P'] = 1
          values['W'] = tonumber(wb == "!")

          local p1a, p2 = match(p1, "^([^,%s]*)%s*(.*)$")
          values['n'] = parse_gpr(p1a)
          if p2 ~= "" then
            local imm = match(p2, "^,%s*#(.*)$")
            if imm then
              local bitlen = bits['i'] or shl(bits['f'] or 0, 2)
              local m = parse_imm_load(imm, bitlen)
              if m < 0 and not bits['U'] then
                werror('negative immediate')
              elseif not bits['i'] and not bits['f'] then
                werror('immediate not supported')
              elseif bits['f'] and m % 4 ~= 0 then
                werror('immediate must have lowest two bits cleared')
              elseif math.abs(m) >= math.pow(2, bitlen) then
                werror('immediate operand larger than ' .. bitlen .. ' bits')
              end
              values['U'] = tonumber(m >= 0)
              values['i'] = math.abs(m)
              values['f'] = shr(math.abs(m), 2)
            else
              local p2a, p3 = match(p2, "^,%s*([^,%s]*)%s*,?%s*(.*)$")
              local m, neg = parse_gpr_pm(p2a)
              -- if ldrd and (m == d or m-1 == d) then werror("register conflict") end
              values['U'] = tonumber(not neg)
              if p3 ~= "" then
                if ext then werror("too many parameters") end
                values['i'] = parse_shift(p3)
              end
            end
          else
            if wb == "!" then werror("bad use of '!'") end
            -- op = op + (ext and 0x00c00000 or 0x00800000)
            values['U'] = 1
            values['i'] = 0
          end

          n = n + 1
        end
      end

    elseif p == '{' then
      local newpidx = pidx
      while templatestr:sub(newpidx, newpidx) ~= '}' and newpidx <= #templatestr do
        newpidx = newpidx + 1
      end
      if templatestr:sub(newpidx, newpidx) ~= '}' then
        werror('no matching ] in definition')
      end

      local subparams = {}
      if params[n]:sub(1, 1) ~= '[' or params[n]:sub(-1, -1) ~= ']' then
        werror('parameter ' .. tonumber(n) .. ' lacks brackets')
      end
      for s in gmatch(params[n]:sub(2, -2), "[^%s,]+") do
        table.insert(subparams, s)
      end
      parse_template_new_subset(bits, values, subparams, templatestr:sub(pidx+1, newpidx-1), #subparams)
      pidx = newpidx + 1
      n = n + 1

    else
      TCR_LOG('UNKNOWN PATTERN:', p)
      assert(false)
    end

    pidx = pidx + 1
  end
end

local function parse_template_new(params, template, nparams, pos)
  local bits = {}
  for i=2,#template do
    parse_op_word(template[i], bits)
  end

  local values = {}
  parse_template_new_subset(bits, values, params, template[1], nparams, pos)

  -- for k,v in pairs(bits) do
  --   TCR_LOG(k .. ' ' .. v)
  -- end
  -- assert(false)
  local ops = {}
  for i=#template,2,-1 do
    table.insert(ops, populate_op_word(template[i], values))
  end
  for i=#ops,1,-1 do
    wputpos(pos, ops[i])
    pos = pos + 1
  end
  return pos
end

map_op[".template__"] = function(params, template, nparams)
  if not params then return sub(template, 9) end

  -- Limit number of section buffer positions used by a single dasm_put().
  -- A single opcode needs a maximum of 3 positions.
  if secpos+3 > maxsecpos then wflush() end
  local pos = wpos()
  local origpos, apos, spos = pos, #actargs, secpos

  -- for k,v in pairs(params) do
  --   TCR_LOG(' --> ' .. k .. ' ' .. v)
  -- end

  local ok, err
  for i, t in pairs(template) do
  -- for t_ in gmatch(template, "[^|]+") do
  --   local donext = false
  --   for t in gmatch(t_, "[^,]+") do
  --     if donext then
  --       pos = wpos()
  --     end
      ok, err = pcall(parse_template_new, params, t, nparams, pos)
      -- TCR_LOG('error?:', t[1], err)
    --   donext = true
    -- end
    if ok then return end
    secpos = spos
    actargs[apos+1] = nil
    actargs[apos+2] = nil
    actargs[apos+3] = nil
  end
  error(err, 0)
end

------------------------------------------------------------------------------

-- Pseudo-opcode to mark the position where the action list is to be emitted.
map_op[".actionlist_1"] = function(params)
  if not params then return "cvar" end
  local name = params[1] -- No syntax check. You get to keep the pieces.
  wline(function(out) writeactions(out, name) end)
end

-- Pseudo-opcode to mark the position where the global enum is to be emitted.
map_op[".globals_1"] = function(params)
  if not params then return "prefix" end
  local prefix = params[1] -- No syntax check. You get to keep the pieces.
  wline(function(out) writeglobals(out, prefix) end)
end

-- Pseudo-opcode to mark the position where the global names are to be emitted.
map_op[".globalnames_1"] = function(params)
  if not params then return "cvar" end
  local name = params[1] -- No syntax check. You get to keep the pieces.
  wline(function(out) writeglobalnames(out, name) end)
end

-- Pseudo-opcode to mark the position where the extern names are to be emitted.
map_op[".externnames_1"] = function(params)
  if not params then return "cvar" end
  local name = params[1] -- No syntax check. You get to keep the pieces.
  wline(function(out) writeexternnames(out, name) end)
end

------------------------------------------------------------------------------

-- Label pseudo-opcode (converted from trailing colon form).
map_op[".label_1"] = function(params)
  if not params then return "[1-9] | ->global | =>pcexpr" end
  if secpos+1 > maxsecpos then wflush() end
  local mode, n, s = parse_label(params[1], true)
  if mode == "EXT" then werror("bad label definition") end
  waction("LABEL_"..mode, n, s, 1)
end

------------------------------------------------------------------------------

-- Pseudo-opcodes for data storage.
map_op[".long_*"] = function(params)
  if not params then return "imm..." end
  for _,p in ipairs(params) do
    local n = tonumber(p)
    if not n then werror("bad immediate `"..p.."'") end
    if n < 0 then n = n + 2^32 end
    wputw(n)
    if secpos+2 > maxsecpos then wflush() end
  end
end

-- Alignment pseudo-opcode.
map_op[".align_1"] = function(params)
  if not params then return "numpow2" end
  if secpos+1 > maxsecpos then wflush() end
  local align = tonumber(params[1])
  if align then
    local x = align
    -- Must be a power of 2 in the range (2 ... 256).
    for i=1,8 do
      x = x / 2
      if x == 1 then
  waction("ALIGN", align-1, nil, 1) -- Action byte is 2**n-1.
  return
      end
    end
  end
  werror("bad alignment")
end

------------------------------------------------------------------------------

-- Pseudo-opcode for (primitive) type definitions (map to C types).
map_op[".type_3"] = function(params, nparams)
  if not params then
    return nparams == 2 and "name, ctype" or "name, ctype, reg"
  end
  local name, ctype, reg = params[1], params[2], params[3]
  if not match(name, "^[%a_][%w_]*$") then
    werror("bad type name `"..name.."'")
  end
  local tp = map_type[name]
  if tp then
    werror("duplicate type `"..name.."'")
  end
  -- Add #type to defines. A bit unclean to put it in map_archdef.
  map_archdef["#"..name] = "sizeof("..ctype..")"
  -- Add new type and emit shortcut define.
  local num = ctypenum + 1
  map_type[name] = {
    ctype = ctype,
    ctypefmt = format("Dt%X(%%s)", num),
    reg = reg,
  }
  wline(format("#define Dt%X(_V) (int)(ptrdiff_t)&(((%s *)0)_V)", num, ctype))
  ctypenum = num
end
map_op[".type_2"] = map_op[".type_3"]

-- Dump type definitions.
local function dumptypes(out, lvl)
  local t = {}
  for name in pairs(map_type) do t[#t+1] = name end
  sort(t)
  out:write("Type definitions:\n")
  for _,name in ipairs(t) do
    local tp = map_type[name]
    local reg = tp.reg or ""
    out:write(format("  %-20s %-20s %s\n", name, tp.ctype, reg))
  end
  out:write("\n")
end

------------------------------------------------------------------------------

-- Set the current section.
function _M.section(num)
  waction("SECTION", num)
  wflush(true) -- SECTION is a terminal action.
end

------------------------------------------------------------------------------

-- Dump architecture description.
function _M.dumparch(out)
  out:write(format("DynASM %s version %s, released %s\n\n",
    _info.arch, _info.version, _info.release))
  dumpactions(out)
end

-- Dump all user defined elements.
function _M.dumpdef(out, lvl)
  dumptypes(out, lvl)
  dumpglobals(out, lvl)
  dumpexterns(out, lvl)
end

------------------------------------------------------------------------------

-- Pass callbacks from/to the DynASM core.
function _M.passcb(wl, we, wf, ww)
  wline, werror, wfatal, wwarn = wl, we, wf, ww
  return wflush
end

-- Setup the arch-specific module.
function _M.setup(arch, opt)
  g_arch, g_opt = arch, opt
end

-- Merge the core maps and the arch-specific maps.
function _M.mergemaps(map_coreop, map_def)
  setmetatable(map_op, { __index = function(t, k)
    local v = map_coreop[k]
    if v then return v end
    local k1, cc, k2 = match(k, "^(.-)(..)([._].*)$")
    local cv = map_cond[cc]
    if cv then
      local v = rawget(t, k1..k2)
      if type(v) == "string" then
        local scv = format("%x", cv)
        return gsub(sub(v, 1, 1) .. scv .. sub(v, 3), "|e", "|"..scv)
      end
    end
  end })
  setmetatable(map_def, { __index = map_archdef })
  return map_op, map_def
end

return _M

------------------------------------------------------------------------------

