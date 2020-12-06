#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "drawmap.h"
#include <string>
#include <iostream>
#include <cstdlib>


cs225::PNG* opennewmap()
{
  cs225::PNG* image=new cs225::PNG();
  image->readFromFile("map.png");
  return image;
  
}

void outputmap(cs225::PNG* image)
{
  image->writeToFile("outputmap.png");
  delete image;
  return;
}

void drawpoint(cs225::PNG* image,double lati,double longi)
{
    unsigned int width= image->width(),height=image->height();
    
    unsigned int x=(unsigned int)(width/2 + (longi/360)*width);
    unsigned int y=(unsigned int)(height/2 - (lati/180)*height);

    for (unsigned i = x-2; i <= x+2; i++) {
    for (unsigned j = y-2; j <= y+2; j++) {
      cs225::HSLAPixel & pixel = image->getPixel(i, j);
      pixel.h=0.0;
      pixel.s=1.0;
      pixel.l=0.5;
    }
    }
    return;
}
//use bensenhame alg to draw lines

void drawline(cs225::PNG* image,double lati1,double longi1,double lati2,double longi2)
{
  unsigned int width= image->width(),height=image->height();

 // if (longi1>longi2){drawline(image,lati2,longi2,lati1,longi1); return;}  
  if((longi1-longi2)<=-180){
      double temp=lati1+(lati2-lati1)*(longi1+180.0)/(longi1-longi2+360.0);
      drawline(image,lati1,longi1,temp,-180.0);
      drawline(image,lati2,longi2,temp,180.0);
      //std::cout<<" temp"<<temp;
      return;
  }
  else if((longi1-longi2)>=180){
      double temp=lati2+(lati1-lati2)*(longi2+180.0)/(longi2-longi1+360.0);
      drawline(image,lati2,longi2,temp,-180.0);
      drawline(image,lati1,longi1,temp,180.0);
      //std::cout<<" temp"<<temp;
      return;
  }
  else{
    //int stepi,stepj;
    //if (longi1<longi2) stepi=1; else  stepi=-1;
    //if (lati1>lati2)  stepj=1; else  stepj=-1;
    unsigned int x1=(unsigned int)(width/2 + (longi1/360)*width);
    unsigned int y1=(unsigned int)(height/2 - (lati1/180)*height);
    unsigned int x2=(unsigned int)(width/2 + (longi2/360)*width);
    unsigned int y2=(unsigned int)(height/2 - (lati2/180)*height);
    
    if ((std::abs((int)(y2-y1)))<(std::abs((int)(x2-x1)))){
      if (x1>x2) drawlinelow(image,x2,y2,x1,y1);
        else drawlinelow(image,x1,y1,x2,y2);
    }
    else{
      if (y1>y2) drawlinehigh(image,x2,y2,x1,y1);
      else drawlinehigh(image,x1,y1,x2,y2);
    }


    //double k=(double)(x2-x1)/(double)(y2-y1);
   /* int m_new =2* (y2-y1);
    int slope_err =m_new -(x2 -x1);
    std::cout<<"  x1y1x2y2"<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<' ';
    for (unsigned i = x1,j = y1; (int)i*stepi < (int)x2*stepi; i+=stepi)
    {
      cs225::HSLAPixel & pixel = image->getPixel(i, j);
            pixel.h=0.0;
            pixel.s=1.0;
            pixel.l=0.5;
      slope_err+= m_new;
      while (stepi*slope_err>=0){
        j+=stepj;
        slope_err-=2*(x2-x1);
        cs225::HSLAPixel & pixel = image->getPixel(i, j);
            pixel.h=0.0;
            pixel.s=1.0;
            pixel.l=0.5;
      }
    }

for (unsigned i = x1; (int)i*stepi <= (int)x2*stepi; i+=stepi) {
    for (unsigned j = y1; (int)j*stepj <= (int)y2*stepj; j+=stepj) {
          if ((double)(i-x1)/(double)(j-y1)>=(k*0.99) &&(double)(i-x1)/(double)(j-y1)<=(k*1.01)){
            cs225::HSLAPixel & pixel = image->getPixel(i, j);
            pixel.h=0.0;
            pixel.s=1.0;
            pixel.l=0.5;
          }
      }
    }*/
  }


  return;
}

//helper
void drawlinehigh(cs225::PNG* image,int x1, int y1,int x2,int y2)
{
  int dx=x2-x1,dy=y2-y1,xi=1;
  if (dx<0)
  {
    xi=-1;
    dx =-dx;
  }
  int D=(2*dx) -dy;
  int x=x1;
  for (int y=y1;y<y2;y++){
    cs225::HSLAPixel & pixel = image->getPixel(x, y);
            pixel.h=0.0;
            pixel.s=1.0;
            pixel.l=0.5;
    if (D>0){
      x=x+xi;
      D=D+(2*(dx-dy));
    }
    else D=D+2*dx;
  }
  return;
}
void drawlinelow(cs225::PNG* image,int x1, int y1,int x2,int y2)
{
  int dx=x2-x1,dy=y2-y1,yi=1;
  if (dy<0)
  {
    yi=-1;
    dy =-dy;
  }
  int D=(2*dy) -dx;
  int y=y1;
  for (int x=x1;x<x2;x++){
    cs225::HSLAPixel & pixel = image->getPixel(x, y);
            pixel.h=0.0;
            pixel.s=1.0;
            pixel.l=0.5;
    if (D>0){
      y=y+yi;
      D=D+(2*(dy-dx));
    }
    else D=D+2*dy;
  }
  return;
}

void draw_map(const std::string& file_routes, const std::string& file_airports, Vertex start, Vertex end)
{
  cs225::PNG* image;
	image=opennewmap();
  AirportGraph a_(file_routes, file_airports);
  vector<Vertex> path = a_.shortestdijkstra(start, end);
  for(unsigned i = 0; i<path.size()-1; i++)
  {
    string id  = a_.ID[path[i]];
    string id_next  = a_.ID[path[i+1]];
    drawpoint(image, std::atof(a_.position[id].first.c_str()), std::atof(a_.position[id].second.c_str()));
    drawpoint(image, std::atof(a_.position[id_next].first.c_str()), std::atof(a_.position[id_next].second.c_str()));
    drawline(image,std::atof(a_.position[id].first.c_str()), std::atof(a_.position[id].second.c_str()), std::atof(a_.position[id_next].first.c_str()), std::atof(a_.position[id_next].second.c_str()));
  }

	outputmap(image);
}

//test only
int main()
{
	/*cs225::PNG* image;
	image=opennewmap();
  drawpoint(image,39.5,115.5);
  drawpoint(image,30.5,120.5);
  drawpoint(image,47.3,-122.1);
  drawpoint(image,40.6,-73.9);


  drawline(image,30.5,120.5,39.5,115.5);
  drawline(image,47.3,-122.1,30.5,120.5);
  drawline(image,47.3,-122.1,40.6,-73.9);*/
  draw_map("routes.txt", "airports.txt", "CGO", "ORD");
	return 0;
}

