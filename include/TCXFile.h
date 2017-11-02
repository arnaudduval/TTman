#ifndef __TCXFILE_H__
#define __TCXFILE_H__

#include <string>
#include <list>
#include <tuple>
#include <libxml++/libxml++.h>
#include <GPSPoint.h>


struct TCXTrackPoint
{
  std::string time;
  GPSPoint coords;
  double altitudeMeters;
  double distanceMeters;
  int heartRateBPM;
  int cadence;
  double speed;
  int watts;

};


using TCXTrack = std::list<TCXTrackPoint>;


struct TCXLap
{
  std::string startTime;
  double totalTimeSeconds;
  double distanceMeters;
  double maximumSpeed;
  int calories;
  int averageHeartRateBPM;
  int maximumHeartRateBPM;
  std::string intensity;
  int cadence;
  std::string triggerMethod;
  TCXTrack track;
  double averageSpeed;
  int maxBikeCadence;
  int steps;
  int averageWatts;
  int maxWatts;
  
  TCXLap(const xmlpp::Node*);
};

struct TCXActivity
{
  std::string sport;
  std::string id;
  std::list<TCXLap> laps;
  
  TCXActivity(const xmlpp::Node*);
};

struct TCXFile
{
  std::list<TCXActivity> activities;
  TCXFile(std::string fileName);
};






#endif