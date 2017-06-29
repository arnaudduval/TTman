#ifndef __GPXFILE_H__
#define __GPXFILE_H__

#include <string>
#include <list>
#include <tuple>
#include <libxml++/libxml++.h>
#include <GPSPoint.h>

// A metadata is a string value associated to a key
using Metadata = std::tuple<std::string, std::string> ;



// Structure defining a GPX waypoint
struct GPXwpt
{
    std::string timestamp;
    double elevation;
    GPSPoint coords;
    
    GPXwpt(const xmlpp::Node*);
};


/*
// Structure defining a GPX route
struct GPXrte
{
    std::list< std::tuple<std::string, std::string> > metadata;
    std::list<GPXwpt> rtept;
}; */



using GPXtrkpt = GPXwpt;

struct GPXtrkseg
{
    std::list<GPXtrkpt> trkpts;
    
    GPXtrkseg(const xmlpp::Node*);
};


// Structure defining a GPX track
struct GPXtrk
{
    std::list<Metadata> metadata;
    std::string name;
    std::list<GPXtrkseg> trksegs;
    
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