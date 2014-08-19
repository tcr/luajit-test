function js_new (f, ...)
	print('should NOT be nil:', type(f))
end
js_new({}, 'null')
