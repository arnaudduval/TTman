#ifndef __GPXFILE_H__
#define __GPXFILE_H__

#include <string>
#include <list>
#include <tuple>

// A metadata is a string value associated to a key
using Metadata = std::tuple<std::string, std::string> ;

/*
// Structure defining a GPX waypoint
struct GPXwpt
{
    std::list< std::tuple<std::string, std::string> > metadata;
};

// Structure defining a GPX route
struct GPXrte
{
    std::list< std::tuple<std::string, std::string> > metadata;
    std::list<GPXwpt> rtept;
};

struct GPXtrkseg
{
    std::list<GPXwpt> trkpt;
};

// Structure defining a GPX track
struct GPXtrk
{
    std::list< std::tuple<std::string, std::string> > metadata;
    std::list<GPXtrkseg> trkseg;
};
*/

struct GPXFile
{
    GPXFile(std::string);
  
    std::list<Metadata> metadata;
    //std::list<GPXwpt> waypoints;
    //std::list<GPXrte> routes;
    //std::list<GPXtrk> tracks;
};




#endif