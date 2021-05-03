#for compiling
CC=gcc

DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#general
NAME=$(shell basename $(CURDIR))

###################################################################
#compiling

all: debug release

debug:
	$(CC) $(DEBUG_FLAGS) src/$(NAME).c -o bin/$(NAME)_debug.out

release:
	$(CC) $(RELEASE_FLAGS) src/$(NAME).c -o bin/$(NAME)_release.out

.PHONY: clean
clean:
	ipcrm -a
	rm -f bin/* keys/*
