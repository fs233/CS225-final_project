#pragma once

#include "cs225/PNG.h"

#include <string>
cs225::PNG* opennewmap(); 
void drawpoint(cs225::PNG* image,double lati,double longi);
void drawline(cs225::PNG* image,double lati1,double longi1,double lati2,double longi2);
void outputmap(cs225::PNG* image);
void drawlinehigh(cs225::PNG* image,int x1, int y1,int x2,int y2);

void drawlinelow(cs225::PNG* image,int x1, int y1,int x2,int y2);

int main();
