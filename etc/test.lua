local bit32 = require('bit32')

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
			op = op + bit32.lshift(1, #word)
		elseif bit ~= '0' then
			op = op + bit32.lshift(bit32.band(values[bit], 1), #word)
			values[bit] = bit32.rshift(values[bit], 1)
		end
		op = op / 2
	end
	return bit32.bor(op, 0)
end






local template = {"Cdni", "0001110iiinnnddd"}

local bits = {}
for i=2,#template do
	parse_op_word(template[i], bits)
end

for k, v in pairs(bits) do
	print(k, v)
end

local values = {}
for k,v in pairs(bits) do
	values[k] = 0xFFFF
end
values['d'] = 5
print(populate_op_word(template[2], values))
local values = {}
for k,v in pairs(bits) do
	values[k] = 0
end
print(populate_op_word(template[2], values))