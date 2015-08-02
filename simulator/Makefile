CCFLAGS = -Wall -I../

all:
	g++ $(CCFLAGS) -c -o A4988Simulator.o A4988Simulator.cc -D DO_SMOKE_TEST
	g++ $(CCFLAGS) A4988Simulator.o -o smoke_test smoke_test.cc -D DO_SMOKE_TEST
	./smoke_test
