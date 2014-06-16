#!/usr/bin/env node

var spawn = require('child_process').spawn

function collect (fn) {
	var stream = new (require('stream').Writable)
	var bufs = [];
	stream._write = function (data, enc, cb) { bufs.push(data); cb() }
	stream.on('pipe', function (s) { s.on('end', function () { fn(Buffer.concat(bufs)); }) })
	return stream;
}

var ret = spawn('qemu-system-arm', ['-M', 'lm3s6965evb', '--kernel', 'main.bin', '--serial', 'stdio', '-no-reboot'])
ret.stdout.pipe(collect(function (buf) {
	// String(buf).split(/\n/).forEach(function (line) {
		// if (String(line).match(/^\d+:/)) {
			// console.log(String(line).replace(/^\d+:\s+/, ''));
		// }
	// });
	process.stdout.write(buf);
}))

ret.stdout.once('data', function () {
	setTimeout(function () {
		spawn('kill', ['-9', ret.pid])
	}, process.argv[2] ? Number(process.argv[2]) : 10);
})