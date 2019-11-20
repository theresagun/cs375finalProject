#include "Disjoint.h"
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

void disjointSet::makeSet(Node n){
  //make new LL, add to set
  S.push_back(disjointLL(n));
}

Node disjointSet::findSet(Node n){
  //returns representative, which is first element in disjointLL
  return *(S[n.setObj].head);
}

void disjointSet::unionSets(Node x, Node y){
  //adds set y to end of set x, deletes set y
  Node xSet = findSet(x);
  Node ySet = findSet(y);
  int xIndex = 0;
  int yIndex = 0;
  for(int i = 0; i < S.size(); i++){
    //if head is this we found it
    if(S[i].head->id == xSet.id) xIndex = i;
    if(S[i].head->id == ySet.id) yIndex = i;
  }
  //put the rest of y onto x
  while(S[yIndex].head != nullptr){
    S[xIndex].insert(S[yIndex].head->id);
    S[yIndex].head = S[yIndex].head->next;
  }
  //delete y
  S.erase(S.begin() + yIndex);
}

void disjointLL::insert(Node n){
//  disjointNode newN = disjointNode(n.id);
  //insert at end
  tail->next = &n;
  //update tail
  tail = &n;
}
