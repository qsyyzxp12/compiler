All:
	g++ AcDc.cpp -g -o AcDc; find . | grep ".*\.\(c\|h\|cpp\)" | xargs etags -f tags # generate emacs tags
originaltest: All
	./AcDc ../test/sample1.ac out1
	./AcDc ../test/sample2.ac out2
	./AcDc ../test/sample3.ac out3
	./AcDc ../test/sample4.ac out4
	./AcDc ../test/sample5.ac out5
original: All
	gcc AcDc.c -g -o originalAcDc
testsimple: All
	./AcDc ../test/testsimple.ac outs; dc outs
test1: All
	./AcDc ../test/test1-variable-length.ac test1; dc test1
test2: All
	./AcDc ../test/test2-Mul-Div.ac test2; dc test2
test3: All
	./AcDc ../test/test3-Mul-Div-Float.ac test3; dc test3
test4: All 
	./AcDc ../test/test4-Constant-Folding test4.out; dc test4.out
test5: All
	./AcDc ../test/test5-Mul-Div-Hard.ac t5.dc; dc t5.dc
test6: All
	./AcDc ../test/test6-constantFolding-Hard.ac test6; dc test6
test7: All
	./AcDc ../test/test7-Final-Test.ac test7; dc test7
test8: All
	./AcDc ../test/test8-Fringe-Condition.ac test8; dc test8
test9: All
	./AcDc ../test/test9-simple test9; dc test9
test10: All
	./AcDc ../test/test10-real-simple test10; dc test10
clean:
	rm AcDc test1 test2
