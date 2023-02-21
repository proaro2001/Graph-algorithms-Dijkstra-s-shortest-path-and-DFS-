// ---------------------------------graphm.h----------------------------------------

// Programmer Name:             Choi Ka Hin
// Course:                      CSS 343
// Creation Date:               Feb 17, 2023
// Date of Last Modification:   February 18, 2023

// header file for graphm.cpp

// -----------------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int MAXNODES = 100; // maximum number of Nodes is 100

struct TableType {
  bool visited; // whether node has been visited
  int dist;     // shortest distance from source known so far
  int path;     // previous node in path of min dist
  void markVisited() { visited = true; }
};

class GraphM {
public:
  GraphM(); // default constructor
  void buildGraph(
      ifstream &); // builds up graph node information and adjacency matrix of
                   // edges between each node reading from a data file
  void insertEdge(int, int, int); // insert Edge to Cost Table
  void removeEdge(int, int);      // remove edge from Cost Table
  void findShortestPath(); // find the shortest path between every node to every
                           // other node in the graph, i.e., TableType T is
                           // updated with shortest path information
  void displayAll(); //  uses "cout"s to demonstrate that the algorithm works
                     //  properly.
  void display(int, int);

private:
  NodeData data[MAXNODES];         // data for graph nodes
  int C[MAXNODES][MAXNODES];       // Cost array, the adjacency matrix
  int size;                        // number of nodes in the graph
  TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path

  // helper function to find shortest distance at the moment
  void dijkstra(int, int);
  // helper function to get the path
  string getPath(int, int);
  // helper function of getPath function
  void getReversePath(int, int, string &);
  // helper function to generate string to vector<int> that stores path
  vector<int> getPath(string);
};

#endif