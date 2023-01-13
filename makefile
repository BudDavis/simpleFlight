

CFLAGS+=-Wall -Wextra -std=c17 -g -O0


./src/simpleFlight: ./src/simpleFlight.o

clean:
	-rm -f ./src/simpleFlight ./src/simpleFlight.o


