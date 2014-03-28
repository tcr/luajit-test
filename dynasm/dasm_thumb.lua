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
  -- Basic data processing instructions.
  and_3 = "e0000000DNPs",
  eor_3 = "e0200000DNPs",
  sub_3 = "e0400000DNPs",
  rsb_3 = "e0600000DNPs",
  -- add_3 = "e0800000DNPs",
  adc_3 = "e0a00000DNPs",
  sbc_3 = "e0c00000DNPs",
  rsc_3 = "e0e00000DNPs",
  tst_2 = "e1100000NP",
  teq_2 = "e1300000NP",
  -- cmp_2 = "e1500000NP",
  cmn_2 = "e1700000NP",
  orr_3 = "e1800000DNPs",
  -- mov_2 = "e1a00000DPs",
  bic_3 = "e1c00000DNPs",
  mvn_2 = "e1e00000DPs",

  and_4 = "e0000000DNMps",
  eor_4 = "e0200000DNMps",
  sub_4 = "e0400000DNMps",
  rsb_4 = "e0600000DNMps",
  add_4 = "e0800000DNMps",
  adc_4 = "e0a00000DNMps",
  sbc_4 = "e0c00000DNMps",
  rsc_4 = "e0e00000DNMps",
  tst_3 = "e1100000NMp",
  teq_3 = "e1300000NMp",
  -- cmp_3 = "e1500000NMp",
  cmn_3 = "e1700000NMp",
  orr_4 = "e1800000DNMps",
  mov_3 = "e1a00000DMps",
  bic_4 = "e1c00000DNMps",
  mvn_3 = "e1e00000DMps",

  lsl_3 = "e1a00000DMws",
  lsr_3 = "e1a00020DMws",
  asr_3 = "e1a00040DMws",
  ror_3 = "e1a00060DMws",
  rrx_2 = "e1a00060DMs",

  -- Multiply and multiply-accumulate.
  mul_3 = "e0000090NMSs",
  mla_4 = "e0200090NMSDs",
  umaal_4 = "e0400090DNMSs",  -- v6
  mls_4 = "e0600090DNMSs",  -- v6T2
  umull_4 = "e0800090DNMSs",
  umlal_4 = "e0a00090DNMSs",
  smull_4 = "e0c00090DNMSs",
  smlal_4 = "e0e00090DNMSs",

  -- Halfword multiply and multiply-accumulate.
  smlabb_4 = "e1000080NMSD",  -- v5TE
  smlatb_4 = "e10000a0NMSD",  -- v5TE
  smlabt_4 = "e10000c0NMSD",  -- v5TE
  smlatt_4 = "e10000e0NMSD",  -- v5TE
  smlawb_4 = "e1200080NMSD",  -- v5TE
  smulwb_3 = "e12000a0NMS", -- v5TE
  smlawt_4 = "e12000c0NMSD",  -- v5TE
  smulwt_3 = "e12000e0NMS", -- v5TE
  smlalbb_4 = "e1400080NMSD", -- v5TE
  smlaltb_4 = "e14000a0NMSD", -- v5TE
  smlalbt_4 = "e14000c0NMSD", -- v5TE
  smlaltt_4 = "e14000e0NMSD", -- v5TE
  smulbb_3 = "e1600080NMS", -- v5TE
  smultb_3 = "e16000a0NMS", -- v5TE
  smulbt_3 = "e16000c0NMS", -- v5TE
  smultt_3 = "e16000e0NMS", -- v5TE

  -- Miscellaneous data processing instructions.
  clz_2 = "e16f0f10DM", -- v5T
  rev_2 = "e6bf0f30DM", -- v6
  rev16_2 = "e6bf0fb0DM", -- v6
  revsh_2 = "e6ff0fb0DM", -- v6
  sel_3 = "e6800fb0DNM", -- v6
  usad8_3 = "e780f010NMS", -- v6
  usada8_4 = "e7800010NMSD", -- v6
  rbit_2 = "e6ff0f30DM", -- v6T2
  movw_2 = "e3000000DW", -- v6T2
  movt_2 = "e3400000DW", -- v6T2
  -- Note: the X encodes width-1, not width.
  sbfx_4 = "e7a00050DMvX", -- v6T2
  ubfx_4 = "e7e00050DMvX", -- v6T2
  -- Note: the X encodes the msb field, not the width.
  bfc_3 = "e7c0001fDvX", -- v6T2
  bfi_4 = "e7c00010DMvX", -- v6T2

  -- Packing and unpacking instructions.
  pkhbt_3 = "e6800010DNM", pkhbt_4 = "e6800010DNMv", -- v6
  pkhtb_3 = "e6800050DNM", pkhtb_4 = "e6800050DNMv", -- v6
  sxtab_3 = "e6a00070DNM", sxtab_4 = "e6a00070DNMv", -- v6
  sxtab16_3 = "e6800070DNM", sxtab16_4 = "e6800070DNMv", -- v6
  sxtah_3 = "e6b00070DNM", sxtah_4 = "e6b00070DNMv", -- v6
  sxtb_2 = "e6af0070DM", sxtb_3 = "e6af0070DMv", -- v6
  sxtb16_2 = "e68f0070DM", sxtb16_3 = "e68f0070DMv", -- v6
  sxth_2 = "e6bf0070DM", sxth_3 = "e6bf0070DMv", -- v6
  uxtab_3 = "e6e00070DNM", uxtab_4 = "e6e00070DNMv", -- v6
  uxtab16_3 = "e6c00070DNM", uxtab16_4 = "e6c00070DNMv", -- v6
  uxtah_3 = "e6f00070DNM", uxtah_4 = "e6f00070DNMv", -- v6
  uxtb_2 = "e6ef0070DM", uxtb_3 = "e6ef0070DMv", -- v6
  uxtb16_2 = "e6cf0070DM", uxtb16_3 = "e6cf0070DMv", -- v6
  uxth_2 = "e6ff0070DM", uxth_3 = "e6ff0070DMv", -- v6

  -- Saturating instructions.
  qadd_3 = "e1000050DMN", -- v5TE
  qsub_3 = "e1200050DMN", -- v5TE
  qdadd_3 = "e1400050DMN",  -- v5TE
  qdsub_3 = "e1600050DMN",  -- v5TE
  -- Note: the X for ssat* encodes sat_imm-1, not sat_imm.
  ssat_3 = "e6a00010DXM", ssat_4 = "e6a00010DXMp", -- v6
  usat_3 = "e6e00010DXM", usat_4 = "e6e00010DXMp", -- v6
  ssat16_3 = "e6a00f30DXM", -- v6
  usat16_3 = "e6e00f30DXM", -- v6

  -- Parallel addition and subtraction.
  sadd16_3 = "e6100f10DNM", -- v6
  sasx_3 = "e6100f30DNM", -- v6
  ssax_3 = "e6100f50DNM", -- v6
  ssub16_3 = "e6100f70DNM", -- v6
  sadd8_3 = "e6100f90DNM", -- v6
  ssub8_3 = "e6100ff0DNM", -- v6
  qadd16_3 = "e6200f10DNM", -- v6
  qasx_3 = "e6200f30DNM", -- v6
  qsax_3 = "e6200f50DNM", -- v6
  qsub16_3 = "e6200f70DNM", -- v6
  qadd8_3 = "e6200f90DNM", -- v6
  qsub8_3 = "e6200ff0DNM", -- v6
  shadd16_3 = "e6300f10DNM", -- v6
  shasx_3 = "e6300f30DNM", -- v6
  shsax_3 = "e6300f50DNM", -- v6
  shsub16_3 = "e6300f70DNM", -- v6
  shadd8_3 = "e6300f90DNM", -- v6
  shsub8_3 = "e6300ff0DNM", -- v6
  uadd16_3 = "e6500f10DNM", -- v6
  uasx_3 = "e6500f30DNM", -- v6
  usax_3 = "e6500f50DNM", -- v6
  usub16_3 = "e6500f70DNM", -- v6
  uadd8_3 = "e6500f90DNM", -- v6
  usub8_3 = "e6500ff0DNM", -- v6
  uqadd16_3 = "e6600f10DNM", -- v6
  uqasx_3 = "e6600f30DNM", -- v6
  uqsax_3 = "e6600f50DNM", -- v6
  uqsub16_3 = "e6600f70DNM", -- v6
  uqadd8_3 = "e6600f90DNM", -- v6
  uqsub8_3 = "e6600ff0DNM", -- v6
  uhadd16_3 = "e6700f10DNM", -- v6
  uhasx_3 = "e6700f30DNM", -- v6
  uhsax_3 = "e6700f50DNM", -- v6
  uhsub16_3 = "e6700f70DNM", -- v6
  uhadd8_3 = "e6700f90DNM", -- v6
  uhsub8_3 = "e6700ff0DNM", -- v6

  -- Load/store instructions.
  str_2 = "e4000000DL", str_3 = "e4000000DL", str_4 = "e4000000DL",
  strb_2 = "e4400000DL", strb_3 = "e4400000DL", strb_4 = "e4400000DL",
  ldr_2 = "e4100000DL", ldr_3 = "e4100000DL", ldr_4 = "e4100000DL",
  ldrb_2 = "e4500000DL", ldrb_3 = "e4500000DL", ldrb_4 = "e4500000DL",
  strh_2 = "e00000b0DL", strh_3 = "e00000b0DL",
  ldrh_2 = "e01000b0DL", ldrh_3 = "e01000b0DL",
  ldrd_2 = "e00000d0DL", ldrd_3 = "e00000d0DL", -- v5TE
  ldrsb_2 = "e01000d0DL", ldrsb_3 = "e01000d0DL",
  strd_2 = "e00000f0DL", strd_3 = "e00000f0DL", -- v5TE
  ldrsh_2 = "e01000f0DL", ldrsh_3 = "e01000f0DL",

  ldm_2 = "e8900000oR", ldmia_2 = "e8900000oR", ldmfd_2 = "e8900000oR",
  ldmda_2 = "e8100000oR", ldmfa_2 = "e8100000oR",
  ldmdb_2 = "e9100000oR", ldmea_2 = "e9100000oR",
  ldmib_2 = "e9900000oR", ldmed_2 = "e9900000oR",
  stm_2 = "e8800000oR", stmia_2 = "e8800000oR", stmfd_2 = "e8800000oR",
  stmda_2 = "e8000000oR", stmfa_2 = "e8000000oR",
  stmdb_2 = "e9000000oR", stmea_2 = "e9000000oR",
  stmib_2 = "e9800000oR", stmed_2 = "e9800000oR",
  pop_1 = "e8bd0000R", push_1 = "e92d0000R",

  -- Branch instructions.
  -- b_1 = "ea000000B",
  bl_1 = "eb000000B",
  blx_1 = "e12fff30C",

  -- Miscellaneous instructions.
  nop_0 = "bf00bf00",
  mrs_1 = "e10f0000D",
  bkpt_1 = "e1200070K", -- v5T
  svc_1 = "ef000000T", swi_1 = "ef000000T",
  ud_0 = "e7f001f0",

  -- VFP instructions.
  ["vadd.f32_3"] = "ee300a00dnm",
  ["vadd.f64_3"] = "ee300b00Gdnm",
  ["vsub.f32_3"] = "ee300a40dnm",
  ["vsub.f64_3"] = "ee300b40Gdnm",
  ["vmul.f32_3"] = "ee200a00dnm",
  ["vmul.f64_3"] = "ee200b00Gdnm",
  ["vnmul.f32_3"] = "ee200a40dnm",
  ["vnmul.f64_3"] = "ee200b40Gdnm",
  ["vmla.f32_3"] = "ee000a00dnm",
  ["vmla.f64_3"] = "ee000b00Gdnm",
  ["vmls.f32_3"] = "ee000a40dnm",
  ["vmls.f64_3"] = "ee000b40Gdnm",
  ["vnmla.f32_3"] = "ee100a40dnm",
  ["vnmla.f64_3"] = "ee100b40Gdnm",
  ["vnmls.f32_3"] = "ee100a00dnm",
  ["vnmls.f64_3"] = "ee100b00Gdnm",
  ["vdiv.f32_3"] = "ee800a00dnm",
  ["vdiv.f64_3"] = "ee800b00Gdnm",

  ["vabs.f32_2"] = "eeb00ac0dm",
  ["vabs.f64_2"] = "eeb00bc0Gdm",
  ["vneg.f32_2"] = "eeb10a40dm",
  ["vneg.f64_2"] = "eeb10b40Gdm",
  ["vsqrt.f32_2"] = "eeb10ac0dm",
  ["vsqrt.f64_2"] = "eeb10bc0Gdm",
  ["vcmp.f32_2"] = "eeb40a40dm",
  ["vcmp.f64_2"] = "eeb40b40Gdm",
  ["vcmpe.f32_2"] = "eeb40ac0dm",
  ["vcmpe.f64_2"] = "eeb40bc0Gdm",
  ["vcmpz.f32_1"] = "eeb50a40d",
  ["vcmpz.f64_1"] = "eeb50b40Gd",
  ["vcmpze.f32_1"] = "eeb50ac0d",
  ["vcmpze.f64_1"] = "eeb50bc0Gd",

  vldr_2 = "ed100a00dl|ed100b00Gdl",
  vstr_2 = "ed000a00dl|ed000b00Gdl",
  vldm_2 = "ec900a00or",
  vldmia_2 = "ec900a00or",
  vldmdb_2 = "ed100a00or",
  vpop_1 = "ecbd0a00r",
  vstm_2 = "ec800a00or",
  vstmia_2 = "ec800a00or",
  vstmdb_2 = "ed000a00or",
  vpush_1 = "ed2d0a00r",

  ["vmov.f32_2"] = "eeb00a40dm|eeb00a00dY", -- #imm is VFPv3 only
  ["vmov.f64_2"] = "eeb00b40Gdm|eeb00b00GdY", -- #imm is VFPv3 only
  vmov_2 = "ee100a10Dn|ee000a10nD",
  vmov_3 = "ec500a10DNm|ec400a10mDN|ec500b10GDNm|ec400b10GmDN",

  vmrs_0 = "eef1fa10",
  vmrs_1 = "eef10a10D",
  vmsr_1 = "eee10a10D",

  ["vcvt.s32.f32_2"] = "eebd0ac0dm",
  ["vcvt.s32.f64_2"] = "eebd0bc0dGm",
  ["vcvt.u32.f32_2"] = "eebc0ac0dm",
  ["vcvt.u32.f64_2"] = "eebc0bc0dGm",
  ["vcvtr.s32.f32_2"] = "eebd0a40dm",
  ["vcvtr.s32.f64_2"] = "eebd0b40dGm",
  ["vcvtr.u32.f32_2"] = "eebc0a40dm",
  ["vcvtr.u32.f64_2"] = "eebc0b40dGm",
  ["vcvt.f32.s32_2"] = "eeb80ac0dm",
  ["vcvt.f64.s32_2"] = "eeb80bc0GdFm",
  ["vcvt.f32.u32_2"] = "eeb80a40dm",
  ["vcvt.f64.u32_2"] = "eeb80b40GdFm",
  ["vcvt.f32.f64_2"] = "eeb70bc0dGm",
  ["vcvt.f64.f32_2"] = "eeb70ac0GdFm",

  -- VFPv4 only:
  ["vfma.f32_3"] = "eea00a00dnm",
  ["vfma.f64_3"] = "eea00b00Gdnm",
  ["vfms.f32_3"] = "eea00a40dnm",
  ["vfms.f64_3"] = "eea00b40Gdnm",
  ["vfnma.f32_3"] = "ee900a40dnm",
  ["vfnma.f64_3"] = "ee900b40Gdnm",
  ["vfnms.f32_3"] = "ee900a00dnm",
  ["vfnms.f64_3"] = "ee900b00Gdnm",

  -- NYI: Advanced SIMD instructions.

  -- NYI: I have no need for these instructions right now:
  -- swp, swpb, strex, ldrex, strexd, ldrexd, strexb, ldrexb, strexh, ldrexh
  -- msr, nopv6, yield, wfe, wfi, sev, dbg, bxj, smc, srs, rfe
  -- cps, setend, pli, pld, pldw, clrex, dsb, dmb, isb
  -- stc, ldc, mcr, mcr2, mrc, mrc2, mcrr, mcrr2, mrrc, mrrc2, cdp, cdp2






  -------------------------
  --[[

  A = skip a word?
  D = ........ .....RRR
  N = ........ .rRRR...
  M = ........ ..iii... or ........ ..RRR...
  W = ......rR RR......
  w = .........wwwwwwww (#3)
  S = ....rRRR ........
  i = ........ iiii....

  -- non-positional :) below:

  n = ........ ....RRRR (#2)
  d = ....RRRR ........ (#1)
  m = ........ ....RRRR (#3)
  j = .iii.... iiiiiiii (#3)
  R = .......P rrrrrrrr (#1)

  ]]


  --[[ Basic data processing instructions. ]]
  ands_2 = "4000DN",
  add_3 = "1800DNW",
  adds_3 = "1800DNW",
  
  -- ADD{S}<c>.W <Rd>,<Rn>,#<const>
  --   11110[1:i]01000[1:S][4:Rn]
  --   0[3:imm][4:Rd][8:imm]
  -- ADD{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}
  --   11101011000[1:S][4:Rn]
  --   0[3:imm][4:Rd][2:imm][2:type][4:Rm]
  ["add.w_3"]  = "f100n,0000dj|eb00n,0000dm",
  ["adds.w_3"] = "f110n,0000dj|eb10n,0000dm",
  ["mul.w_3"]  = "fb00n,f000dm",
  ["mov_2"]    = "4600DN|2000Sw",
  ["mov.w_2"]  = "F04FA,0000Sw",

  ["cmp_2"]    = "4280DN|2800Sw",

  ["push_1"]   = "B400R",
  ["pop_1"]    = "BC00R",

  -- Multiply and multiply-accumulate.

  -- Halfword multiply and multiply-accumulate.

  -- Packing and unpacking instructions.

  -- Branch instructions.
  b_1 = "d000B",
  bx_1   = "4700N",
  it_1  = "BF08i",
  ite_1  = "BF04i",

  -- Miscellaneous
  ["nop_0"]   = "bf00",
}

do
  local t = {}
  for k,v in pairs(map_op) do
    if sub(v, -1) == "s" then
      local v2 = sub(v, 1, 2)..char(byte(v, 3)+1)..sub(v, 4, -2)
      t[sub(k, 1, -3).."s"..sub(k, -2)] = v2
    end
  end
  for k,v in pairs(t) do
    map_op[k] = v
  end
end

-- map_op = {}

map_op = {
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

local function parse_vr(expr, tp)
  local t, r = match(expr, "^([sd])([0-9]+)$")
  if t == tp then
    r = tonumber(r)
    if r <= 31 then
      if t == "s" then return shr(r, 1), band(r, 1) end
      return band(r, 15), shr(r, 4)
    end
  end
  werror("bad register name `"..expr.."'")
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

local function parse_vrlist(reglist)
  local ta, ra, tb, rb = match(reglist,
         "^{%s*([sd])([0-9]+)%s*%-%s*([sd])([0-9]+)%s*}$")
  ra, rb = tonumber(ra), tonumber(rb)
  if ta and ta == tb and ra and rb and ra <= 31 and rb <= 31 and ra <= rb then
    local nr = rb+1 - ra
    if ta == "s" then
      return shl(shr(ra,1),12)+shl(band(ra,1),22) + nr
    else
      return shl(band(ra,15),12)+shl(shr(ra,4),22) + nr*2 + 0x100
    end
  end
  werror("register list expected")
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

local function parse_imm12(imm)
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

local function parse_imm_new(imm)
  local n = tonumber(imm)
  if n then
    return n
  else
    waction("IMM_NEW", 0, imm)
    return 0
  end
end

local function parse_imm16(imm)
  imm = match(imm, "^#(.*)$")
  if not imm then werror("expected immediate operand") end
  local n = tonumber(imm)
  if n then
    if shr(n, 16) == 0 then return band(n, 0x0fff) + shl(band(n, 0xf000), 4) end
    werror("out of range immediate `"..imm.."'")
  else
    waction("IMM16", 32*16, imm)
    return 0
  end
end

local function parse_imm_load(imm, ext)
  local n = tonumber(imm)
  if n then
  --   if ext then
  --     if n >= -255 and n <= 255 then
  -- local up = 0x00800000
  -- if n < 0 then n = -n; up = 0 end
  -- return shl(band(n, 0xf0), 4) + band(n, 0x0f) + up
  --     end
  --   else
  --     if n >= -4095 and n <= 4095 then
  -- if n >= 0 then return n+0x00800000 end
  -- return -n
  --     end
    -- end
    -- werror("out of range immediate `"..imm.."'")
      return n
  else
    waction(ext and "IMML8" or "IMML12", 32768 + shl(ext and 8 or 12, 5), imm)
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

local function parse_load(params, nparams, n, op)
  local oplo = band(op, 255)
  local ext, ldrd = (oplo ~= 0), (oplo == 208)
  local d
  if (ldrd or oplo == 240) then
    d = band(shr(op, 12), 15)
    if band(d, 1) ~= 0 then werror("odd destination register") end
  end
  local pn = params[n]
  local p1, wb = match(pn, "^%[%s*(.-)%s*%](!?)$")
  local p2 = params[n+1]
  if not p1 then
    if not p2 then
      if match(pn, "^[<>=%-]") or match(pn, "^extern%s+") then
  local mode, n, s = parse_label(pn, false)
  waction("REL_"..mode, n + (ext and 0x1800 or 0x0800), s, 1)
  return op + 15 * 65536 + 0x01000000 + (ext and 0x00400000 or 0)
      end
      local reg, tailr = match(pn, "^([%w_:]+)%s*(.*)$")
      if reg and tailr ~= "" then
  local d, tp = parse_gpr(reg)
  if tp then
    waction(ext and "IMML8" or "IMML12", 32768 + 32*(ext and 8 or 12),
      format(tp.ctypefmt, tailr))
    return op + shl(d, 16) + 0x01000000 + (ext and 0x00400000 or 0)
  end
      end
    end
    werror("expected address operand")
  end
  if wb == "!" then op = op + 0x00200000 end
  if p2 then
    if wb == "!" then werror("bad use of '!'") end
    local p3 = params[n+2]
    op = op + shl(parse_gpr(p1), 16)
    local imm = match(p2, "^#(.*)$")
    if imm then
      local m = parse_imm_load(imm, ext)
      if p3 then werror("too many parameters") end
      op = op + m + (ext and 0x00400000 or 0)
    else
      local m, neg = parse_gpr_pm(p2)
      if ldrd and (m == d or m-1 == d) then werror("register conflict") end
      op = op + m + (neg and 0 or 0x00800000) + (ext and 0 or 0x02000000)
      if p3 then op = op + parse_shift(p3) end
    end
  else
    local p1a, p2 = match(p1, "^([^,%s]*)%s*(.*)$")
    op = op + shl(parse_gpr(p1a), 16) + 0x01000000
    if p2 ~= "" then
      local imm = match(p2, "^,%s*#(.*)$")
      if imm then
  local m = parse_imm_load(imm, ext)
  op = op + m + (ext and 0x00400000 or 0)
      else
  local p2a, p3 = match(p2, "^,%s*([^,%s]*)%s*,?%s*(.*)$")
  local m, neg = parse_gpr_pm(p2a)
  if ldrd and (m == d or m-1 == d) then werror("register conflict") end
  op = op + m + (neg and 0 or 0x00800000) + (ext and 0 or 0x02000000)
  if p3 ~= "" then
    if ext then werror("too many parameters") end
    op = op + parse_shift(p3)
  end
      end
    else
      if wb == "!" then werror("bad use of '!'") end
      op = op + (ext and 0x00c00000 or 0x00800000)
    end
  end
  return op
end

local function parse_vload(q)
  local reg, imm = match(q, "^%[%s*([^,%s]*)%s*(.*)%]$")
  if reg then
    local d = shl(parse_gpr(reg), 16)
    if imm == "" then return d end
    imm = match(imm, "^,%s*#(.*)$")
    if imm then
      local n = tonumber(imm)
      if n then
  if n >= -1020 and n <= 1020 and n%4 == 0 then
    return d + (n >= 0 and n/4+0x00800000 or -n/4)
  end
  werror("out of range immediate `"..imm.."'")
      else
  waction("IMMV8", 32768 + 32*8, imm)
  return d
      end
    end
  else
    if match(q, "^[<>=%-]") or match(q, "^extern%s+") then
      local mode, n, s = parse_label(q, false)
      waction("REL_"..mode, n + 0x2800, s, 1)
      return 15 * 65536
    end
    local reg, tailr = match(q, "^([%w_:]+)%s*(.*)$")
    if reg and tailr ~= "" then
      local d, tp = parse_gpr(reg)
      if tp then
  waction("IMMV8", 32768 + 32*8, format(tp.ctypefmt, tailr))
  return shl(d, 16)
      end
    end
  end
  werror("expected address operand")
end

------------------------------------------------------------------------------

-- Handle opcodes defined with template strings.
local function parse_template(params, template, nparams, pos)
  local op = tonumber(sub(template, 1, 4), 16)
  local n = 1
  local vr = "s"

  -- Process each character.
  -- TCR_LOG('-->' .. template .. ' ' .. tonumber(nparams or 0) .. ' ' .. pos)
  for p in gmatch(sub(template, 5), ".") do
    local q = params[n]

    if p == "n" then
      op = op + shl(parse_gpr(params[2]), 0);
    elseif p == "d" then
      op = op + shl(parse_gpr(params[1]), 8);
    elseif p == "m" then
      op = op + shl(parse_gpr(params[3]), 0);
    elseif p == "j" then
      local imm = match(params[3], "^#(.*)$")
      if imm then
        val = parse_imm12(imm)
        op = op + shl(band(shr(val, 8), 0xfff), 12) + shl(band(val, 0xff), 0)
      else
      	werror("expected immediate literal")
      end
    elseif p == "R" then
      op = op + parse_reglist(params[1]); n = n + 1

    elseif p == "D" then
      op = op + shl(parse_gpr(q), 0); n = n + 1
    elseif p == "N" then
      op = op + shl(parse_gpr(q), 3); n = n + 1
    elseif p == "M" then
      local imm = match(q, "^#(.*)$")
      if imm then
        op = op + shl(parse_imm12(imm), 3)
      else
        op = op + shl(parse_gpr(q), 3)
      end
      n = n + 1
    elseif p == "S" then
      op = op + shl(parse_gpr(q), 8); n = n + 1
    elseif p == "i" then
      if q == "le" then
        op = op + shl(0xD, 4); n = n + 1
      else
        assert(false)
      end
    elseif p == "W" then
      local imm = match(q, "^#(.*)$")
      if imm then
        op = op + shl(parse_imm12(imm), 6)
      else
        op = op + shl(parse_gpr(q), 6)
      end
      n = n + 1
    elseif p == "w" then
      local imm = match(q, "^#(.*)$")
      if imm then
        op = op + parse_imm12(imm)
      else
        op = op + parse_gpr(q)
      end
      n = n + 1
    elseif p == "B" then
      local mode, n, s = parse_label(q, false)
      waction("REL_"..mode, n, s, 1)
    elseif p == "A" then
      n = n + 1




    elseif p == "M" then
      op = op + parse_gpr(q); n = n + 1
    elseif p == "d" then
      local r,h = parse_vr(q, vr); op = op+shl(r,12)+shl(h,22); n = n + 1
    elseif p == "n" then
      local r,h = parse_vr(q, vr); op = op+shl(r,16)+shl(h,7); n = n + 1
    elseif p == "m" then
      local r,h = parse_vr(q, vr); op = op+r+shl(h,5); n = n + 1
    elseif p == "P" then
      local imm = match(q, "^#(.*)$")
      if imm then
        op = op + parse_imm12(imm) + 0x02000000
      else
        op = op + parse_gpr(q)
      end
      n = n + 1
    elseif p == "p" then
      op = op + parse_shift(q, true); n = n + 1
    elseif p == "L" then
      op = parse_load(params, nparams, n, op)
    elseif p == "l" then
      op = op + parse_vload(q)
    elseif p == "C" then -- blx gpr vs. blx label.
      if match(q, "^([%w_]+):(r1?[0-9])$") or match(q, "^r(1?[0-9])$") then
  op = op + parse_gpr(q)
      else
  if op < 0xe0000000 then werror("unconditional instruction") end
  local mode, n, s = parse_label(q, false)
  waction("REL_"..mode, n, s, 1)
  op = 0xfa000000
      end
    elseif p == "F" then
      vr = "s"
    elseif p == "G" then
      vr = "d"
    elseif p == "o" then
      local r, wb = match(q, "^([^!]*)(!?)$")
      op = op + shl(parse_gpr(r), 16) + (wb == "!" and 0x00200000 or 0)
      n = n + 1
    elseif p == "r" then
      op = op + parse_vrlist(q); n = n + 1
    elseif p == "v" then
      op = op + parse_imm(q, 5, 7, 0, false); n = n + 1
    elseif p == "w" then
      local imm = match(q, "^#(.*)$")
      if imm then
  op = op + parse_imm(q, 5, 7, 0, false); n = n + 1
      else
  op = op + shl(parse_gpr(q), 8) + 16
      end
    elseif p == "X" then
      op = op + parse_imm(q, 5, 16, 0, false); n = n + 1
    elseif p == "Y" then
      local imm = tonumber(match(q, "^#(.*)$")); n = n + 1
      if not imm or shr(imm, 8) ~= 0 then
  werror("bad immediate operand")
      end
      op = op + shl(band(imm, 0xf0), 12) + band(imm, 0x0f)
    elseif p == "K" then
      local imm = tonumber(match(q, "^#(.*)$")); n = n + 1
      if not imm or shr(imm, 16) ~= 0 then
  werror("bad immediate operand")
      end
      op = op + shl(band(imm, 0xfff0), 4) + band(imm, 0x000f)
    elseif p == "T" then
      op = op + parse_imm(q, 24, 0, 0, false); n = n + 1
    elseif p == "s" then
      -- Ignored.
    else
      assert(false)
    end
  end
  wputpos(pos, op)
end

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
        values[p] = parse_imm12(imm)
        if values[p] >= math.pow(2, bits[p]) then
          werror('immediate operand larger than ' .. bits[p] .. ' bits')
        end
      elseif bits['H'] then
        -- fun encoding time!
        local val = parse_imm12(imm)
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
        values[p] = parse_imm12(imm)
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
            local m = parse_imm_load(imm, ext)
            local bitlen = bits['i'] or shl(bits['f'] or 0, 2)
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
              local m = parse_imm_load(imm, ext)
              local bitlen = bits['i'] or shl(bits['f'] or 0, 2)
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

-- local oplo = band(op, 255)
-- local ext, ldrd = (oplo ~= 0), (oplo == 208)
-- local d
-- if (ldrd or oplo == 240) then
--   d = band(shr(op, 12), 15)
--   if band(d, 1) ~= 0 then werror("odd destination register") end
-- end
-- local pn = params[n]
-- local p1, wb = match(pn, "^%[%s*(.-)%s*%](!?)$")
-- local p2 = params[n+1]
-- if not p1 then
--   if not p2 then
--     if match(pn, "^[<>=%-]") or match(pn, "^extern%s+") then
-- local mode, n, s = parse_label(pn, false)
-- waction("REL_"..mode, n + (ext and 0x1800 or 0x0800), s, 1)
-- return op + 15 * 65536 + 0x01000000 + (ext and 0x00400000 or 0)
--     end
--     local reg, tailr = match(pn, "^([%w_:]+)%s*(.*)$")
--     if reg and tailr ~= "" then
-- local d, tp = parse_gpr(reg)
-- if tp then
--   waction(ext and "IMML8" or "IMML12", 32768 + 32*(ext and 8 or 12),
--     format(tp.ctypefmt, tailr))
--   return op + shl(d, 16) + 0x01000000 + (ext and 0x00400000 or 0)
-- end
--     end
--   end
--   werror("expected address operand")
-- end
-- if wb == "!" then op = op + 0x00200000 end
-- if p2 then
--   if wb == "!" then werror("bad use of '!'") end
--   local p3 = params[n+2]
--   op = op + shl(parse_gpr(p1), 16)
--   local imm = match(p2, "^#(.*)$")
--   if imm then
--     local m = parse_imm_load(imm, ext)
--     if p3 then werror("too many parameters") end
--     op = op + m + (ext and 0x00400000 or 0)
--   else
--     local m, neg = parse_gpr_pm(p2)
--     if ldrd and (m == d or m-1 == d) then werror("register conflict") end
--     op = op + m + (neg and 0 or 0x00800000) + (ext and 0 or 0x02000000)
--     if p3 then op = op + parse_shift(p3) end
--   end
-- else
--   local p1a, p2 = match(p1, "^([^,%s]*)%s*(.*)$")
--   op = op + shl(parse_gpr(p1a), 16) + 0x01000000
--   if p2 ~= "" then
--     local imm = match(p2, "^,%s*#(.*)$")
--     if imm then
-- local m = parse_imm_load(imm, ext)
-- op = op + m + (ext and 0x00400000 or 0)
--     else
-- local p2a, p3 = match(p2, "^,%s*([^,%s]*)%s*,?%s*(.*)$")
-- local m, neg = parse_gpr_pm(p2a)
-- if ldrd and (m == d or m-1 == d) then werror("register conflict") end
-- op = op + m + (neg and 0 or 0x00800000) + (ext and 0 or 0x02000000)
-- if p3 ~= "" then
--   if ext then werror("too many parameters") end
--   op = op + parse_shift(p3)
-- end
--     end
--   else
--     if wb == "!" then werror("bad use of '!'") end
--     op = op + (ext and 0x00c00000 or 0x00800000)
--   end
-- end

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

