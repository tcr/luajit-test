#!/usr/bin/env node

var assert = require('assert');

if (process.argv.length <= 2) {
	console.error('Usage: disas.js fe57 0000')
	process.exit(1);
}

var fs = require('fs')

var codes = fs.readFileSync(__dirname + '/luajit/dynasm/dasm_thumb.lua', 'utf-8').split(/\n/).map(function (str) {
	return str.match(/^\s*\["([^"]+)"\] = "([^"]+)"/m)
}).filter(function (instr) {
	return instr;
}).map(function (instr) {
	return {name: instr[1], code: instr[2].split('|') };
});

var match = process.argv.slice(2).map(function (a) {
	var ret = ('0000000000000000' + parseInt(a, 16).toString(2)).slice(-16);
	assert.equal(ret.length, 16);
	return ret;
}).join('');

function tab (str) {
	return (str + '                ').slice(0, 14);
}

console.log(tab('[INPUT]'), match);
codes.forEach(function (instr) {
	instr.code.forEach(function (code) {
		code = code.replace(/^.*:/, '');
		if (code.length != match.length) {
			return;
		}

		for (var i = 0; i < code.length; i++) {
			if ((code[i] == '1' || code[i] == '0') && code[i] != match[i]) {
				return;
			}
		}

		console.log(tab(instr.name), code);
	});
})
