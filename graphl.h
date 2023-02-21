// ---------------------------------graphl.h----------------------------------------

// Programmer Name:             Choi Ka Hin
// Course:                      CSS 343
// Creation Date:               Feb 17, 2023
// Date of Last Modification:   February 18, 2023

// header file for graphl.cpp

// -----------------------------------------------------------------------------------
#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <fstream>
#include <iostream>
#include <stack>

using namespace std;
const int LMAXNODES = 100; // maximum node for this class

struct EdgeNode; // forward reference for the compiler

struct GraphNode {    // structs used for simplicity, use classes if desired
  EdgeNode *edgeHead; // head of the list of edges
  NodeData *data;     // data information about each node
  bool visited;
};

struct EdgeNode {
  int adjGraphNode;   // subscript of the adjacent graph node
  EdgeNode *nextEdge; // next Edge pointer
  // constructor takes in an int for adjGraphNode
  EdgeNode(int to) : adjGraphNode(to), nextEdge(nullptr) {}
  // constructor takes in int and next node
  EdgeNode(int to, EdgeNode *next) : adjGraphNode(to), nextEdge(next) {}
};

class GraphL {
public:
  GraphL();  // constructor
  ~GraphL(); // destructor
  // builds up graph node information and adjacency list of edges between each
  // node reading from a data file.
  void buildGraph(istream &);
  // Displays each node information and edge in the graph
  void displayGraph();
  // Makes a depth-first search and displays each node in depth-first order
  void depthFirstSearch();

private:
  GraphNode graph[LMAXNODES]; // array of GraphNodes
  int size;                   // number of nodes

  // helper function to insert Edge
  void insertEdge(int, int);
  // helper function to get edges and be used in displayGraph function
  string getEdges(int);
  // helper function of depthFirstSearch function
  void dfsHelper(stack<int> &, string &, int);
};

#endif