###############################################################################

ARGS := 

###############################################################################

NAME := $(shell basename $(CURDIR))

###############################################################################

CC := gcc
CCPP := g++
C_FLAGS := -ansi -pedantic-errors -Wall -Wextra -g
CPP_FLAGS := -std=gnu++98 -Weffc++ -pedantic-errors -Wall -Wextra -DNDEBUG -O3

VLG := valgrind
VLG_FLAGS := --leak-check=yes --track-origins=yes
HLG_FLAGS := --tool=helgrind

GDB := gdb

###############################################################################

C := bin/c.out
CPP := bin/cpp.out

###############################################################################

SRCS := $(wildcard src/*.c)

###############################################################################

all: $(C) $(CPP)

$(C): $(SRCS)
	$(CC) $(C_FLAGS) $^ -o $@ -I include/

$(CPP): cpp/*
	$(CCPP) $(CPP_FLAGS) $^ -o $@ -DSECOND_STAGE

.PHONY: clean
clean:
	rm -f bin/*

###############################################################################

runc: $(C)
	$^ $(ARGS)

runcpp: $(CPP)
	$^ $(ARGS)
