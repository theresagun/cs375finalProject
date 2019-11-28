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
  //    //cout << "index: " << index << endl;
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
    cout<<"trans " << trans[i].id <<endl;
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
      cout<<" SCC size " << scc.size()<<endl;
      DFSvisitT(trans[index], trans, scc);
      cout<<" SCC size 2 " << scc.size()<<endl;
    }
    if(scc.size() > 0 ){
      ret.push_back(scc);
    }
  }
  return ret;


//  //cout<<"==========================SORT========================="<<endl;
//  for(int i = 0 ; i < nodes.size() ; i++){
//    //cout<< "id " << nodes[i].id << " disc time  "<<nodes[i].d << " finish time "<< nodes[i].f<<endl;
//  }
//  //cout<<"==========================TRANS STUFF========================="<<endl;
//  for(int i = 0 ; i < trans.size() ; i++){
//    //cout<< "id " << trans[i].id << " disc time  "<<trans[i].d << " finish time "<< trans[i].f<<endl;
//  }
//  //cout << ret.size() << endl;
  vector<vector<Node>> ret2;
  for(int i=0; i< ret.size(); i++){
    bool inside=false;

    if(ret[i].size()>1) {
      ret2.push_back(ret[i]);
    }
    else if(ret[i].size() == 1){
      for(int j=0; j< ret[i][0].adjacents.size(); j++){
        if(ret[i][0].id==ret[i][0].adjacents[j]){
          inside=true;
        }
      }
      if(inside == true){
        ret2.push_back(ret[i]);
      }
    }

  }
  return ret2;
}


void Graph::DFSvisitT(Node &node, vector<Node> &t, vector<Node> &s){
  time++;
  node.d = time;
  ////cout << "time: " << time << endl;
  node.color = "gray";
  for(int i = 0 ; i < node.adjacents.size() ; i++){
//    //cout << "node id: "<< node.id << endl;
    int index = getNodeT(node.adjacents[i], t);
//    //cout << "node at index: " << t[index].id << endl;
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
  ////cout << "time: " << time << endl;
  node.color = "gray";
  for(int i = 0 ; i < node.adjacents.size() ; i++){
    //cout << "node id: "<< node.id << endl;
    int index = getNode(node.adjacents[i]);
    //cout << "node at index: " << nodes[index].id << endl;
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
    //cout<<"=========================="<<endl;
   //cout<<"size "<<q.size()<<endl;
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
      //cout<<"new value; size = "<<q.size()<<endl;
      for(int i=0; i<q.size(); i++){
        //cout<<"=======value: " << temp.front().id<<endl;
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
      //cout << "scc size " << scc.size() <<endl;
      if(scc[0].id == scc[scc.size()-1].id){
        ret.push_back(scc);
      }
    }
  }


    /*  for(int i = scc.size()-1 ; i >= 0 ; i--){
        Node temp = scc[i];
        for(int j = 0 ; j < scc[i].adjacents.size() ; j++){
          vector<Node> path;
          //cout<<"i is "<<i<<endl;
          ////cout<<temp.parent<<endl;
          ////cout<<temp.id<<endl;
          int idx=getNodeT(scc[i].adjacents[j], scc);
          Node adjacent = scc[idx];
          //cout<<"Adjacent id  " <<adjacent.id<<endl;
          //cout<<"  parent " <<temp.parent<<endl;
          //cout<<"temp " <<temp.id<<endl;
          while(temp.parent != adjacent.id && temp.parent!=NULL && temp.id != adjacent.id){
            //cout<<"  hereheh" <<endl;
            path.push_back(temp);
            int index = getNodeT(temp.parent, scc);
            //cout<<"index is  " <<index <<endl;
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
    //cout<<"new arrray"<<endl;
    //cout<<"---";
    for(int j=0;ZX j<ret[i].size(); j++){
      //cout<< ret[i][j].id <<" , ";
    }
    //cout<<""<<endl;
  }

  return ret;
}
*/

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
      ////cout<<"here" <<endl;
      set<Node> scc;
      BFS(nodes[i], scc);   //see if adjacents lead back to source node
    //  for(int i=0; i<scc.size(); i++){
    //    //cout<<"scc val " << scc[i].id<<endl;
    //  }
      ret.insert(scc);
    }
  }
      /*
      //cout<<"here" <<endl;
      if(scc[0].id == scc[scc.size()-1].id){
        scc.erase(scc.begin()+scc.size()-1);
        finalSet.insert(scc);
      }
      for(int k = scc.size()-1 ; k >= 0 ; k--){
        Node temp = scc[k];
        //cout<<"here2" <<endl;
        for(int j = 0 ; j < scc[k].adjacents.size() ; j++){
          vector<Node> path;
          int idx=getNodeT(scc[k].adjacents[j], scc);
          Node adjacent = scc[idx];
          int c=0;
          while( temp.parent!=NULL && temp.id != adjacent.id){
            //cout<<"here3" <<endl;
            path.push_back(temp);
            int index=getNodeT(temp.parent, scc);
            if(scc[index].visited == false){
              scc[index].visited=true;
              temp=scc[index];
            }
            else{
              //cout<<"ended" <<endl;
              break;
            }
          }
          if(temp.id==adjacent.id) {
            path.push_back(adjacent);
            finalSet.insert(path);
          }
        }
        //cout<<"bot" <<endl;
      }
    }
    //cout<<"ended" <<endl;
  }

  set<set<Node>> intermediate;
  for(auto it=finalSet.begin(); it!= finalSet.end(); it++){
    set<Node> oneSet;
    for(int n=0; n<(*it).size(); n++){
      oneSet.insert((*it)[n]);
    }
    intermediate.insert(oneSet);
}

  for(auto it=intermediate.begin(); it!= intermediate.end(); it++){
    bool add = true;
    for(auto it2=intermediate.begin(); it2!= intermediate.end(); it2++){
      if((*it2).size() == (*it).size()) continue;
      if(std::includes((*it2).begin(), (*it2).end(), (*it).begin(), (*it).end(), compBFS)==true){
          add=false;
        }
    }
    if(add ==  true) {
      ret.insert(*(it));
    }
  }
  */
    //cout<<"ended" <<endl;
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
    ////cout << "\n---NODE " << nodes[i].id << endl;
    for(int j = 0; j < nodes[i].adjacents.size(); j++){
      ////cout << "-ADJ " << nodes[i].adjacents[j] << endl;
      //for each node ie. v
      if(dj.findSet(nodes[i]) != dj.findSet(nodes[getNode(nodes[i].adjacents[j])])){ //from notes
      //if they are not in the same set
        ////cout << "union " << nodes[i].id << " " << nodes[i].adjacents[j] << endl;
          dj.unionSets(nodes[i], nodes[getNode(nodes[i].adjacents[j])]);
      }
    }
  }
  return dj.S;
}
