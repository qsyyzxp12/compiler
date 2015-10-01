All:
	g++ AcDc.cpp -g -o AcDc; find . | grep ".*\.\(c\|h\|cpp\)" | xargs etags -f tags # generate emacs tags
originaltest:
	./AcDc ../test/sample1.ac out1
	./AcDc ../test/sample2.ac out2
	./AcDc ../test/sample3.ac out3
	./AcDc ../test/sample4.ac out4
	./AcDc ../test/sample5.ac out5
original:
	gcc AcDc.c -g -o originalAcDc
testsimple:
	./AcDc ../test/testsimple.ac outs
test1: AcDc
	./AcDc ../test/test1-variable-length.ac test1
test2: AcDc test2
	./AcDc ../test/test2-Mul-Div.ac test2
test3: AcDc test3
	./AcDc ../test/test3-Mul-Div-Float.ac test3
test4: AcDc test4
	./AcDc ../test/test4-Constant-Folding test4
test5: AcDc
	./AcDc ../test/test5-Mul-Div-Hard.ac test5
clean:
	rm AcDc test1 test2
