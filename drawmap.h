#pragma once

#include "cs225/PNG.h"
#include "graph.h"
#include "edge.h"
#include "graph_algorithms.h"
#include "read_from_file.h"
#include <string>

cs225::PNG* opennewmap(); 
void drawpoint(cs225::PNG* image,double lati,double longi);
void drawline(cs225::PNG* image,double lati1,double longi1,double lati2,double longi2);
void outputmap(cs225::PNG* image);
void drawlinehigh(cs225::PNG* image,int x1, int y1,int x2,int y2);

void drawlinelow(cs225::PNG* image,int x1, int y1,int x2,int y2);

/**
* draw the shortest path out in output map
* @param file_routes - file with the routes
* @param file_airports - file with the airports
* @param start - the code of the starting airport
* @param end - the code of the dest
* */
void draw_map(const std::string& file_routes, const std::string& file_airports, Vertex start, Vertex end);

int main();
