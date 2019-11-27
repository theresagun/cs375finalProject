#include "Disjoint.h"
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

void disjointSet::makeSet(Node n){
  //make new LL, add to set
  S.push_back(disjointLL(n));
  //cout << "in make set " << S[S.size()-1].head->id << endl;
}

int disjointSet::findSet(int n){
  //rework logic
  cout << "in find set" << endl;
  cout << "want set that n is in " << n << endl;
  cout << "currently returning " << S[n].head->id << endl;
  //returns representative, which is first element in disjointLL
  return S[n].head->id;
}

void disjointSet::unionSets(Node x, Node y){
  cout << "node x id is " << x.id << endl;
  cout << "node y id is " << y.id <<endl;
    //adds set y to end of set x, deletes set y
    //findset is fucked up
  int xSet = findSet(x.id);
  int ySet = findSet(y.id);
  int xIndex = 0;
  int yIndex = 0;
  cout << "xset id " << xSet << "vs. yset id " << ySet << endl;
  for(int i = 0; i < S.size(); i++){
    //if head is this we found it
    if(S[i].head->id == xSet) xIndex = i;
    if(S[i].head->id == ySet) yIndex = i;
  }
  cout << xIndex << endl;
  cout << yIndex << endl;
  //put the rest of y onto x
  while(S[yIndex].head != nullptr){
  //  cout << "here" << endl;
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
    cout << "size is " << g.nodes[i].adjacents.size() << endl;
    cout << "looking at node " << g.nodes[i].id << endl;
    for(int j = 0; j < g.nodes[i].adjacents.size(); j++){
      cout << "looking at adj node " << g.nodes[i].adjacents[j] << endl;
      cout << "getNode " << g.nodes[g.getNode(g.nodes[i].adjacents[j])].id << endl;
      //what does get node do?
      //we want to pass two nodes into unionSets
  //    cout << "adj is " << g.nodes[i].adjacents[j] << endl;
      if(findSet(g.nodes[i].id) == findSet(g.nodes[i].adjacents[j])){
        unionSets(g.nodes[i], g.nodes[g.getNode(g.nodes[i].adjacents[j])]);
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
