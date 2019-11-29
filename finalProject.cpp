#include "Graph.h"
#include "disjoint2.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iostream>
using namespace std;

int main(int argc, char** argv){
  ifstream infile(argv[1]);
  string graphType=argv[2];
  int num;
  bool newNode = true;
  Graph g;
  while(infile >> num){
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
    }
  }
  ifstream sparse; ifstream dense;
  ofstream output;
  output.open("output.txt");
//DFS
  auto start1=chrono::high_resolution_clock::now();
  vector<vector<Node>> d=g.DFST();
  auto end1 = chrono::high_resolution_clock::now();
  auto time1 = chrono::duration<double>(end1-start1);
  output<<"DFS time for " << graphType << " graph "<<time1.count() <<"\n";
  for(int i=0; i<d.size(); i++){
    for(int j=0; j<d[i].size(); j++){
      output<<d[i][j].id << ", ";
    }
    output<<"\n";
  }
//BFS
  auto start2=chrono::high_resolution_clock::now();
  set<set<Node>> b = g.BFSscc();
  auto end2 = chrono::high_resolution_clock::now();
  auto time2 = chrono::duration<double>(end2-start2);
  output<<"BFS time for " << graphType << " graph "<<time2.count() <<"\n";
  for(auto i=b.begin(); i!=b.end(); i++){
    for(auto it=(*i).begin(); it!= (*i).end(); it++){
      output<<(*it).id <<", ";
    }
    output<<"\n";
  }
//disjoint-set
  auto start3=chrono::high_resolution_clock::now();
  vector<vector<Node>> djs = g.disjointCC();
  auto end3 = chrono::high_resolution_clock::now();
  auto time3 = chrono::duration<double>(end3-start3);
  output<<"Disjoint Set time for " << graphType << " graph "<<time3.count() <<"\n";
  for(int i=0; i<djs.size(); i++){
    for(int j=0; j<djs[i].size(); j++){
      output<<djs[i][j].id << ", ";
    }
    output<<"\n";
  }
  output.close();
}
