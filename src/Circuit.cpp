#include <list>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>

#include <GPSPoint.h>




struct Point
{
  GPSPoint coords;
  double alt;
};

using Circuit = std::list<Point>;

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


int main()
{
  Circuit myCircuit = ReadCircuit("data/circuit.txt");
  GPSPoint Paris{48.853, 2.35};
  GPSPoint Lyon{45.764043,4.835659};
  std::cout << "Distance Paris-Lyon : " << Distance(Paris, Lyon) << "\n";
  std::cout << "Cap Paris-Lyon : " << Azimuth(Paris, Lyon) << "\n";

  return 0;
}