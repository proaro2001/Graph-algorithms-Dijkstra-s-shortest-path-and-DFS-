// ---------------------------------graphm.cpp----------------------------------------

// Programmer Name:             Choi Ka Hin
// Course:                      CSS 343
// Creation Date:               Feb 17, 2023
// Date of Last Modification:   February 18, 2023

// -----------------------------------------------------------------------------------

// Purpose: This program implements a graph using an adjacency matrix.
// It allow users to find the shortest path between vertices, displaying graph
// details, and initializing the graph by insert and delete edge functions or
// txt files
// -----------------------------------------------------------------------------------

// Notes:  The algorithm used to find the shortest path is Dijkstra's algorithm.
// Assumption: I assume user (instructor/grader) understand the actual usable
//             node is 99 nodes instead of 100

// -----------------------------------------------------------------------------------

#include "graphm.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;
const int infinity = INT_MAX; // assume infinity is max value of int

// ------------------------------------GraphM-----------------------------------------------

// Constructor

// GraphM: a constructor that initializes the GraphM object
// preconditions: None
// postconditions: the GraphM object is created
//                 all of its T[i][j] elements have their dist set to infinity,
//                 visited set to false and path set to zero.

// -----------------------------------------------------------------------------------------

GraphM::GraphM() : size(0) {
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      T[i][j].dist = infinity;
      T[i][j].visited = false;
      T[i][j].path = 0;
      C[i][j] = 0;
    }
  }
}

// End of GraphM

// -------------------------buildGraph------------------------------------

// Description:
// buildGraph: function to build a graph based on the data from the input file.
// preconditions: the input file (ifs) has been opened.
//                The input file must be formatted in the following order: size,
//                nodes' data, and the cost of each node traveling to another.
// postconditions: a graph has been built based on the data from the input file.

// -----------------------------------------------------------------------
void GraphM::buildGraph(ifstream &ifs) {
  if (ifs) {
    ifs >> this->size; // get size

    string temp = "";   // temporary string
    getline(ifs, temp); // white space

    // set Node data for each location
    for (int i = 1; i <= this->size; i++) {
      this->data[i].setData(ifs);
    }

    int from_Node = 0; // starting point
    int to_Node = 0;   // destination
    int cost = 0;      // cost to go from starting point to the destination

    // get the cost of each node traveling to another
    while (ifs >> from_Node >> to_Node >> cost) {
      if (from_Node == 0 || to_Node == 0) {
        break;
      } // stop when reach 0 0 0
      insertEdge(from_Node, to_Node, cost);
    }
  }
}
// end of buildGraph

// ---------------------- findShortestPath-----------------------------

// Description
// findShortestPath: function to find the shortest path from every node to every
// other node Preconditions: the graph has been built using buildGraph()
// Postconditions: T is updated with new shortest path information

// --------------------------------------------------------------------
void GraphM::findShortestPath() {
  // i is the row to check
  for (int source = 1; source <= size; source++) {
    T[source][source].dist = 0;
    // find the shortest distance from source to all other nodes
    dijkstra(source, source);
  }
}
// end of findShortestPath

// -----------------------findTheV-----------------------------------

// Description:
// findTheV:  helper method of findShortestPath implemented recursive function
// that finds the
//            shortest path from a given source node (from) to all other nodes
// preconditions: row and from are valid node indices, and from is already
// visited. postconditions: sets the distance and path for each node to the
// source node.

// Parameters:
// - row: the index of the source node.
// - from: the index of the starting node.

// ------------------------------------------------------------------
void GraphM::dijkstra(int row, int from) {
  T[row][from].markVisited();
  int next_from = from;
  int smallestDist = infinity;

  // check every nodes
  for (int i = 1; i <= size; i++) {
    // if not visited and it is connected
    if (!T[row][i].visited) {
      if (C[from][i] != 0) { // if has edge, update T[][]
        if (T[row][from].dist + C[from][i] < T[row][i].dist) {
          T[row][i].dist = T[row][from].dist + C[from][i];
          T[row][i].path = from;
        }
      }
      // update the next smallest one to look at
      if (T[row][i].dist < smallestDist) {
        smallestDist = T[row][i].dist;
        next_from = i;
      }
    }
  }

  // after checking every nodes, visit the next smallest
  if (next_from != from || smallestDist != infinity) {
    dijkstra(row, next_from);
  }
  // it all visited, end
}
// end of findTheV

// -------------------------getPath--------------------------------

// Description
// getPath: function to find the shortest path between two nodes
// preconditions: from and to are valid node numbers
// postconditions: returns a string that represents the shortest path between
// two nodes
//                 If no path , return nothing

// ----------------------------------------------------------------
string GraphM::getPath(int from, int to) {
  string ans = "";
  getReversePath(from, to, ans);
  reverse(ans.begin(), ans.end());
  return ans;
}
// end of getPath

// ----------------------getReversePath---------------------------

// Description:
// getReversePath: a helper method to get the reverse path from to to from
// Preconditions: data is filled, getPath function is called, and
//                the shortestPath is found as well
// Postconditions: a reverse "Path" will be returned to ans

// ---------------------------------------------------------------
void GraphM::getReversePath(int from, int to, string &ans) {
  if (!T[from][to].visited) {
    return;
  }
  if (from == to) {
    ans.append(to_string(to));
  } else {
    ans.append(to_string(to) + " ");
    getReversePath(from, T[from][to].path, ans);
  }
}
// end of getReversePath

// ------------------------displayAll-----------------------------

// Description:
// displayAll: display All information with given format
// Preconditions: findTheShortestPath is called
// Postconditions: The function displays a table in given information

// ---------------------------------------------------------------
void GraphM::displayAll() {
  cout << "Description           From node   To node       Distance      Path"
       << endl;

  for (int from = 1; from <= size; from++) {
    cout << data[from] << endl;
    for (int to = 1; to <= size; to++) {
      if (from == to) {
        continue;
      }
      cout << "                             " << from << "         " << to
           << "             "
           << (T[from][to].dist == infinity ? "---"
                                            : to_string(T[from][to].dist))
           << "         " << getPath(from, to) << endl;
    }
  }

  cout << endl;
}
// end of displayAll

// ------------------------getPath----------------------------------

// Description
// getPath: turn string to array that stores the path
// Precondition: path is valid string that only store int and space
// Postcondition: Returns a vector containing the nodes that make up the path.

// -----------------------------------------------------------------
vector<int> GraphM::getPath(string path) {
  vector<int> ret;
  if (!path.empty()) {
    for (int i = 0; i < path.size(); i += 2) {
      ret.push_back(path[i] - '0');
    }
  }
  return ret;
}
// end of getPath

// ----------------------------display------------------------------

// Description
// display: function to display the shortest path and the list of nodes
// visited in traversing from the source node to the destination node
// Precondition: from_Node and to_Node are valid nodes in the graph
// Postcondition: display information in given format

// -------------------------------------------------------------------
void GraphM::display(int from_Node, int to_Node) {
  cout << "\t" << from_Node << "\t" << to_Node << "\t"
       << (T[from_Node][to_Node].dist != infinity
               ? to_string(T[from_Node][to_Node].dist)
               : "---")
       << "\t";
  string path = getPath(from_Node, to_Node);
  cout << path << endl;
  vector<int> paths = getPath(path);
  for (int x : paths) {
    cout << data[x] << endl;
  }
  cout << endl;
}
// end of display

// ----------------------------insertEdge----------------------------

// Description
// insertEdge: function to insert an edge between two nodes in the graph
// Precondition: from_Node and to_Node are valid inputs
// Postcondition: An edge is inserted between the two specified nodes in the
// graph with the given cost

// ------------------------------------------------------------------
void GraphM::insertEdge(int from_Node, int to_Node, int cost) {
  C[from_Node][to_Node] = cost;
}
// end of insertEdge

// -----------------------removeEdge------------------------------===

// Description
// removeEdge: function to remove an edge between two nodes in the graph
// Precondition: from_Node and to_Node are valid nodes
// Postcondition: The edge between the two specified nodes in the graph is
// removed

// -------------------------------------------------------------------
void GraphM::removeEdge(int from_Node, int to_Node) {
  C[from_Node][to_Node] = 0;
}
// end of removeEdge