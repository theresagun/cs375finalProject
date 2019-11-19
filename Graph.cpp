#include "Graph.h"
#include <iostream>
#include <queue>
#include <limits>
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
    if(nodes[index].color=="white"){
      nodes[index].parent = node.id;
      DFSvisit(nodes[index]);
    }
  }
  node.color="black";
  time++;
  node.f = time;
}

void Graph::BFS(Node s){
  for(int i=0; i<nodes.size(); i++){
    if(nodes[i].id == s.id) continue;
    nodes[i].color="w";
    nodes[i].d = 2147483647;
    nodes[i].parent= NULL;
  }
  s.color="g";
  s.d=0;
  s.parent=NULL;
  queue<Node> q;
  q.push(s);

  while(!q.empty()){
    queue<Node> temp = q;
    cout<<"=========================="<<endl;
   cout<<"size "<<q.size()<<endl;
    Node u = q.front();
    q.pop();
    for(int i =0; i<u.adjacents.size(); i++ ){
      int index=getNode(u.adjacents[i]);
      if(nodes[index].color == "w"){
        nodes[index].color = "g";
        nodes[index].d = u.d + 1;
        nodes[index].parent=u.id;
        q.push(nodes[index]);
      }
      queue<Node> temp = q;
      cout<<"new value; size = "<<q.size()<<endl;
      for(int i=0; i<q.size(); i++){
        cout<<"=======value: " << temp.front().id<<endl;
        temp.pop();
      }
    }
    u.color="b";
  }


}
