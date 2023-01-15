#pragma once
#include <vector>
#include <string>
#include <functional>

// This is the interface jsbsim and the rest of the world.
//

#include <FGFDMExec.h>


class terms_t
{
  public:
   std::string jsbsimName;
   std::string websocketName;
   std::function<double()> f;
   terms_t(std::string, std::string ,std::function<double()> );
};

typedef std::vector<terms_t> termsVec;

class jsbsimInterface_t
{
   JSBSim::FGFDMExec fdmex;

  public:
   termsVec inTerms;
   termsVec outTerms;
   void copyInToJSBSim (int);
   void copyOutOfJSBSim (int);
   jsbsimInterface_t(JSBSim::FGFDMExec );
};
