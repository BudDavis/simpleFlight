

CFLAGS+=-Wall -Wextra -std=c17 -g -O0


convert: convert.o

clean:
	-rm -f convert.o convert
