MAKE=mingw32-make
CC=gcc
CSTD=c99
SRC=src\sfa.c
EXT=.exe
CFLAGS=-Wall -Werror -pedantic -Wextra -O2 -std=${CSTD}

.PHONY: all build clean assembly clean_assembly

all: build run

build: ${SRC}
	${CC} ${CFLAGS} ${SRC} -o sfa${EXT}

run: build
	./sfa${EXT}

assembly: 
	${CC} -S -O0 -o ./sfa.s ${SRC}