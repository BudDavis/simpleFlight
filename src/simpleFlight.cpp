

#include <stdio.h>

#include <FGFDMExec.h>




int main()
{
        int result;
        //FGFDMExec fdmex = new FGFDMExec(); // (1) Instantiation
        //result = fdmex->LoadModel( ... ); // (2) Model loading
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
	printf("hello\n");
	return 0;
}
