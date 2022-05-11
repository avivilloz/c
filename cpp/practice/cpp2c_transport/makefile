###############################################################################

ARGS := 

###############################################################################

NAME := $(shell basename $(CURDIR))

###############################################################################

CC := gcc
DEBUG_FLAGS := -ansi -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS := -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

VLG := valgrind
VLG_FLAGS := --leak-check=yes --track-origins=yes
HLG_FLAGS := --tool=helgrind

GDB := gdb

###############################################################################

DEBUG := bin/$(NAME)_debug.out
RELEASE := bin/$(NAME)_release.out

###############################################################################

SRCS := $(wildcard src/*.c)

###############################################################################

all: $(DEBUG) $(RELEASE)

$(DEBUG): $(SRCS)
	$(CC) $(DEBUG_FLAGS) $^ -o $@

$(RELEASE): $(SRCS)
	$(CC) $(RELEASE_FLAGS) $^ -o $@ 

.PHONY: clean
clean:
	rm -f bin/*

###############################################################################

rund: $(DEBUG)
	$^ $(ARGS)

runr: $(RELEASE)
	$^ $(ARGS)

runvlg: $(DEBUG)
	$(VLG) $(VLG_FLAGS) $^ $(ARGS)

runhlg: $(DEBUG)
	$(VLG) $(HLG_FLAGS) $^ $(ARGS)

rungdb: $(DEBUG)
	$(GDB) $^ $(ARGS)
