CFLAGS=-Wall -Wextra -DDEBUG -g -std=c++14
proj=finalProject
D=disjoint2
all: $(proj).o Graph.o $(D).o
	g++ $(proj).o Graph.o $(D).o -o $(proj)

$(proj).o: $(proj).cpp
	g++ -c $(CFLAGS) $(proj).cpp

$(D).o: $(D).cpp $(D).h
	g++ -c $(CFLAGS) $(D).cpp

Graph.o: Graph.cpp Graph.h
	g++ -c $(CFLAGS) Graph.cpp

run: all
	./$(proj) large2.txt dense

clean:
	rm -rf *.o $(proj) $(D) Graph
