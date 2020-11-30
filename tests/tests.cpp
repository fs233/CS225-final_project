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

TEST_CASE("Correctly reading the file") {
  Graph g_("routes_testcase 1.txt", "airports_testcase 1.txt");

  REQUIRE(g_.routes.size() == 16);
  REQUIRE(g_.position.size() == 8);
  
 //BV,1463,BGY,1525,TIA,1190,,0,737
  REQUIRE(g_.routes[0][2] == "BGY");
  REQUIRE(g_.routes[0][3] == "1525");
  REQUIRE(g_.routes[0][4] == "TIA");
  REQUIRE(g_.routes[0][5] == "1190");
  //BV,1463,FCO,1555,PMO,1512,,0,737
  REQUIRE(g_.routes[8][2] == "FCO");
  REQUIRE(g_.routes[8][3] == "1555");
  REQUIRE(g_.routes[8][4] == "PMO");
  REQUIRE(g_.routes[8][5] == "1512");
  
  std::pair<std::string, std::string> TIA("41.4146995544","19.7206001282");
  std::pair<std::string, std::string> FCO("41.8002778","12.2388889"); 
  REQUIRE(g_.position["1190"] == TIA);
  REQUIRE(g_.position["1555"] == FCO);

}

TEST_CASE("Generating the airport graph correctly") {
  AirportGraph a_("routes_testcase 1.txt", "airports_testcase 1.txt");
  REQUIRE(int(a_.getEdgeWeight("TIA", "FCO"))==624);
  REQUIRE(int(a_.getEdgeWeight("PMO", "BRI"))==455);
  REQUIRE(a_.getEdgeLabel("BLQ", "TIA")=="BLQ---to---TIA");
}

TEST_CASE("bfs") {
  AirportGraph a_("routes3.txt", "airports.txt");
  vector<Vertex> traversal = a_.bfs("SHA");
  for (auto t : traversal) {
    std::cout << t << std::endl;
  }
  vector<Vertex> traversal2;
  traversal2.push_back("SHA");
  traversal2.push_back("PEK");
  traversal2.push_back("JFK");
  traversal2.push_back("NRT");
  traversal2.push_back("LHR");
  traversal2.push_back("SYD");
  traversal2.push_back("LAX");
  REQUIRE(traversal == traversal2);
}

/*TEST_CASE("Shortest Path 1") {
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
}*/
