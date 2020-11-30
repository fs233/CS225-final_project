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

 
  if(longi1-longi2)<=-180){
      double temp=lati1+(lati2-lati1)*(longi1+180.0)/(longi1-longi2+360.0)
      drawline(image,lati1,longi1,temp,-180.0);
      drawline(image,lati2,longi2,temp,180.0);
      return
  }
  else if(longi1-longi2)>=180){
      double temp=lati2+(lati1-lati2)*(longi2+180.0)/(longi2-longi1+360.0)
      drawline(image,lati2,longi2,temp,-180.0);
      drawline(image,lati1,longi1,temp,180.0);
      return
  }else{
    if (longi1<longi2) int stepi=1 else int stepi=-1;
    if (lati1>lati2) int stepj=1; else int stepj=-1;
    unsigned int x1=unsigned int(width/2 + (longi1/360)*width);
    unsigned int y1=unsigned int(height/2 - (lati1/180)*height);
    unsigned int x2=unsigned int(width/2 + (longi2/360)*width);
    unsigned int y2=unsigned int(height/2 - (lati2/180)*height);
    for (unsigned i = x1; (int)i*stepi <= (int)x2*stepi; i+=stepi) {
    for (unsigned j = y1; (int)j*stepj <= (int)y2*stepj; j+=stepj) {
          //to be continue
      }
    }
  }


  return;
}



