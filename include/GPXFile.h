#ifndef __GPXFILE_H__
#define __GPXFILE_H__

#include <string>
#include <list>
#include <tuple>
#include <libxml++/libxml++.h>

// A metadata is a string value associated to a key
using Metadata = std::tuple<std::string, std::string> ;

struct GPXNodeWithMetadata
{
  std
}



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
*/
// Structure defining a GPX track
struct GPXtrk
{
    std::list<Metadata> metadata;
    std::string name;
    //std::list<GPXtrkseg> trkseg;
    
    GPXtrk(const xmlpp::Node*);
    void ReadNameXML(const xmlpp::Node*);
};


struct GPXFile
{
    GPXFile(std::string);
  
    std::list<Metadata> metadata;
    //std::list<GPXwpt> waypoints;
    //std::list<GPXrte> routes;
    std::list<GPXtrk> tracks;
    void ReadMetadataXMLNode(const xmlpp::Node*);
};




#endif