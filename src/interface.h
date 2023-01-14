#pragma once
#include <vector>
#include <string>


// This is the interface jsbsim and the rest of the world.
//


class terms_t
{
  public:
   std::string jsbsimName;
   std::string websocketName;
   terms_t(std::string a, std::string b);
};

typedef std::vector<terms_t> termsVec;

class jsbsimInterface_t
{
  public:
   termsVec inTerms;
   termsVec outTerms;
   void copyInToJSBSim (int i);
   void copyOutOfJSBSim (int i);
};
