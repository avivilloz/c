#for compiling
CC=gcc

DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g -pthread
RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -pthread

#general
NAME=$(shell basename $(CURDIR))

###################################################################
#compiling

all: debug release

debug:
	$(CC) $(DEBUG_FLAGS) src/$(NAME).c -o bin/$(NAME)_debug.out -fopenmp

release:
	$(CC) $(RELEASE_FLAGS) src/$(NAME).c -o bin/$(NAME)_release.out -fopenmp

.PHONY: clean
clean:
	rm -f bin/*
