#!/usr/bin/env node

var spawn = require('child_process').spawn

function collect (fn) {
	var stream = new (require('stream').Writable)
	var bufs = [];
	stream._write = function (data, enc, cb) { bufs.push(data); cb() }
	stream.on('pipe', function (s) { s.on('end', function () { fn(Buffer.concat(bufs)); }) })
	return stream;
}

var name = process.argv[2] || 'test';
var showasm = !!process.argv[3]

var ret = spawn('arm-none-eabi-objdump', ['-D', 'main', '-Mforce-thumb']);
ret.stdout.pipe(collect(function (buf) {
	buf = String(buf)
	var i = 0;
	buf.match(new RegExp(name + ">:\\s*\\n([\\s\\S]*?)\\n\\n"))[1].split(/\n/).map(function (out) {
		var line = out.substr(10).split(/\s{2,}/)
		// console.log(';;;', line + (showasm ? '\t#' + out.substr(21) : ''))
		console.log(';;;', line.shift(), '\t#', line.join(' '));
	// 	out = '';
	})
}))
