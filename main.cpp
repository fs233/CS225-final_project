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

/*AirportGraph::AirportGraph(const std::string& file_routes, const std::string& file_airports): g_(file_routes, file_airports){
    //Graph g_(file_routes, file_airports);//construct the graph with the data
    int count = 0;
    std::cout<<"R size: "<<g_.routes.size()<<std::endl;
    std::cout<<"A size: "<<g_.position.size()<<std::endl;
    for(unsigned i = 0; i<g_.routes.size(); i++)
    {
        if(!g_.routes[i].empty()){
            Vertex source_id = g_.routes[i][3];//get the source vertex
            Vertex destination_id = g_.routes[i][5];//get the dest vertex
            std::pair<std::string, std::string> s = g_.position[source_id];
            std::pair<std::string, std::string> d = g_.position[destination_id];
            double weight = Distance(s, d);
            string source_code = g_.routes[i][2];//get the source vertex
            string destination_code = g_.routes[i][4];//get the dest vertex
            g_.insertEdge(source_id, destination_id, weight, source_code+"---to---"+destination_code);
            count++;
        }
    } 
    std::cout<<"insert count: "<<count<<std::endl;  
    std::cout<<"adj size:"<<g_.adjacency_list.size()<<std::endl;
}

double AirportGraph::Distance(std::pair<std::string, std::string> s, std::pair<std::string, std::string> d){
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
std::vector<std::vector<std::string>> Graph::read_route(const std::string& filename){
    std::vector<std::vector<std::string>> routes;
    ifstream wordsFile(filename);
    string airline;
    string airline_id;
    string source;
    string source_id;
    string destination;
    string destination_id;
    string other_info;

    if (wordsFile.is_open()) {
        while(wordsFile.good()){
            std::vector<std::string> one_route;
            //reading information form each line of the file
            getline(wordsFile, airline,',');
            getline(wordsFile, airline_id,',');
            getline(wordsFile, source,',');
            getline(wordsFile, source_id,',');
            getline(wordsFile, destination,',');
            getline(wordsFile, destination_id,',');
            getline(wordsFile, other_info,'\n');
            //storing the information into the vec
            one_route.push_back(airline);
            one_route.push_back(airline_id);
            one_route.push_back(source);
            one_route.push_back(source_id);
            one_route.push_back(destination);
            one_route.push_back(destination_id);
            one_route.push_back(other_info);
            //strong one route in to the collection of the routes
            routes.push_back(one_route);
        }
    }
    wordsFile.close();
    return routes;
}

std::map<std::string, std::pair<std::string, std::string>> Graph::read_airports(const std::string& filename){
    std::map<std::string, std::pair<std::string, std::string>> position;
    ifstream wordsFile(filename);
    string airport_id;
    string name;
    string city;
    string country;
    string iata;
    string icao;
    string lati;
    string longi;
    string alti;
    string other_info;
    if (wordsFile.is_open()) {
        while(wordsFile.good()){
            getline(wordsFile, airport_id,',');
            getline(wordsFile, name,',');
            getline(wordsFile, city,',');
            getline(wordsFile, country,',');
            getline(wordsFile, iata,',');
            getline(wordsFile, icao,',');
            getline(wordsFile, lati,',');//get lati
            getline(wordsFile, longi,',');//get longi
            getline(wordsFile, other_info,'\n');//other useless
            if(position.find(airport_id)==position.end()){
                position[airport_id] = std::make_pair(lati, longi);//storing the information needed in to the dictionary
            }
        }
    }
     wordsFile.close();
     return position;
}

Graph::Graph(const std::string& file_routes, const std::string& file_airports){
    routes = read_route(file_routes);
    position = read_airports(file_airports);
}

double Distance(std::pair<std::string, std::string> s, std::pair<std::string, std::string> d){
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

bool Graph::insertEdge(Vertex source, Vertex destination, double weight, std::string label)
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exit
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination, weight, label);
    
    return true;
}


void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(40) << vertexColumn;
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(40) << edgeColumn;
            cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

void AirportGraph::print(){
    g_.print();
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

vector<Edge> AirportGraph::getEdges() const
{
    return g_.getEdges();
}

vector<Vertex> Graph::getAdjacent(Vertex source) const 
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}


Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
            }
        }
    }

    return ret;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source + " -> " + destination);
        return false;
    }
    return true;
}

void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}
*/

int main() {
    AirportGraph a_("routes.txt", "airports.txt");
    //a_.print();
    vector<Vertex> airp = a_.getVertices();
    vector<Edge> routes = a_.getEdges();
    std::cout<<airp.size()<<std::endl;
    std::cout<<routes.size()<<std::endl;

}