// -------------------------------- graphl.h -----------------------------------------

// Programmer Name:             Choi Ka Hin
// Course:                      CSS 343
// Creation Date:               Feb 17, 2023
// Date of Last Modification:   February 18, 2023

// -----------------------------------------------------------------------------------

// Purpose - This file contains the declaration and definition of the GraphL class
//           It allows users to build and display the graph, as well as performing a depth-first 
//           search on the graph.

// -----------------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions:
// - The maximum number of nodes in the graph is assumed to be 99.
// - The graph is assumed to be a directed graph
// - The insertEdge() method does not sort the edges.
// - The depth-first search starts from node 1 

// -----------------------------------------------------------------------------------

#include "graphl.h"
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// -------------------------------GraphL Constructor----------------------------------
// Description
// GraphL: default constructor to initialize GraphL object with empty data and no edges.
// Precondition: None.
// Postcondition: A new GraphL object is created with empty data and no edges.
// -----------------------------------------------------------------------------------
GraphL::GraphL() : size(0) {
  for (int i = 0; i < LMAXNODES; i++) {
    graph[i].edgeHead = nullptr;
    graph[i].data = nullptr;
    graph[i].visited = false;
  }
}
// end of GraphL constructor

// ---------------------------------~GraphL------------------------------------
// Description:
// Destructor for the GraphL class. Frees all allocated memory for the object.
// Precondition:None.
// Postcondition: All memory is freed.
// -----------------------------------------------------------------------------------
GraphL::~GraphL() {
  for (int i = 1; i <= size; i++) {
    EdgeNode *curr = graph[i].edgeHead; // free all edgenode memory
    while (curr) {
      EdgeNode *edge_delete = curr;
      curr = curr->nextEdge;
      delete edge_delete;
    }
    delete graph[i].data; // free NodeData class
  }
}
// end of ~GraphL()

// ------------------------------------buildGraph-----------------------------------------------
// Description:
// buildGraph: function to build the graph based on the given formatted data 
// preconditions:  data less than equal to 99 nodes
// postconditions: the graph is built with node data and edges extracted from the input stream.
// Assumptions:
// - The input stream contains valid data in the specified format.
// ------------------------------------------------------------------------------------------------
void GraphL::buildGraph(istream &ifs) {
  if (!ifs) {
    return;
  }

  ifs >> this->size;  // get the number of size, assume the size won't exceed 99
  string temp = "";   // tempory string to store node data
  getline(ifs, temp); // skip the white space and skip to next line

  // extracting node data
  for (int i = 1; i <= size; i++) {
    graph[i].data = new NodeData();
    graph[i].data->setData(ifs);
  }

  // extracting edge
  int from_Node = 0;
  int to_Node = 0;
  do {
    ifs >> from_Node >> to_Node;
    insertEdge(from_Node, to_Node);
  } while (from_Node != 0 && to_Node != 0);
}
// end of buildGraph

// ------------------------------------insertEdge-----------------------------------------------
// Description:
// insertEdge: function to insert an edge from one node to another
// preconditions: from_Node and to_Node are both valid index
// postconditions: an edge is inserted from the starting node to the ending node
// --------------------------------------------------------------------------------------------
void GraphL::insertEdge(int from_Node, int to_Node) {
  if ((from_Node > 0 && from_Node <= size) &&
      (to_Node > 0 && to_Node <= size)) {
    // no sorting here according to the instruction
    EdgeNode *newHead = new EdgeNode(to_Node, graph[from_Node].edgeHead);
    graph[from_Node].edgeHead = newHead;
  }
}
// end of insertEdge

// --------------------------------- GraphL::displayGraph() -----------------------------------
// Description
// displayGraph: method to display the graph
// preconditions: None
// postconditions: display the graph in given format
// --------------------------------------------------------------------------------------------
void GraphL::displayGraph() {
  cout << "Graph:" << endl;
  for (int i = 1; i <= size; i++) {
    cout << "Node " << i << "\t\t\t" << *graph[i].data << endl;
    cout << getEdges(i) << endl;
  }
}
// end of displayGraph

// -------------------------------------getEdges-----------------------------------------------
// Description:
// getEdges: function to get all edges of a node in a string 
// Preconditions: from_Node is a valid node index (1 <= from_Node <= size).
// Postconditions: return a string of edge with given format
// --------------------------------------------------------------------------------------------
string GraphL::getEdges(int from_Node) {
  string ans = ""; // string variable to store the return value
  EdgeNode *curr = graph[from_Node].edgeHead;

  while (curr) { // get every adjGraphNode value
    ans.append(" edge    " + to_string(from_Node));
    ans.append("\t" + to_string(curr->adjGraphNode) + "\n");
    curr = curr->nextEdge;
  }
  return ans;
}
// end of getEdges

// ------------------------------------depthFirstSearch--------------------------------------
// Description:
// depthFirstSearch: function to perform a depth-first search on the graph
// preconditions: the graph has been built
// postconditions: display the searching path in dfs
// -----------------------------------------------------------------------------------------
void GraphL::depthFirstSearch() {
  stack<int> s;
  s.push(1); // initalize the stack

  string ans = "Depth-first Ordering : ";

  // check all Nodes
  for (int i = 1; i <= size; i++) {
    dfsHelper(s, ans, i);
  }

  cout << ans << endl;
}
// end of depthFirstSearch

// ------------------------------------dfsHelper------------------------------------------
// Description
// dfsHelper: helper function to perform depth-first search for GraphL
// preconditions: None
// postconditions: traverse the graph in depth-first order and mark visited nodes, update
//  the stack with next node to visit
// ---------------------------------------------------------------------------------------
void GraphL::dfsHelper(stack<int> &s, string &str, int currIndex) {
  if (graph[currIndex].visited) {
    return;
  } // stop going deep if visited

  graph[currIndex].visited = true;        // mark visited
  str.append(to_string(currIndex) + " "); // append answer to the string

  EdgeNode *currNode = graph[currIndex].edgeHead;
  while (currNode) {
    dfsHelper(s, str, currNode->adjGraphNode);
    currNode = currNode->nextEdge;
  }
}
// end of dfsHelper