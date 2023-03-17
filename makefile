

CC=g++

JSBSIM_LIB+=/usr/local/lib
JSBSIM_INC+=/usr/include/JSBSim

CXXFLAGS+=-Wall -Wextra -std=c++14 -g -O0
CPPFLAGS+=-I${JSBSIM_INC} \
          -I src/include \
          -I src/

LDLIBS+= -lboost_system -lpthread -lrt -L${JSBSIM_LIB} -lJSBSim

SIMPLEFLIGHT_OBJ=src/simpleFlight.o src/sim.o src/simConnection.o

./src/simpleFlight: ${SIMPLEFLIGHT_OBJ}

clean:
	-rm -f ./src/simpleFlight  ${SIMPLEFLIGHT_OBJ}


