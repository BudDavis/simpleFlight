#include "interface.h"

terms_t::terms_t(std::string a, std::string b)
{
    jsbsimName = a;
    websocketName = b;
}

void jsbsimInterface_t::copyInToJSBSim (int i)
{
}

void jsbsimInterface_t::copyOutOfJSBSim (int i)
{
}

termsVec in  = {terms_t("aaa","bbbb")};
termsVec out = {terms_t("aaa","bbb")};

