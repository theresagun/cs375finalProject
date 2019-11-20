#ifndef DISJOINT_TG
#define DISJOINT_TG
#include <cstdlib>
#include <vector>
#include "Graph.h"

// class disjointNode{
//   //linked list node
// public:
//   int setMember; //data
//   disjointNode * next; //next node
//   disjointSet * setObj; //set object
//   disjointNode(int n){
//     setMember = n;
//     next = nullptr;
//     setObj = nullptr;
//   }
// };

class disjointLL{
  //linked list implementation
public:
  Node * head;
  Node * tail;
  disjointLL(Node n){
    //disjointNode dn = disjointNode(n.id);
    head = tail = &n;
  }
  void insert(Node);
};

class disjointSet{
public:
  std::vector<disjointLL> S;
  void makeSet(Node);
  int findSet(int);
  void unionSets(Node, Node);
  std::vector<std::vector<int>> connectedComponents(Graph);
};

#endif
