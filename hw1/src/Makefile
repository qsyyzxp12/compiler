All:
	g++ AcDc.cpp -g -o AcDc
originaltest:
	./AcDc ../test/sample1.ac out1
	./AcDc ../test/sample2.ac out2
	./AcDc ../test/sample3.ac out3
	./AcDc ../test/sample4.ac out4
	./AcDc ../test/sample5.ac out5
test1: AcDc
	./AcDc ../test/test1-variable-length.ac test1
test2: AcDc
	./AcDc ../test/test2-Mul-Div.ac test2
clean:
	rm AcDc
