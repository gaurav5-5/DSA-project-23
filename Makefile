CC=gcc
CSTD=c99
SRC=src/main.c src/trie.c src/ui.c
PROJ_NAME=spellcheck
EXT=.exe
BIN_DIR=bin
CFLAGS=-Wall -Werror -pedantic -Wextra -O2 -std=${CSTD}
INC_DIR=include

.PHONY: all build clean assembly clean_assembly

all: build run

build: ${SRC}
	@echo "Building File"
	@if not exist "${BIN_DIR}" mkdir ${BIN_DIR}
	${CC} ${CFLAGS} -I${INC_DIR} ${SRC} -o ${BIN_DIR}/${PROJ_NAME}${EXT}
	@robocopy res ${BIN_DIR}/res /s /e  /ns /nc /nfl /ndl /np /njh /njs

run: build
	${BIN_DIR}/${PROJ_NAME}${EXT}

assembly: 
	@if not exist "${BIN_DIR}" mkdir ${BIN_DIR}
	@if not exist "${BIN_DIR}/asm" mkdir ${BIN_DIR}/asm
	@${CC} -S -O0 -I${INC_DIR} -o ${BIN_DIR}/asm/${PROJ_NAME}.s ${SRC}

clean_assembly:
	rm $(BIN_DIR)/asm/${PROJ_NAME}.s

clean:
	rm -rf ${BIN_DIR}