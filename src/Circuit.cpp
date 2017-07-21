#include <Circuit.h>
#include <string>
#include <fstream>
#include <stdexcept>






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


