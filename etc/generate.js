var ins = require('./instructions.json');

function luadump (arg) {
	if (Array.isArray(arg)) {
		return JSON.stringify(arg).replace(/,/g, ', ').replace(/\[/g, '{').replace(/\]/g, '}')
	} else if (typeof arg == 'object') {
		var str = '{\n';
		for (var k in arg) {
			str += '  [' + JSON.stringify(k) + '] = ' + luadump(arg[k])
			  .replace(/\{\{/g, '{\n    {')
			  .replace(/\}\}/g, '}\n  }')
			  .replace(/\}, \{/g, '\},\n    \{')
			  + ',\n'
		}
		str += '}'
		return str;
	} else {
		return JSON.stringify(arg);
	}
}

Array.prototype.group = function (obj) {
	obj = obj || {};
	this.forEach(function (entry) {
		(obj[entry.key] || (obj[entry.key] = [])).push(entry.value);
	});
	return obj
}

var out = Object.keys(ins).map(function (name) {
	var op = ins[name][1].replace(/<t>/g, '').split(/[\s,]+/)
	var id = op[0].replace(/<.*?>/g, '');
	return {
		key: id + '_' + (op.length - 1),
		value: [op.slice(1).map(function (str) {
			return str.replace(/<[A-Z]([a-z])\w*>/g, '$1').replace(/<([a-z])\w*>/g, '$1')
		}).join('')].concat(ins[name].slice(2))
	};
}).group();

console.log(luadump(out))