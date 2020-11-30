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

TEST_CASE("Correctly constructing the map and vector") {
  Graph g_("routes_testcase 1.txt", "airports_testcase 1.txt");

  REQUIRE(g_.routes.size() == 16);
  REQUIRE(g_.position.size() == 8);
}

TEST_CASE("Correctly reading the file") {
  Graph g_("routes.txt", "airports.txt");

  std::pair<std::string, std::string> VEY("63.42430114746094","-20.278900146484375");
  std::pair<std::string, std::string> THF("52.472999572753906","13.403900146484375"); 

  REQUIRE(g_.routes[0][2] == "AER");
  REQUIRE(g_.routes[0][3] == "2965");
  REQUIRE(g_.routes[0][4] == "KZN");
  REQUIRE(g_.routes[0][5] == "2990");
  REQUIRE(g_.routes[16734][2] == "PEK");  
  REQUIRE(g_.routes[16734][3] == "3364");
  REQUIRE(g_.routes[16734][4] == "JFK");
  REQUIRE(g_.routes[16734][5] == "3797");
  REQUIRE(g_.position["20"] == VEY);
  REQUIRE(g_.position["343"] == THF);
}

TEST_CASE("Generating the airport graph") {
  AirportGraph a_("routes.txt", "airports.txt");
  REQUIRE(int(a_.getEdgeWeight("BOS", "PIT"))==797);
  REQUIRE(int(a_.getEdgeWeight("HGH", "TPE"))==578);
  REQUIRE(a_.getEdgeLabel("LAX", "IND")=="LAX---to---IND");
  REQUIRE(a_.getEdgeLabel("HRK", "WAW")=="HRK---to---WAW");

}

TEST_CASE("bfs") {
  AirportGraph a_("routes3.txt", "airports.txt");
  vector<Vertex> traversal = a_.bfs("SHA");
  for (auto t : traversal) {
    std::cout << t << std::endl;
  }
  vector<Vertex> traversal2;
  traversal2.push_back("PEK");
  REQUIRE(traversal == traversal2);
}

TEST_CASE("Shortest Path 1") {
  AirportGraph a_("routes3.txt", "airports.txt");
  vector<Vertex> path = a_.shortestPath("SHA", "WIL");
  for (auto p : path) {
    std::cout << p << std::endl;
  }
  vector<Vertex> ans;
  ans.push_back("PEK");
  ans.push_back("AMS");
  ans.push_back("JRO");
  ans.push_back("WIL");
  ans.push_back("NYK");
	REQUIRE(path == ans);
}
