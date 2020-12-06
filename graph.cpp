#include "graph.h"

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel);


Graph::Graph(const std::string& file_routes, const std::string& file_airports){
    routes = read_route(file_routes);
    position = read_airports(file_airports);
    ID = getID(file_airports);
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
            //store one route in to the collection of the routes
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

std::map<std::string, std::string> Graph::getID(const std::string& filename){
    std::map<std::string, std::string> ID;
    ifstream wordsFile(filename);
    string airport_id;
    string name;
    string city;
    string country;
    string iata;
    string icao;
    string other_info;
    if (wordsFile.is_open()) {
        while(wordsFile.good()){
            getline(wordsFile, airport_id,',');
            getline(wordsFile, name,',');
            getline(wordsFile, city,',');
            getline(wordsFile, country,',');
            getline(wordsFile, iata,',');
            getline(wordsFile, icao,',');
            getline(wordsFile, other_info,'\n');//other useless
            string iata_clean = iata.substr(1, iata.length()-2);
            if(ID.find(iata_clean)==ID.end()){
                ID[iata_clean] = airport_id;//storing the information needed in to the dictionary
            }
            string icao_clean = icao.substr(1, icao.length()-2);
            if(ID.find(icao_clean)==ID.end()){
                ID[icao_clean] = airport_id;//storing the information needed in to the dictionary
            }
        }
    }
     wordsFile.close();
     return ID;
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

vector<Edge> Graph::incidentEdges(Vertex v) const
{
    if (adjacency_list.empty())
        return vector<Edge>();
    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        if(source == v){
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
    }
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

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    return new_edge;
}


string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
}

double Graph::getEdgeWeight(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}


Vertex Graph::removeVertex(Vertex v)
{
    if (adjacency_list.find(v) != adjacency_list.end())
    {   
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
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

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    
    return e;
}


Edge Graph::setEdgeWeight(Vertex source, Vertex destination, double weight)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    //std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;
    return new_edge;
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


void Graph::clear()
{
    adjacency_list.clear();
}


/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}


/**
 * Prints the graph to stdout.
 */
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

