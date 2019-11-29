#include "Graph.h"
#include "disjoint2.h"
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <set>
using namespace std;

int Graph::getNode(int num){
  for(int i = 0 ; i < nodes.size() ; i++){
    if(nodes[i].id==num){ return i; }
  }
  return -1;
}

int Graph::getNodeT(int num, vector<Node> r){
  for(int i = 0 ; i < r.size() ; i++){
    if(r[i].id==num){
      return i;
    }
  }
  return -1;
}

bool operator <(const Node& a, const Node& b){
			return a.id < b.id;
}

vector<Node> Graph::transpose(){
  vector<Node> ret;
  for(int i = 0 ; i < nodes.size() ; i++){
    if(nodes[i].adjacents.size() == 0){
      ret.push_back(nodes[i]);
      continue;
    }
    for(int j = 0 ; j < nodes[i].adjacents.size() ; j++){
      int t = nodes[i].adjacents[j];
      int index = getNodeT(t, ret);
      if(index==-1){
        Node temp = Node(t);
        temp.adjacents.push_back(nodes[i].id);
        ret.push_back(temp);
      }
      else{
        int index = getNodeT(t, ret);
        if(index!=-1){
          ret[index].adjacents.push_back(nodes[i].id);
        }
      }
    }
  }
  for(int i = 0 ; i < ret.size() ; i++){
    if(getNodeT(nodes[i].id, ret)==-1){
      Node temp = Node(nodes[i].id);
      ret.push_back(temp);
    }
  }
  return ret;
}

void Graph::DFS(){
  for(int i = 0 ; i < nodes.size() ; i++){
    nodes[i].color="white";
    nodes[i].parent = -1;
  }
  time = 0;
  for(int i = 0 ; i < nodes.size() ; i++){
    if(nodes[i].color == "white"){
      DFSvisit(nodes[i]);
    }
  }
}

bool comp(Node a, Node b){
  if(a.f > b.f) return true;
  return false;
}

bool compBFS(Node a, Node b){
  if(a.id < b.id) return true;
  return false;
}

vector<vector<Node>> Graph::DFST(){
  vector<vector<Node>> ret;
  DFS();
  sort(nodes.begin(), nodes.end(), comp);
  vector<Node> trans= transpose();
  for(int i = 0 ; i < trans.size() ; i++){
    trans[i].color="white";
    trans[i].parent = -1;
  }
  time = 0;
  for(int i = 0 ; i < trans.size() ; i++){
    int index = getNodeT(nodes[i].id, trans);
    vector<Node> scc;
    if(trans[index].color == "white"){
      scc.push_back(trans[index]);
      DFSvisitT(trans[index], trans, scc);
    }
    if(scc.size() > 0 ){
      ret.push_back(scc);
    }
  }
  return ret;
}

void Graph::DFSvisitT(Node &node, vector<Node> &t, vector<Node> &s){
  time++;
  node.d = time;
  node.color = "gray";
  for(int i = 0 ; i < node.adjacents.size() ; i++){
    int index = getNodeT(node.adjacents[i], t);
    if(t[index].color=="white"){
      s.push_back(t[index]);
      t[index].parent = node.id;
      DFSvisitT(t[index], t, s);
    }
  }
  node.color="black";
  time++;
  node.f = time;
}

void Graph::DFSvisit(Node &node){
  time++;
  node.d = time;
  node.color = "gray";
  for(int i = 0 ; i < node.adjacents.size() ; i++){
    int index = getNode(node.adjacents[i]);
    if(nodes[index].color=="white"){
      nodes[index].parent = node.id;
      DFSvisit(nodes[index]);
    }
  }
  node.color="black";
  time++;
  node.f = time;
}

set<set<Node>> Graph::BFSscc(){
  set<set<Node>> ret;
  set<vector<Node>> finalSet;
  for(int i = 0; i<nodes.size(); i++){
    for(int p=0; p<nodes.size(); p++){
      nodes[p].color="w";
      nodes[p].d = 2147483647;
      nodes[p].parent= NULL;
      nodes[p].visited=false;
    }
    if(nodes[i].color == "w" && nodes[i].added == false){
      set<Node> scc;
      BFS(nodes[i], scc);   //see if adjacents lead back to source node
      ret.insert(scc);
    }
  }
    return ret;
}

void Graph::BFS(Node s, set<Node>& t){
  s.color="g";
  s.d=0;
  s.parent=NULL;
  queue<Node> q;
  q.push(s);
  t.insert(s);
  while(!q.empty()){
    queue<Node> temp = q;
    Node u = q.front();
    q.pop();
    for(int i = 0; i<u.adjacents.size(); i++ ){
      int index=getNode(u.adjacents[i]);
      if(index != -1 && nodes[index].color == "w"){
        nodes[index].color = "g";
        nodes[index].d = u.d + 1;
        nodes[index].parent=u.id;
        t.insert(nodes[index]);
        q.push(nodes[index]);
        nodes[index].added=true;
      }
      queue<Node> temp = q;
      for(int i=0; i<q.size(); i++){
        temp.pop();
      }
    }
    u.color="b";
  }
  int p = getNode(s.id);
  nodes[p].added = false;
}

vector<vector<Node>> Graph::disjointCC(){
  /*puts each vertex in its own set, for each edge merge sets*/
  disjoint dj;
  //make each vertex a set
  for(int i = 0; i < nodes.size(); i++){
    dj.makeSet(nodes[i]);
  }
  //for each edge, merge sets containing those vertices
  for(int i = 0; i < nodes.size(); i++){
    //for each node ie. u
    for(int j = 0; j < nodes[i].adjacents.size(); j++){
      //for each node ie. v
      if(dj.findSet(nodes[i]) != dj.findSet(nodes[getNode(nodes[i].adjacents[j])])){ //from notes
      //if they are not in the same set
          dj.unionSets(nodes[i], nodes[getNode(nodes[i].adjacents[j])]);
      }
    }
  }
  return dj.S;
}
