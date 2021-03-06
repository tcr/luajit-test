#!/usr/bin/env node

var spawn = require('child_process').spawn

function collect (fn) {
	var stream = new (require('stream').Writable)
	var bufs = [];
	stream._write = function (data, enc, cb) { bufs.push(data); cb() }
	stream.on('pipe', function (s) { s.on('end', function () { fn(Buffer.concat(bufs)); }) })
	return stream;
}

var ret = spawn('./bin/qemu-system-arm-darwin', ['-m', '1024K', '-M', 'lm3s6965evb', '--kernel', process.argv[2], '-no-reboot', '-nographic'].concat(
	(process.argv.indexOf('-d') > -1 ? ['-s', '-S'] : []),
	(process.argv.indexOf('-v') > -1 ? ['-d', 'cpu,exec,in_asm'] : [])
));

ret.on('error', function (err) {
		console.error(err);
		process.exit(1);
});
ret.stderr.pipe(process.stderr);
ret.stdout.pipe(process.stdout);

ret.stdout.on('data', function (d) {
	d = String(d);
	if (d.indexOf('# terminate.') > -1) {
		spawn('kill', ['-9', ret.pid]).on('exit', function (c) {
			process.exit(0);
		})
	}
})

if (process.argv[3] != '-d') {
	ret.stdout.once('data', function () {
		setTimeout(function () {
			spawn('kill', ['-9', ret.pid])
		}, process.argv[3] ? Number(process.argv[3]) : 1000000);
	})
}
