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

double Distance(std::pair<std::string, std::string> s, std::pair<std::string, std::string> d)
{
    double s_lati = std::atof(s.first.c_str());
    double s_longi = std::atof(s.second.c_str());
    double d_lati = std::atof(d.first.c_str());
    double d_longi = std::atof(d.second.c_str());
    double rad_s_lati = s_lati*3.1415926/180.0;
    double rad_d_lati = d_lati*3.1415926/180.0;
    double a = rad_s_lati-rad_d_lati;
    double b = s_longi*3.1415926/180.0 -  d_longi*3.1415926/180.0;
    double l = 2 * asin(sqrt(pow(sin(a/2),2) + cos(rad_s_lati)*cos(rad_d_lati)*pow(sin(b/2),2)));
    double distance  = l * 6378.137;
    return distance;
}

int main() {
  /*AirportGraph a_("routes.txt", "airports.txt");
  vector<Vertex> path = a_.shortestPath("PEK", "NYK");
  for (auto i : path) {
    cout << i << endl;
  }*/

  std::pair<std::string, std::string> PMO("38.175999","13.091");
  std::pair<std::string, std::string> BRI("41.138901","16.760599"); 
  std::cout<<Distance(PMO, BRI)<<std::endl;
}