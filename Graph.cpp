#include "Graph.h"
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
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
vector<Node> Graph::transpose(){
  vector<Node> ret;
  for(int i = 0 ; i < nodes.size() ; i++){
    for(int j = 0 ; j < nodes[i].adjacents.size() ; j++){
      int t = nodes[i].adjacents[j];
      int index = getNodeT(t, ret);
      cout << "index: " << index << endl;
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

    cout<<"trans id "<<trans[index].id<<endl;
    if(trans[index].color == "white"){
      scc.push_back(trans[index]);
      DFSvisitT(trans[index], trans, scc);
    }
    ret.push_back(scc);
  }
  cout<<"==========================SORT========================="<<endl;
  for(int i = 0 ; i < nodes.size() ; i++){
    cout<< "id " << nodes[i].id << " disc time  "<<nodes[i].d << " finish time "<< nodes[i].f<<endl;
  }
  cout<<"==========================TRANS STUFF========================="<<endl;
  for(int i = 0 ; i < trans.size() ; i++){
    cout<< "id " << trans[i].id << " disc time  "<<trans[i].d << " finish time "<< trans[i].f<<endl;
  }
  return ret;
}


void Graph::DFSvisitT(Node &node, vector<Node> &t, vector<Node> &s){
  time++;
  node.d = time;
  //cout << "time: " << time << endl;
  node.color = "gray";
  for(int i = 0 ; i < node.adjacents.size() ; i++){
    cout << "node id: "<< node.id << endl;
    int index = getNodeT(node.adjacents[i], t);
    cout << "node at index: " << t[index].id << endl;
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
  //cout << "time: " << time << endl;
  node.color = "gray";
  for(int i = 0 ; i < node.adjacents.size() ; i++){
    cout << "node id: "<< node.id << endl;
    int index = getNode(node.adjacents[i]);
    cout << "node at index: " << nodes[index].id << endl;
    if(nodes[index].color=="white"){
      nodes[index].parent = node.id;
      DFSvisit(nodes[index]);
    }
  }
  node.color="black";
  time++;
  node.f = time;
}
/*
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
*/

/*
vector<vector<Node>> Graph::BFSscc(){
  vector<vector<Node>> ret;
  for(int i = 0; i<nodes.size(); i++){
    for(int i=0; i<nodes.size(); i++){
      //if(nodes[i].id == s.id) continue;
      nodes[i].color="w";
      nodes[i].d = 2147483647;
      nodes[i].parent= NULL;
      nodes[i].visited=false;
    }
    if(nodes[i].color == "w"){
      vector<Node> scc;
      //scc.push_back(nodes[i]);
      BFS(nodes[i], scc);   //see if adjacents lead back to source node
      cout << "scc size " << scc.size() <<endl;
      if(scc[0].id == scc[scc.size()-1].id){
        ret.push_back(scc);
      }
    }
  }


    /*  for(int i = scc.size()-1 ; i >= 0 ; i--){
        Node temp = scc[i];
        for(int j = 0 ; j < scc[i].adjacents.size() ; j++){
          vector<Node> path;
          cout<<"i is "<<i<<endl;
          //cout<<temp.parent<<endl;
          //cout<<temp.id<<endl;
          int idx=getNodeT(scc[i].adjacents[j], scc);
          Node adjacent = scc[idx];
          cout<<"Adjacent id  " <<adjacent.id<<endl;
          cout<<"  parent " <<temp.parent<<endl;
          cout<<"temp " <<temp.id<<endl;
          while(temp.parent != adjacent.id && temp.parent!=NULL && temp.id != adjacent.id){
            cout<<"  hereheh" <<endl;
            path.push_back(temp);
            int index = getNodeT(temp.parent, scc);
            cout<<"index is  " <<index <<endl;
            if(scc[index].visited == false){
              scc[index].visited=true;
              temp=scc[index];
            }
            else{
              break;
            }
            //temp = temp.parent;
          }
          if(temp.parent!=NULL){
            path.push_back(adjacent);
            ret.push_back(path);
          }
        }
      }
    }
  }

  for(int i=0; i<ret.size(); i++){
    cout<<"new arrray"<<endl;
    cout<<"---";
    for(int j=0; j<ret[i].size(); j++){
      cout<< ret[i][j].id <<" , ";
    }
    cout<<""<<endl;
  }

  return ret;
}
*/

vector<vector<Node>> Graph::BFSscc(){
  vector<vector<Node>> ret;
  for(int i = 0; i<nodes.size(); i++){
    for(int i=0; i<nodes.size(); i++){
      //if(nodes[i].id == s.id) continue;
      nodes[i].color="w";
      nodes[i].d = 2147483647;
      nodes[i].parent= NULL;
      nodes[i].visited=false;
    }
    if(nodes[i].color == "w"){
      vector<Node> scc;
      //scc.push_back(nodes[i]);
      BFS(nodes[i], scc);   //see if adjacents lead back to source node
      cout << "scc size " << scc.size() <<endl;
      for(int i = scc.size()-1 ; i >= 0 ; i--){
        Node temp = scc[i];
        for(int j = 0 ; j < scc[i].adjacents.size() ; j++){
          vector<Node> path;
          int idx=getNodeT(scc[i].adjacents[j], scc);
          Node adjacent = scc[idx];
          cout<<"Adjacent id  " <<adjacent.id<<endl;
          cout<<"  parent " <<temp.parent<<endl;
          cout<<"temp " <<temp.id<<endl;
//adjacent.id != temp.parent &&
          while( temp.parent!=NULL && temp.id != adjacent.id){
            cout<<"  hereheh" <<endl;
            path.push_back(temp);
            int index = getNodeT(temp.parent, scc);
            cout<<"index is  " <<index <<endl;
            if(scc[index].visited == false){
              scc[index].visited=true;
              temp=scc[index];
            }
            else{
              break;
            }
            //temp = temp.parent;
          }
          if(temp.id==adjacent.id){
            path.push_back(adjacent);
            ret.push_back(path);
          }
        }
      }
    }
  }

  for(int i=0; i<ret.size(); i++){
    cout<<"new arrray"<<endl;
    cout<<"---";
    for(int j=0; j<ret[i].size(); j++){
      cout<< ret[i][j].id <<" , ";
    }
    cout<<""<<endl;
  }

  return ret;
}


void Graph::BFS(Node s, vector<Node>& t){
  s.color="g";
  s.d=0;
  s.parent=NULL;
  queue<Node> q;
  q.push(s);
  t.push_back(s);
  while(!q.empty()){
    queue<Node> temp = q;
    Node u = q.front();
    q.pop();
    for(int i =0; i<u.adjacents.size(); i++ ){
      int index=getNode(u.adjacents[i]);
      if(nodes[index].color == "w"){
        nodes[index].color = "g";
        nodes[index].d = u.d + 1;
        nodes[index].parent=u.id;
        t.push_back(nodes[index]);
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
  for(int i=0;i<t.size(); i++){
    cout<<"t id " <<t[i].id <<endl;
  }
}
