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
  bool visited;
  bool added;
  //for disjoint sets
  Node * next; //next node
  int setObj = -1; //set object index
  //
  Node(int num){id=num; added=false;}
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
  void BFS(Node, std::vector<Node> &);
  std::vector<std::vector<Node>> BFSscc();
  std::vector<std::vector<Node>> DFST();
  void DFSvisitT(Node &node, std::vector<Node> &t, std::vector<Node> &s);
};

#endif
