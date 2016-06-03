#ifndef __GPSPOINT_H__
#define __GPSPOINT_H__


#define EARTH_RADIUS 6371.
#define EPS_GPS  1.E-10     

struct GPSPoint
{
  double lat;
  double lon;
};





// This function computes the distance between 2 GPS Points
double Distance(const GPSPoint& , const GPSPoint& );

// This function computes the azimuth from one GPS point to another
double Azimuth(const GPSPoint& , const GPSPoint& );





#endif