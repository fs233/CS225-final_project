#pragma once
#include "edge.h"
#include "graph.h"
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

class AirportGraph
{
    public: 

    //constructor of the airport graph using the data provided
    AirportGraph(const std::string& file_routes, const std::string& file_airports); 

    /**
     * takes the position pair and calculate the distance in km
     * @param s, d the pair of latitude and longitude stored in the map posistion
     * */
    double Distance(std::pair<std::string, std::string> s, std::pair<std::string, std::string> d); 
    
    /**
     * Gets all adjacent vertices to the parameter vertex.
     * @param source - vertex to get neighbors from
     * @return a vector of vertices
     */
    vector<Vertex> getAdjacent(Vertex source) const;

    /**
     * Returns one vertex in the graph. This function can be used
     *  to find a random vertex with which to start a traversal.
     * @return a vertex from the graph
     */
    Vertex getStartingVertex() const;

    /**
     * Gets all vertices in the graph.
     * @return a vector of all vertices in the graph
     */
    vector<Vertex> getVertices() const;
    

    /**
     * Gets an edge between two vertices.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if exist, return the corresponding edge
     *         - if edge doesn't exist, return Edge()
     */
    Edge getEdge(Vertex source, Vertex destination) const;

    /**
     * get the edges that has Vertex v as the source
     * @param - a vertex
     * @return - a vector of edges 
     */ 
    vector<Edge> incidentEdges(Vertex v) const;
   
    /**
     * Gets all the edges in the graph.
     * @return a vector of all the edges in the graph
     */
    vector<Edge> getEdges() const;

    /**
     * Gets the edge label of the edge between vertices u and v.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if edge exists, return edge label
     *         - if edge doesn't exist, return InvalidLabel
     */
    string getEdgeLabel(Vertex source, Vertex destination) const;

    /**
     * Gets the weight of the edge between two vertices.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if edge exists, return edge wright
     *         - if doesn't, return InvalidWeight
     */
    double getEdgeWeight(Vertex source, Vertex destination) const;

    /**
     * print out the airport graph created
     */
    void print();

    vector<Vertex> bfs(const Vertex start);

    vector<Vertex> shortestdijkstra(const Vertex start, const Vertex end);

    std::vector<std::vector<std::string>> routes; //vector containing all information from the route
    
    std::map<std::string, std::pair<std::string, std::string>> position;

    std::map<std::string, std::string> ID;

    private:

    Graph g_;

    
};