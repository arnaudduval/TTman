#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__


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