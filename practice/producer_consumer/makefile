#for compiling
CC=gcc

DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

INCLUDE=-I include/ -I ~/git/ds/queue/include/ -I ~/git/ds/slist/include/ -I ~/git/ds/dlist/include/

SRC_TO_INCLUDE=src/* ~/git/ds/queue/src/* ~/git/ds/slist/src/* ~/git/ds/dlist/src/*

#general
NAME=$(shell basename $(CURDIR))

###################################################################
#compiling

all: debug release

debug:
	$(CC) $(DEBUG_FLAGS) $(SRC_TO_INCLUDE) $(INCLUDE) -o bin/$(NAME)_debug.out -lpthread

release:
	$(CC) $(RELEASE_FLAGS) $(SRC_TO_INCLUDE) $(INCLUDE) -o bin/$(NAME)_release.out -lpthread

.PHONY: clean
clean:
	ipcrm -a
	rm -f bin/*
