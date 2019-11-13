#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <cstdlib>
#include <string>
#include <queue>
class Node{
public:
  int id;
  std::vector<int> adjacents;
  std::string color;
  int parent;
  int d;
  int f;
  Node(int num){id=num;}
};

class Graph{
public:
  int time;
  std::vector<Node> nodes;
  std::queue<Node> q;
  Node getNode(int);
  void DFS();
  void DFSvisit(Node);
  void BFS();
};

#endif
