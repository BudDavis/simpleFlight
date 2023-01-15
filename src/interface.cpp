#include "interface.h"

terms_t::terms_t(std::string a, std::string b, std::function<double()> c)
{
    jsbsimName = a;
    websocketName = b;
    f = c;
}

void jsbsimInterface_t::copyInToJSBSim (int i)
{
}

void jsbsimInterface_t::copyOutOfJSBSim (int i)
{
}

jsbsimInterface_t::jsbsimInterface_t(JSBSim::FGFDMExec f)
{
     fdmex = f;
}

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

 <latitude unit="DEG">   47.0 </latitude>
  <longitude unit="DEG"> 122.0 </longitude>
  <phi>         0.0 </phi>
  <theta>       0.0 </theta>
  <psi unit="DEG">       150.0 </psi>
  <altitude>    2000.00 </altitude>


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
#endif
