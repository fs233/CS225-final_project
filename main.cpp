#include <string>
#include <iostream>
#include <vector>
#include "final.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;
int main() {
    /*ifstream wordsFile("routes.txt");
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
            //routes.push_back(one_route);
            std::cout<<one_route[0]<<std::endl;
        }
    }
    wordsFile.close();*/
    std::map<std::string, std::pair<string, string>> position;
    ifstream wordsFile("airports.txt");
    string airport_id;
    string name;
    string city;
    string country;
    string iata;
    string icao;
    string lati;
    string longi;
   // string alti;
    string other_info;
    if (wordsFile.is_open()) {
        while(wordsFile.good()){
            getline(wordsFile, airport_id,',');
            getline(wordsFile, name,',');
            getline(wordsFile, city,',');
            getline(wordsFile, country,',');
            getline(wordsFile, iata,',');
            getline(wordsFile, icao,',');
            getline(wordsFile, lati,',');
            getline(wordsFile, longi,',');
            getline(wordsFile, other_info,'\n');
            if(position.find(airport_id)==position.end()){
                position[airport_id] = std::make_pair(lati, longi);
            }
        }
    }
     wordsFile.close();
     std::cout<<position[std::to_string(1)].first<<std::endl;
}