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
  //for disjoint sets
  Node * next; //next node
  int setObj = -1; //set object index
  //
  Node(int num){id=num;}
};

class Graph{
public:
  int time;
  std::vector<Node> nodes;
  std::queue<Node> q;
  int getNode(int);
  int getNodeT(int, std::vector<Node>);
  std::vector<Node> transpose();
  void DFS();
  void DFSvisit(Node&);
  void BFS(Node);
};

#endif
