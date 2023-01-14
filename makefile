

CC=g++


JSBSIM_INC=/usr/local/include/JSBSim

CXXFLAGS+=-Wall -Wextra -std=c++14 -g -O0
CPPFLAGS+=-I${JSBSIM_INC}

./src/simpleFlight: ./src/simpleFlight.o

clean:
	-rm -f ./src/simpleFlight ./src/simpleFlight.o


