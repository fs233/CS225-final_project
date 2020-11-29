#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "math.h"
#include "graph.h"
#include "graph_algorithms.h"
#include "edge.h"
#include "read_from_file.h"

using std::string;
using std::vector;
using std::ifstream;


int main() {
  AirportGraph a_("routes.txt", "airports.txt");
  vector<Vertex> path = a_.shortestPath("PEK", "NYK");
  for (auto i : path) {
    cout << i << endl;
  }
}