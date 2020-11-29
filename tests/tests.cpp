#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "../graph.h"
#include "../edge.h"

#include "../graph_algorithms.h"
#include "../catch/catch.hpp"
#include "../read_from_file.h"


TEST_CASE("h") {
  AirportGraph a_("routes.txt", "airports.txt");
  vector<Vertex> path = a_.shortestPath("PEK", "NYK");

  vector<Vertex> path2;
  path2.push_back("PEK");
  path2.push_back("AMS");
  path2.push_back("JRO");
  path2.push_back("WIL");
  path2.push_back("NYK");
	REQUIRE(path == path2);
}
