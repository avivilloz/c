#for compiling
CC=gcc

DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#general
NAME=$(shell basename $(CURDIR))

###################################################################
#compiling

all: debug release

prog: create_prog

debug:
	$(CC) $(DEBUG_FLAGS) src/$(NAME).c -o bin/$(NAME)_debug.out

release:
	$(CC) $(RELEASE_FLAGS) src/$(NAME).c -o bin/$(NAME)_release.out

create_prog:
	$(CC) $(DEBUG_FLAGS) src/prog_ex3.c -o bin/prog.out

.PHONY: clean
clean:
	rm -f bin/*
