CC:=clang++
LD := clang++
CFLAGS:=-I. -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LDFLAGS := -I.	-std=c++1y -stdlib=libc++ -lc++abi
DEPS := DataReader.h Graph.h
OBJ := main.o DataReader.o Graph.o
TEST_OBJ := catch.o test-datareader.o test-graph.o DataReader.o Graph.o

%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(LD) -o $@ $^ $(LDFLAGS)

test: $(TEST_OBJ)
	$(LD) -o $@ $^ $(LDFLAGS)

test-datareader.o: tests/test-datareader.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

test-graph.o: tests/test-graph.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

catch.o: tests/catchmain.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: all test clean

clean:
	rm main *.o
