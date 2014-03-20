var fs = require('fs');

var dump = fs.readFileSync(__dirname + '/instrtable.cpp', 'utf-8').split(/\n/);

var instrs = dump.slice(2482, 2791)
	.filter(function (line) {
		return line.match(/^\s*\{.*\},?\s*$/);
	}).map(function (line) {
		return eval(line.replace(/\{/, '[').replace(/(\w+) \}\s*,?/, '"$1" ]'));
	});

Array.prototype.unzip = function (obj) {
	obj = obj || {};
	this.forEach(function (entry) {
		obj[entry.key] = entry.value;
	})
	return obj;
}

var ops = dump.slice(4, 2480)
	.join('\n').match(/int (\w+)[\s\S]+?\n\}/g)
	.map(function (op) {
		return {
			key: op.match(/int (\w+)/)[1],
			value: (op.match(/case (\d+):[\s\S]+?FormatInstruction\("(.*?)"/g) || []).map(function (c) {
				return c.match(/case (\d+):[\s\S]+?FormatInstruction\("(.*?)"/).slice(1, 3)
			}).map(function (c) {
				return {key: Number(c[0]), value: c[1]}
			}).unzip([])
		};
	})
	.unzip({})

ops.Branch[2] = ops.Branch[1];

var json = instrs.map(function (line) {
	var op = ops[line[5]];
	if (!op) throw 'Weird op: ' + line[5];
	var format = op[line[4]];
	if (!format) {
		console.error('Weird format: ' + line[5] + ' => ' + line[4]);
		console.log(op);
		return '';
	}

	// console.error(format.split(/[\s,]+/))
	var type = line[5];
	line.splice(1, 0, format)
	line.splice(!line[4] ? 3 : 4, 5)
	return {
		key: type,
		value: line
	}

	// return '[' + JSON.stringify(line[0]) + '] = ' + luadump([/*line[0]*/].concat(line[3] ? [line[1], line[2]] : [line[1]]));
}).unzip({});

console.log(JSON.stringify(json, null, '  '));