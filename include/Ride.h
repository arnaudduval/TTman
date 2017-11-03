#ifndef __RIDE_H__
#define __RIDE_H__

#include <Circuit.h>
#include <TCXFile.h>

struct RidePoint
{
  std::string timeStamp;
  Point point;
  double distance;
  double power;
  double speed;
  int heartRate;
  int cadence;
  int iLap;
};


struct Ride
{
  double dt;            // sampling rate
  std::vector<RidePoint> points;
  
  Ride(TCXFile);
};



#endif