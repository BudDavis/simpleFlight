#include <string>

#include "json.hpp"
#include "sim.hpp"


sim::sim()
{
   std::string ac = "c172r";
   std::string scr = "";
   std::string reset = "reset00";
   if (fdmex.LoadModel( ac , true ) )
   {
      fdmex.RunIC(); // loop JSBSim once w/o integrating
      std::cout << "the ic object is " << fdmex.GetIC() << std::endl;
   }
}

sim::~sim()
{
}

void sim::tick()
{
    fdmex.Run();
}

void sim::importData(std::string S)
{
}

std::string sim::exportData()
{
   return "";
}



