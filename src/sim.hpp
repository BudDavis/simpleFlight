#pragma once

// This is the interface between the websocket server
// and the JSBSim system.
//
//

#include <boost/utility/enable_if.hpp>
#include <FGFDMExec.h>

//include "json.hpp"



class sim
{
   JSBSim::FGFDMExec fdmex;
 public:
   void tick();
   void importData(std::string);
   std::string exportData();
   sim();
   ~sim();
};



