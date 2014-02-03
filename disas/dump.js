#!/usr/bin/env node

var spawn = require('child_process').spawn

function collect (fn) {
	var stream = new (require('stream').Writable)
	var bufs = [];
	stream._write = function (data, enc, cb) { bufs.push(data); cb() }
	stream.on('pipe', function (s) { s.on('end', function () { fn(Buffer.concat(bufs)); }) })
	return stream;
}

var ret = spawn('arm-none-eabi-objdump', ['-D', 'main']);
ret.stdout.pipe(collect(function (buf) {
	buf = String(buf)
	console.log(buf.match(/test>:\s*\n([\s\S]*?)\n\n/)[1]);
}))