#!/bin/bash
include makefile.config

.PHONY: all pkg help clean

SRC = $(wildcard src/*.c) \
      $(wildcard src/db/sqlite/*.c) \
      $(wildcard src/photostore/*.c) 
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -O2 -Os -I -ldl -lreadline -lncurses
LDFLAGS = -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION
CFLAGS = -I ../include
RELEASE= release/

$(shell mkdir -p $(RELEASE))

all:

	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(RELEASE)$(NAME).o 

clean:

	-rm -rf $(RELEASE)*.o

