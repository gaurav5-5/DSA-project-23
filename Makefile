CC=gcc
CSTD=c99
INC_DIR=include/
BIN_DIR=bin/mk
SRC=src/sfa.c
EXT=.exe
CFLAGS=-Wall -Werr -pedantic -Wextra -O2 -I$(INC_DIR) -std=$(CSTD)

all: sfa

sfa:
  $(CC) $(CFLAGS) $^ -o $(BIN_DIR)/sfa$(EXT) 
  mkdir $(BIN_DIR)/res
  cp res/ui.txt res/words.txt $(BIN_DIR)/res

clean:
  rm -rf $(BIN_DIR)
