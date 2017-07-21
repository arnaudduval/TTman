#include <string>
#include <GPXFile.h>
#include <Circuit.h>

int main(int argc, char *argv[])
{
  /*Circuit myCircuit = ReadCircuit("data/circuit.txt");
  GPSPoint Paris{48.853, 2.35};
  GPSPoint Lyon{45.764043,4.835659};
  std::cout << "Distance Paris-Lyon : " << Distance(Paris, Lyon) << "\n";
  std::cout << "Cap Paris-Lyon : " << Azimuth(Paris, Lyon) << "\n";*/
  
  // parse arguments
  if(argc > 1)
  {
    if (std::string(argv[1]) == "--readgpx")
    {
      if(argc >= 3)
      {
        std::string filePath(argv[2]);
        GPXFile gpx(filePath);
        gpx.MakeLog("ReadGPX.log");
        
        Circuit c(gpx);
      }
    }
  }
    
  

  return 0;
}