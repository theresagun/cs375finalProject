CFLAGS=-Wall -Wextra -DDEBUG -g -std=c++14
proj=finalProject

all: $(proj).o Graph.o
	g++ $(proj).o Graph.o -o $(proj)

$(proj).o: $(proj).cpp
	g++ -c $(CFLAGS) $(proj).cpp

Graph.o: Graph.cpp Graph.h
	g++ -c $(CFLAGS) Graph.cpp

run: all
	./$(proj) testinput.txt

clean:
	rm -rf *.o $(proj)
