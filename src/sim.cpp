#include <math.h>

#include <string>

#include "json.hpp"
#include <JSBSim/FGJSBBase.h>

#include "sim.hpp"

const double RADTODEG = 180.0/M_PI;


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
   nlohmann::json pos = { 
                          {"longitude",fdmex.GetPropagate()->GetLocation().GetLongitudeDeg() },
                          {"latitude",fdmex.GetPropagate()->GetLocation().GetLatitudeDeg() },
                          {"psi",fdmex.GetPropagate()->GetEuler(JSBSim::FGJSBBase::ePsi)*RADTODEG }, 
                          {"phi",fdmex.GetPropagate()->GetEuler(JSBSim::FGJSBBase::ePhi)*RADTODEG }, 
                          {"tht",fdmex.GetPropagate()->GetEuler(JSBSim::FGJSBBase::eTht)*RADTODEG } 
                       };
   std::cout << pos.dump() << std::endl;
   return pos.dump();
//termsVec in  = {terms_t("aaa","bbbb", []{return fdmex.GetPropagate()->GetLocation().GetLongitudeDeg(); } ) };
//termsVec in  = {terms_t("aaa","bbbb", []{return fdmex.GetPropagate()->GetLocation().GetLongitudeDeg() } ) };
//termsVec out = {terms_t("aaa","bbb")};
//fdmex.GetPropagate()->GetLocation().GetLongitudeDeg()
#if 0
    SG_LOG( SG_FLIGHT, SG_INFO, "  Bank Angle: "
            << Propagate->GetEuler(FGJSBBase::ePhi)*RADTODEG << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  Pitch Angle: "
            << Propagate->GetEuler(FGJSBBase::eTht)*RADTODEG << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  True Heading: "
            << Propagate->GetEuler(FGJSBBase::ePsi)*RADTODEG << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  Latitude: "
            << Propagate->GetLocation().GetLatitudeDeg() << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  Longitude: "
            << Propagate->GetLocation().GetLongitudeDeg() << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  Altitude: "
            << Propagate->GetAltitudeASL() << " feet" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  loaded initial conditions" );

#endif
   return "";
}


