#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>



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
    
    unsigned int x=unsigned int(width/2 + (longi/360)*width);
    unsigned int y=unsigned int(height/2 - (lati/180)*height);

    for (unsigned i = x-1; i <= x+1; i++) {
    for (unsigned j = y-1; j <= y+1; j++) {
      cs225::HSLAPixel & pixel = image->getPixel(i, j);
      pixel.h=0.0;
      pixel.s=1.0;
      pixel.l=0.5;
    }
    }
    return;
}

void drawline(cs225::PNG* image,double lati1,double longi1,double lati2,double longi2)
{
  unsigned int width= image->width(),height=image->height();


  return;
}



