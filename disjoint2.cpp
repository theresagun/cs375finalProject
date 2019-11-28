#include <cstdlib>
#include <iostream>
#include <vector>

#include "Graph.h"
#include "disjoint2.h"

using namespace std;

void disjoint::makeSet(Node x){
  /*make new set, add to larger set*/
  //make new set of just this node
  vector<Node> newSet;
  newSet.push_back(x);
  //insert set to set of sets
  S.push_back(newSet);
}

Node * disjoint::findSet(Node x){
  /*returns representative of set with this node*/
  //check if in sets in larger set
  for(int i = 0; i < S.size(); i++){
    //checks elements
    for(int j = 0; j < S[i].size(); j++){
      if(S[i][j].id == x.id){
        //if it is in the set, return the first item in this set
        return &S[i][0];
      }
    }
  }
  //if not in set already
  return nullptr;
}

void disjoint::unionSets(Node x, Node y){
  /*join sets that nodes x and y belong in*/
  //find representative of each set
  Node * xRep = findSet(x);
  Node * yRep = findSet(y);
  if(xRep == nullptr || yRep == nullptr) return;
  //find which set they belong to in larger set
  int xIndex = -1, yIndex = -1;
  for(int i = 0; i < S.size(); i++){
     if(&S[i][0] == xRep){
       xIndex = i;
     }
     if(&S[i][0] == yRep){
       yIndex = i;
     }
  }
  //already in same set
  if(xIndex == yIndex) return;
  //add y to this set
  for(int i = 0; i < S[yIndex].size(); i++){
    S[xIndex].push_back(S[yIndex][i]);
  }
  //delete y's set
  S.erase(S.begin() + yIndex);
}
