#include "Graph.h"
#include <iostream>
using namespace std;

int Graph::getNode(int num){
  for(int i = 0 ; i < nodes.size() ; i++){
    if(nodes[i].id==num){ return i; }
  }
  return NULL;
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

void Graph::DFSvisit(Node node){
  time++;
  node.d = time;
  //cout << "time: " << time << endl;
  node.color = "gray";
  for(int i = 0 ; i < node.adjacents.size() ; i++){
    int index = getNode(node.adjacents[i]);
    
    cout << "temp.id: " << temp.id << endl;
    cout << "temp.color: " << temp.color << endl;
    if(temp.color=="white"){
      temp.parent = node.id;
      DFSvisit(temp);
    }
  }
  node.color="black";
  time++;
  node.f = time;
}
