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
using namespace std;

AirportGraph::AirportGraph(const std::string& file_routes, const std::string& file_airports): g_(file_routes, file_airports)
{
    for(unsigned i = 0; i<g_.routes.size(); i++)
    {
        if(!g_.routes[i].empty()){
            Vertex source_id = g_.routes[i][3];//get the source vertex
            Vertex destination_id = g_.routes[i][5];//get the dest vertex
            double weight = 0.0;
            if(source_id != "/N" && destination_id != "/N"){
                std::pair<std::string, std::string> s = g_.position[source_id];
                std::pair<std::string, std::string> d = g_.position[destination_id];
                weight = Distance(s, d);
            }
            string source_code = g_.routes[i][2];//get the source vertex
            string destination_code = g_.routes[i][4];//get the dest vertex
            g_.insertEdge(source_code, destination_code, weight, source_code+"---to---"+destination_code);
        }
    } 
}

double AirportGraph::Distance(std::pair<std::string, std::string> s, std::pair<std::string, std::string> d)
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

/**
 * add functions in this place 
 * put the functions below at the bottom
 * */

vector<Vertex> AirportGraph::bfs(const Vertex start) {
    unordered_map<Vertex, bool> visited;
    queue<Vertex> q;
    vector<Vertex> traversal; 
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        Vertex v = q.front();
        traversal.push_back(v);
        q.pop();
        vector<Vertex> adjacents = g_.getAdjacent(v);
        for (auto a : adjacents) {
            if (!visited[a]) {
                visited[a] = true;
                q.push(a);
            }
        }
    }
    return traversal;
}

vector<Vertex> AirportGraph::shortestPath(const Vertex start, const Vertex end) {
    unordered_map<Vertex, bool> visited;
    unordered_map<Vertex, Vertex> pred;
    queue<Vertex> q;

    visited[start] = true;
    q.push(start);
    while(!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adjacents = g_.getAdjacent(v);
        for (auto a : adjacents) {
            if (g_.getEdgeWeight(v, a) == 0) {
                continue;
            }
            if (!visited[a]) {
                visited[a] = true;
                pred[a] = v;
                q.push(a);
                if (a == end) {
                    break;
                }
            }
        }
    }
    vector<Vertex> path;
    Vertex p = end;
    while (p != start) {
        path.push_back(p);
        p = pred[p];
    }
    p = start;
    path.push_back(p);
    reverse(path.begin(), path.end());
    return path;
}


vector<Vertex> AirportGraph::shortestdijkstra(const Vertex start, const Vertex end) {
  //double max = std::numeric_limits<double>::max();
  unordered_map<Vertex, int> dist;
  unordered_map<Vertex, Vertex> P;
  vector<Vertex> wr = g_.getVertices();
  vector<Vertex> q;
  Vertex k;
  vector<Vertex> path;
  for (auto a : wr) {
    dist[a] = 100000;
    P[a] = k;
    q.push_back(a);
  }
  dist[start] = 0;
  while (!q.empty()) {
    int u = 100000;
    Vertex o;
    for (auto i : q) {
      if (dist[i] <= u) {
        u = dist[i];
        o = i;
      }
    }
    vector<Vertex> qq = q;
    q.clear();
    for (auto a : qq) {
      if (a == o) {
        continue;
      }
      q.push_back(a);
    }
    if (P[end] != k) {
      Vertex ppp = end;
      while (ppp != k) {
         path.push_back(ppp);
         ppp = P[ppp];
         //if (P[ppp] == start) {
           //break;
         //}
      }
      break;
    }
    vector<Vertex> adjacents = g_.getAdjacent(o);
    for (auto a : adjacents) {
      if (g_.getEdgeWeight(o, a) + dist[o] < dist[a]) {
        dist[a] = g_.getEdgeWeight(o, a) + dist[o];
        P[a] = o;
      }
    }
    
  }
  
  reverse(path.begin(), path.end());
  return path;
}

vector<Vertex> AirportGraph::getAdjacent(Vertex source) const
{
    return g_.getAdjacent(source);
}

Vertex AirportGraph::getStartingVertex() const
{
    return g_.getStartingVertex();
}

vector<Vertex> AirportGraph::getVertices() const{
    return g_.getVertices();
}

Edge AirportGraph::getEdge(Vertex source, Vertex destination) const
{
    return g_.getEdge(source, destination);
}

vector<Edge> AirportGraph::incidentEdges(Vertex v) const
{
    return g_.incidentEdges(v);
}

vector<Edge> AirportGraph::getEdges() const
{
    return g_.getEdges();
}

string AirportGraph::getEdgeLabel(Vertex source, Vertex destination) const
{
    return g_.getEdgeLabel(source, destination);
}

double AirportGraph::getEdgeWeight(Vertex source, Vertex destination) const
{
    return g_.getEdgeWeight(source, destination);
}

void AirportGraph::print(){
    g_.print();
}