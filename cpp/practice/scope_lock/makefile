###############################################################################

ARGS := 

###############################################################################

NAME := $(shell basename $(CURDIR))

###############################################################################

CC := g++
DEBUG_FLAGS := -std=gnu++98 -Weffc++ -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS := -std=gnu++98 -Weffc++ -pedantic-errors -Wall -Wextra -DNDEBUG -O3

VLG := valgrind
VLG_FLAGS := --leak-check=yes --track-origins=yes
HLG_FLAGS := --tool=helgrind

GDB := gdb

###############################################################################

DEBUG := bin/$(NAME)_debug.out
RELEASE := bin/$(NAME)_release.out

###############################################################################

TEST := test/test_$(NAME).cpp

###############################################################################

all: $(DEBUG) $(RELEASE)

$(DEBUG): $(TEST)
	$(CC) $(DEBUG_FLAGS) $^ -o $@ -I include/ -lpthread -lboost_system

$(RELEASE): $(TEST)
	$(CC) $(RELEASE_FLAGS) $^ -o $@ -I include/ -lpthread -lboost_system

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
