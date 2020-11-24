#pragma once

#include <string>
#include <map>
#include <vector>

class shortest_path
{
    public: 
    void read_route(const std::string& filename);
    void read_airports(const std::string& filename);
    std::vector<std::vector<std::string>> routes;
    std::map<std::string, std::pair<std::string, std::string>> position;
};