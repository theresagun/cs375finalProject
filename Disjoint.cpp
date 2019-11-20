#include "Disjoint.h"
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

void disjointSet::makeSet(Node n){
  //make new LL, add to set
  S.push_back(disjointLL(n));
}

int disjointSet::findSet(int n){
  //returns representative, which is first element in disjointLL
  return S[n].head->id;
}

void disjointSet::unionSets(Node x, Node y){
  //adds set y to end of set x, deletes set y
  Node xSet = findSet(x.id);
  Node ySet = findSet(y.id);
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

vector<vector<int>> disjointSet::connectedComponents(Graph g){
  //iterate through nodes, make set of each
  for(int i = 0; i < g.nodes.size(); i++){
    makeSet(g.nodes[i]);
  }
  //for each edge, union sets if necessary
  for(int i = 0; i < g.nodes.size(); i++){
    for(int j = 0; j < g.nodes[i].adjacents.size(); j++){
      if(findSet(g.nodes[i].id) == findSet(g.nodes[i].adjacents[j])){
        unionSets(g.nodes[i], g.getNode(g.nodes[i].adjacents[j]));
      }
    }
  }
  //return vector of vectors of ints (ids)
  vector<vector<int>> retVal;
  vector<int> toPush;
  Node * temp;
  //iterate through set of LLs
  for(int i = 0; i < S.size(); i++){
    //iterate through LL
    temp = S[i].head;
    while(temp != nullptr){
      toPush.push_back(temp->id);
      temp = temp->next;
    }
    retVal.push_back(toPush);
    toPush.clear();
  }
  return retVal;
}
