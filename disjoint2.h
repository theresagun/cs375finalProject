#ifndef DISJOINT2_TG
#define DISJOINT2_TG
#include <cstdlib>
#include <vector>
#include "Graph.h"

class disjoint{
public:
  std::vector<std::vector<Node>> S;
  void makeSet(Node);
  Node * findSet(Node);
  void unionSets(Node, Node);
};

#endif
