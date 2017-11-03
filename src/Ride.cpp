#include <Ride.h>
#include <TCXFile.h>


Ride::Ride(TCXFile f)
{
  // Copy data from TCX file structure
  int i = 0;
  for(auto iterActivities = f.activities.begin() ; iterActivities != f.activities.end() ; ++iterActivities)
  {
    for(auto iterLaps = (*iterActivities).laps.begin() ; iterLaps != (*iterActivities).laps.end() ; ++iterLaps)
    {
      ++i;
      for(auto it = (*iterLaps).track.begin() ; it != (*iterLaps).track.end() ; ++it)
      {
        RidePoint p;
        p.timeStamp = (*it).time;
        p.point.coords = (*it).coords;
        p.point.alt = (*it).altitudeMeters;
        p.distance = (*it).distanceMeters;
        p.heartRate = (*it).heartRateBPM;
        p.cadence = (*it).cadence;
        p.speed = (*it).speed;
        p.power = (*it).watts;
        p.iLap = i;
        
        points.push_back(p);
      }
    }
  }
 
  // Compute azimuth for each point
  for(auto i = 0 ; i < points.size() ; ++i)
  {
    if(i != points.size()-2)
      points[i].point.azimuth = Azimuth(points[i].point.coords, points[i+1].point.coords);
    else // cas du dernier point
      points[i].point.azimuth = points[i-1].point.azimuth;
  }
  
  // Compute dt for each point
  // Pour le moment on ne se casse pas la tête mais il faudra faire autrement et réparer les trous
  dt = 1.;
}