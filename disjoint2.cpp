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
  //cout << "size of S is " << S.size() << endl;
}

Node * disjoint::findSet(Node x){
  /*returns representative of set with this node*/
  //check if in sets in larger set
  for(int i = 0; i < S.size(); i++){
    //checks elements
    for(int j = 0; j < S[i].size(); j++){
    //  if(S[i].find(x) != S.end()){
  //    if(S[i].find(S[i].begin(), S[i].end(), x) != S[i].end()){
      if(S[i][j].id == x.id){
        //if it is in the set, return the first item in this set
        return &S[i][0];
    //    return &(*(S[i].begin()));
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
//  cout << "x ind is " << xIndex << " y ind is " << yIndex << endl;
  if(xIndex == yIndex) return;
//  cout << "yrep is " << yRep->id << endl;
  //add y to this set
//  S[xIndex].push_back(y);
  //cout << "size of s[yindex] is " << S[yIndex].size() << endl;
  for(int i = 0; i < S[yIndex].size(); i++){
  //  cout << "yup" << i << endl;
    S[xIndex].push_back(S[yIndex][i]);
  }
  //delete y's set
  S.erase(S.begin() + yIndex);
}

// vector<vector<Node>> disjoint::disjointCC(Graph g){
//   /*puts each vertex in its own set, for each edge merge sets*/
//   //make each vertex a set
//   for(int i = 0; i < g.nodes.size(); i++){
//     makeSet(g.nodes[i]);
//   }
//   //for each edge, merge sets containing those vertices
//   for(int i = 0; i < g.nodes.size(); i++){
//     //for each node ie. u
//     for(int j = 0; j < g.node[i].adjacents.size(); j++){
//       //for each node ie. v
//       if(findSet(g.nodes[i]) != findSet(g.nodes[g.getNode(g.nodes.adjacents[j])])){
//         //if they are not in the same set, merge
//         unionSets(g.nodes[i], g.nodes[g.getNode(g.nodes.adjacents[j])]);
//       }
//     }
//   }
//   return S;
// }
