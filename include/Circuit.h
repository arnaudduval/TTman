#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include <list>
#include <GPSPoint.h>
#include <GPXFile.h>


struct Point
{
  GPSPoint coords;
  double alt;
  double azimuth;
  
  Point(){};
  Point(const GPSPoint&, const double&);

};


class Circuit : public std::list<Point>
{
  public :
    // Default constructor
    Circuit() : std::list<Point>() {};
  
    // Constructor form a GPX file
    Circuit(const GPXFile&);
  
  private :
    void ComputeAzimuth();
};





#endif