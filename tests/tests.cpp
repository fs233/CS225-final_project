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

TEST_CASE("BFS Traversal 1") {
  AirportGraph a_("routes_testcase 1.txt", "airports_testcase 1.txt");
  vector<Vertex> traversal = a_.bfs("FCO");
  vector<Vertex> traversal2;
  traversal2.push_back("FCO");
  traversal2.push_back("TIA");
  traversal2.push_back("PMO");
  traversal2.push_back("DME");
  traversal2.push_back("CTA");
  traversal2.push_back("BLQ");
  traversal2.push_back("BGY");
  traversal2.push_back("BRI");
  REQUIRE(traversal == traversal2);
}

TEST_CASE("BFS Traversal 2") {
  AirportGraph a_("routes_testcase 2.txt", "airports_testcase 2.txt");
  vector<Vertex> traversal = a_.bfs("PEK");
  vector<Vertex> test;
  test.push_back("PEK");
  test.push_back("SZX");
  test.push_back("NNG");
  test.push_back("CSX");
  test.push_back("CAN");
  test.push_back("TYN");
  test.push_back("WUH");
  test.push_back("CGO");
  test.push_back("KWL");
  test.push_back("HLD");
  REQUIRE(traversal == test);
}

TEST_CASE("Shortest Path") {
  AirportGraph a_("routes_testcase 1.txt", "airports_testcase 1.txt");
  vector<Vertex> path = a_.shortestPath("BGY", "DME");
  vector<Vertex> ans;
  ans.push_back("BGY");
  ans.push_back("TIA");
  ans.push_back("FCO");
  ans.push_back("DME");
	REQUIRE(path == ans);
}
