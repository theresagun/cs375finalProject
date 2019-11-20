#include "Graph.h"
#include "Disjoint.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char** argv){
  ifstream infile(argv[1]);
  int num;
  bool newNode = true;
  Graph g;
  while(infile >> num){
    //cout << "num: " << num << endl;
    if(num==-1){
      newNode = true;
      continue;
    }
    if(newNode==true){
      g.nodes.push_back(Node(num));
      newNode = false;
    }
    else{
      g.nodes[g.nodes.size()-1].adjacents.push_back(num);
      //cout << "last: " << last.id << endl;
      //last.adjacents.push_back(num);
    }
  }
  cout << "while loop done" << endl;
  cout << g.nodes.size() << endl;
  for(int i = 0 ; i < g.nodes.size() ; i++){
    cout << "node: " << g.nodes[i].id << endl;
    //cout << "adjacent size: " << g.nodes[i].adjacents.size() << endl;
    for(int j = 0 ; j < g.nodes[i].adjacents.size() ; j++){
      cout << "adjacents: " << g.nodes[i].adjacents[j] << endl;
    }
  }
  /*g.DFS();
  cout << g.nodes[1].color << endl;
  for(int i = 0 ; i < g.nodes.size() ; i++){
    cout << g.nodes[i].id<<", " << g.nodes[i].color<<", " << g.nodes[i].d<<", " << g.nodes[i].f << endl;
  }*/
  //cout << g.nodes[0].id << endl;
  g.BFS(g.nodes[1]);
  for(int i = 0 ; i < g.nodes.size() ; i++){
     cout << "id: "<<g.nodes[i].id<<endl;
  }
  //disjoint shit
  disjointSet ds = disjointSet();
  vector<vector<int>> cc = ds.connectedComponents(g);
}
