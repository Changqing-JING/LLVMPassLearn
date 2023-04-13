print:
	opt -load-pass-plugin build/lib/libAddConst.so -passes="print<add-const>" -disable-output examples/foo.ll

run:
	opt -load-pass-plugin build/lib/libAddConst.so -passes="add-const" -S -o build/foo2.ll  examples/foo.ll