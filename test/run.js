#!/usr/bin/env node

var spawn = require('child_process').spawn

function collect (fn) {
	var stream = new (require('stream').Writable)
	var bufs = [];
	stream._write = function (data, enc, cb) { bufs.push(data); cb() }
	stream.on('pipe', function (s) { s.on('end', function () { fn(Buffer.concat(bufs)); }) })
	return stream;
}

var ret = spawn('qemu-system-arm', ['-M', 'lm3s6965evb', '--kernel', 'main.bin', '-no-reboot', '-nographic'])

ret.on('error', function (err) {
		console.error(err);
		process.exit(1);
});
ret.stderr.pipe(process.stderr);
ret.stdout.pipe(process.stdout);

ret.stdout.once('data', function () {
	setTimeout(function () {
		spawn('kill', ['-9', ret.pid])
	}, process.argv[2] ? Number(process.argv[2]) : 10);
})
