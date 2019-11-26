#include "Graph.h"
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
  cout << ret.size() << endl;
  vector<vector<Node>> ret2;
  for(int i=0; i< ret.size(); i++){
    bool inside=false;

    if(ret[i].size()>1) {
      cout<<"true222" <<endl;
      ret2.push_back(ret[i]);
      //inside = true;
    }
    else if(ret[i].size() == 1){
      cout<<" size " << ret[i].size() << "id " << ret[i][0].id<<endl;
      for(int j=0; j< ret[i][0].adjacents.size(); j++){
        cout<<"ret[i][0].id " << ret[i][0].id << "adj " <<ret[i][0].adjacents[j] << endl;
        if(ret[i][0].id==ret[i][0].adjacents[j]){
          inside=true;
        }
      }
      if(inside == true){
        cout<<"true" <<endl;
        ret2.push_back(ret[i]);
      }
    }

  }
  cout << ret2.size() << ":::::" << endl;
  return ret2;
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
    for(int j=0;ZX j<ret[i].size(); j++){
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
    for(int p=0; p<nodes.size(); p++){
      nodes[p].color="w";
      nodes[p].d = 2147483647;
      nodes[p].parent= NULL;
      nodes[p].visited=false;
    }
    if(nodes[i].color == "w"){
      vector<Node> scc;
      //scc.push_back(nodes[i]);
      BFS(nodes[i], scc);   //see if adjacents lead back to source node
      if(scc[0].id == scc[scc.size() -1].id){
        scc.erase(scc.begin()+scc.size()-1);
        ret.push_back(scc);
      }
      for(int k = scc.size()-1 ; k >= 0 ; k--){
        Node temp = scc[k];
        for(int j = 0 ; j < scc[k].adjacents.size() ; j++){
          vector<Node> path;
          int idx=getNodeT(scc[k].adjacents[j], scc);
          Node adjacent = scc[idx];
          while( temp.parent!=NULL && temp.id != adjacent.id){
            path.push_back(temp);
            int index = getNodeT(temp.parent, scc);
            if(scc[index].visited == false){
              scc[index].visited=true;
              temp=scc[index];
            }
            else{
              break;
            }
          }
          if(temp.id==adjacent.id) {
            path.push_back(adjacent);
            ret.push_back(path);
          }
        }
      }
    }
  }


  for(int b=0; b<ret.size(); b++){
      sort(ret[b].begin(), ret[b].end(), compBFS);
  }
  // for(int m=0; m<ret.size(); m++){
  //     ret2.push_back(ret[m]);
  // }


  for(int m=0; m<ret.size(); m++){
    for(int n=m+1; n<ret.size(); n++){
      int size1=ret[m].size()-1;
      int size2=ret[n].size()-1;
      if(ret[m][size1].id == ret[n][size2].id || ret[m][0].id == ret[n][0].id  ){
        if(ret[m].size() > ret[n].size()){
          ret[n].clear();
        }
        else ret[m].clear();
        //ret.erase(ret.begin() + m);
      }
    }
}
  vector<vector<Node>> ret2;
  for(int m=0; m<ret.size(); m++){
    if(ret[m].size() > 0) ret2.push_back(ret[m]);
  }


// cout<<"an" <<endl;
//   set<int> indexes;
//   //cout<<" ret 2 size is  " << ret2.size()<<endl;
//   for(int m=0; m<ret.size(); m++){
//     cout<< "m is " << m<<endl;
//     for(int n=m; n<ret.size(); n++){
//       cout<< "n is " << n<<endl;
//       //cout<<"an" <<endl;
//       //cout<<"ret[m][0] " <<ret[m][0].id <<endl;
//       cout<<"Asfmf" << ret[n].size()<<endl;
//       //cout<<"ret[n][0] " <<ret[n][0].id <<endl;
//       if(ret[m].size()!=0 && ret[n].size()!=0){
//          if(ret[m][0].id == ret[n][0].id){
//         //ret.push_back(ret[m]);
//           indexes.insert(m);
//         }
//         //ret.erase(ret.begin() + m);
//       }
//       cout<<"done"<<endl;
//     }
//   }
//   for(auto s = indexes.end(); s!=indexes.begin(); s--){
//     ret.erase(ret.begin() + *s);
//   }


    for(int i=0; i<ret2.size(); i++){
      cout<<"new arrray"<<endl;
      cout<<"---";
      for(int j=0; j<ret2[i].size(); j++){
        cout<< ret2[i][j].id <<" , ";
      }
      cout<<""<<endl;
    }



    return ret2;
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
    for(int i = 0; i<u.adjacents.size(); i++ ){
      int index=getNode(u.adjacents[i]);
      if(nodes[index].color == "w"){
        nodes[index].color = "g";
        nodes[index].d = u.d + 1;
        nodes[index].parent=u.id;
        t.push_back(nodes[index]);
        q.push(nodes[index]);
        nodes[index].added=true;
      }
      queue<Node> temp = q;
//      cout<<"new value; size = "<<q.size()<<endl;
      for(int i=0; i<q.size(); i++){
//        cout<<"=======value: " << temp.front().id<<endl;
        temp.pop();
      }
    }
    u.color="b";

  }
  int p = getNode(s.id);
  nodes[p].added = false;
}
