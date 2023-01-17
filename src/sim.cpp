#include <math.h>

#include <string>

#include "json.hpp"

#include <boost/utility/enable_if.hpp>
#include <JSBSim/FGJSBBase.h>
#include <JSBSim/models/FGFCS.h>
#include <JSBSim/models/FGPropulsion.h>

#include "sim.hpp"

const double RADTODEG = 180.0/M_PI;


sim::sim()
{
   //std::string scr = "scripts/T37";
   //std::string scr = "scripts/c3105";
   //std::string scr = "./scripts/c1722";
   std::string scr = "scripts/737_cruise";
   //std::string scr = "scripts/737_cruise_steady_turn";
   //std::string scr = "scripts/c172_cruise_8K";
   //int result = FDMExec->LoadScript(ac, override_sim_rate_value, ResetName);
   fdmex.LoadScript(SGPath::fromLocal8Bit(scr.c_str()));
   fdmex.RunIC(); // loop JSBSim once w/o integrating
   //fdmex.Hold();
   std::cout << "the ic object is " << fdmex.GetIC() << std::endl;
}

sim::~sim()
{
}
int delay=0;
void sim::tick()
{
    delay++;
    if (delay<330)
      return;
    fdmex.Run();
}

void sim::importData(std::string S)
{
    // incoming S is a json formatted string
    try
    {
       nlohmann::json j = nlohmann::json::parse ( S );
       fdmex.GetFCS()->SetDaCmd(  j["aileron"] );
       fdmex.GetFCS()->SetDeCmd(  j["elevator"] );
       fdmex.GetFCS()->SetDsCmd(  j["rudder"] );
       fdmex.GetFCS()->SetDrCmd( -1.0 * j["rudder"].get<double>() );
       for (size_t i = 0; i < fdmex.GetPropulsion()->GetNumEngines(); i++) 
       {
          fdmex.GetFCS()->SetThrottleCmd(i, j["throttle"] );
       }

#if 0
  FCS->SetDaCmd( globals->get_controls()->get_aileron());
    FCS->SetRollTrimCmd( globals->get_controls()->get_aileron_trim() );
    FCS->SetDeCmd( globals->get_controls()->get_elevator());
    FCS->SetPitchTrimCmd( globals->get_controls()->get_elevator_trim() );
    FCS->SetDrCmd( -globals->get_controls()->get_rudder() );
    FCS->SetDsCmd( globals->get_controls()->get_rudder() );
    FCS->SetYawTrimCmd( -globals->get_controls()->get_rudder_trim() );
    FCS->SetDfCmd( globals->get_controls()->get_flaps() );
    FCS->SetDsbCmd( globals->get_controls()->get_speedbrake() );
    FCS->SetDspCmd( globals->get_controls()->get_spoilers() );

    FCS->SetRollTrimCmd( globals->get_controls()->get_aileron_trim() );
    FCS->SetDeCmd( globals->get_controls()->get_elevator());
    FCS->SetPitchTrimCmd( globals->get_controls()->get_elevator_trim() );
    FCS->SetDrCmd( -globals->get_controls()->get_rudder() );
    FCS->SetDsCmd( globals->get_controls()->get_rudder() );
    FCS->SetYawTrimCmd( -globals->get_controls()->get_rudder_trim() );
    FCS->SetDfCmd( globals->get_controls()->get_flaps() );
    FCS->SetDsbCmd( globals->get_controls()->get_speedbrake() );
    FCS->SetDspCmd( globals->get_controls()->get_spoilers() );
#endif
    }
    catch (int e)
    {
      cout << "An exception occurred. Exception Nr. " << e << '\n';
    }
}

std::string sim::exportData()
{
   nlohmann::json pos = { 
                          {"longitude",fdmex.GetPropagate()->GetLocation().GetLongitude()*RADTODEG },
                          {"latitude",fdmex.GetPropagate()->GetLocation().GetGeodLatitudeRad()*RADTODEG },
                          {"altitude",fdmex.GetPropagate()->GetAltitudeASL() },
                          {"psi",fdmex.GetPropagate()->GetEuler(JSBSim::FGJSBBase::ePsi)*RADTODEG }, 
                          {"phi",fdmex.GetPropagate()->GetEuler(JSBSim::FGJSBBase::ePhi)*RADTODEG }, 
                          {"tht",fdmex.GetPropagate()->GetEuler(JSBSim::FGJSBBase::eTht)*RADTODEG } 
                       };
   std::cout << "ASL = " << fdmex.GetPropagate()->GetAltitudeASL() << std::endl;
   return pos.dump();
}


