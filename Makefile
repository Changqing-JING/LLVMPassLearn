run:
	opt -load-pass-plugin build/lib/libAddConst.so -passes="print<add-const>" -disable-output examples/foo.ll