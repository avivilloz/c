###############################################################################
#add information if needed

ARGS :=

HDRS := -I include/

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

###############################################################################

$(DEBUG): $(TEST)
	$(CC) $(DEBUG_FLAGS) $^ -o $@ $(HDRS)

$(RELEASE): $(TEST)
	$(CC) $(RELEASE_FLAGS) $^ -o $@ $(HDRS) 

###############################################################################

.PHONY: clean
clean:
	rm -f obj/* lib/* bin/*

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

###############################################################################
