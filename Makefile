CC=gcc
CSTD=c99
SRC=src\sfa.c
EXT=.exe
BIN_DIR=bin
CFLAGS=-Wall -Werror -pedantic -Wextra -O2 -std=${CSTD}

.PHONY: all build clean assembly clean_assembly

all: build run

build: ${SRC}
	@echo "Building File"
	@if not exist "${BIN_DIR}" mkdir ${BIN_DIR}
	${CC} ${CFLAGS} ${BFLAGS} ${SRC} -o ${BIN_DIR}/sfa${EXT}
	@robocopy res ${BIN_DIR}/res /s /e  /ns /nc /nfl /ndl /np /njh /njs

run: build
	${BIN_DIR}/sfa${EXT}

assembly: 
	@if not exist "${BIN_DIR}" mkdir ${BIN_DIR}
	@if not exist "${BIN_DIR}/asm" mkdir ${BIN_DIR}/asm
	@${CC} -S -O0 -o ${BIN_DIR}/asm/sfa.s ${SRC}

clean_assembly:
	rm $(BIN_DIR)/asm/sfa.s
