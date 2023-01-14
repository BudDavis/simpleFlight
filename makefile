

CC=g++

JSBSIM_LIB+=/usr/local/lib
JSBSIM_INC+=/usr/local/include/JSBSim

CXXFLAGS+=-Wall -Wextra -std=c++14 -g -O0
CPPFLAGS+=-I${JSBSIM_INC} -I src/include
LDLIBS+=-L${JSBSIM_LIB} -lJSBSim

./src/simpleFlight: ./src/simpleFlight.o

clean:
	-rm -f ./src/simpleFlight ./src/simpleFlight.o


