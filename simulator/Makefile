all:
	g++ -c -o A4988Simulator A4988Simulator.cc -D DO_SMOKE_TEST
	g++ A4988Simulator.o -o smoke_test smoke_test.cc -D DO_SMOKE_TEST
	./smoke_test
