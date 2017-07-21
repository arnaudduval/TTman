#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include <list>
#include <GPSPoint.h>


struct Point
{
  GPSPoint coords;
  double alt;
  double azimuth;
};


class Circuit : public std::list<Point>
{
  void ComputeAzimuth();
};





#endif