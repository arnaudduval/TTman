#include <Circuit.h>
#include <string>
#include <fstream>
#include <stdexcept>


Point::Point(const GPSPoint& c, const double& e)
{
  alt = e;
  coords = c;
}



Circuit::Circuit(const GPXFile& f)
{
  for(auto itrack = f.tracks.begin() ; itrack != f.tracks.end() ; ++itrack)
  {
    for(auto isegment = (*itrack).trksegs.begin() ; isegment != (*itrack).trksegs.end() ; ++isegment)
    {
      for(auto ipoint = (*isegment).trkpts.begin() ; ipoint != (*isegment).trkpts.end() ; ++ipoint)
      {
        push_back(Point((*ipoint).coords, (*ipoint).elevation));
      }
    }
  }
}





Circuit ReadCircuit(std::string const &fileName)
{
  std::ifstream ifs(fileName);
  if(ifs.good())
  {
    Circuit _circuit;
    double _lat, _lon, _alt;
    while (!ifs.eof())
    {
      ifs >> _lat >> _lon >> _alt;
      _circuit.push_back(Point{GPSPoint{_lat, _lon}, _alt});
    }
    return _circuit;
  }
  else 
  {
    throw std::runtime_error("failed to open file: " + fileName);
  }  
  
}


