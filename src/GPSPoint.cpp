#include <cmath>
#include <stdexcept>

#include <GPSPoint.h>


// This function computes the distance between 2 GPS Points
double Distance(const GPSPoint& ptA, const GPSPoint& ptB)
{
  double a = ptA.lat*M_PI/180.;
  double b = ptB.lat*M_PI/180.;
  double c = ptA.lon*M_PI/180.;
  double d = ptB.lon*M_PI/180.;
  return EARTH_RADIUS*acos(sin(a)*sin(b) + cos(a)*cos(b)*cos(c-d));
}

// This function computes the azimuth from one GPS point to another
double Azimuth(const GPSPoint& ptA, const GPSPoint& ptB)
{
  double a = ptA.lat*M_PI/180.;
  double b = ptB.lat*M_PI/180.;
  double c = ptA.lon*M_PI/180.;
  double d = ptB.lon*M_PI/180.;
  
  if((std::abs(a-b) < EPS_GPS)||(std::abs(c-d) < EPS_GPS))
    return 0.;
    //throw std::runtime_error("Start and finish point are nearly the same.");
  
  double tc1;
  if( cos(a) < EPS_GPS)
  {
    if(a> 0.)
      tc1 = M_PI;               // Start from N pole
    else
      tc1 = 2.*M_PI;            // Start from S pole
  }
  else
  {
    double dist = acos(sin(a)*sin(b) + cos(a)*cos(b)*cos(c-d));

    if(sin(c-d) < 0.)
    {
      tc1 = acos((sin(b)-sin(a)*cos(dist))/(sin(dist)*cos(a)));
    }
    else
    {
      tc1 = 2.*M_PI -  acos((sin(b)-sin(a)*cos(dist))/(sin(dist)*cos(a)));
    }
  }
  return tc1*180./M_PI;
}
