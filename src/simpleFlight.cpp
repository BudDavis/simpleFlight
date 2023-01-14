

#include <stdio.h>
#include <string>

#include <FGFDMExec.h>

JSBSim::FGFDMExec fdmex;



int main(int argc, char* argv[])
{

/* the arguments must be:
 *                  websocket port
 *                  aircraft xml file
 *                  script xml file
 *                  reset xml file
 */
        std::string ac = "c310/c310ap";
        std::string scr = "";
        std::string reset = "raft/c310/ellington.xml";
        int result = fdmex.LoadModel( ac , false );
        //copy_to_JSBsim(); // copy control inputs to JSBSim
        //fdmex->RunIC(); // loop JSBSim once w/o integrating
        //copy_from_JSBsim(); // update the bus
#if 0
        fdmex->LoadScript( ScriptName ); // the script loads the aircraft and
        result = FDMExec->Run();
        while (result) 
        { // cyclic execution
           result = FDMExec->Run(); // execute JSBSim
        }
#endif
	printf("normal exit\n");
	return 0;
}
