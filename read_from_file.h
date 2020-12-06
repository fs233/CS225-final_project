#pragma once

#include <string>
#include <map>
#include <vector>

class readfile
{
    public: 
    std::vector<std::vector<std::string>> read_route(const std::string& filename);
    std::map<std::string, std::pair<std::string, std::string>> read_airports(const std::string& filename);
    std::map<std::string, std::string> getID(const std::string& filename);
};