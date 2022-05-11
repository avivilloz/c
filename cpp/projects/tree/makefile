###############################################################################
#add information if needed

ARGS := /home/avivilloz/projects

HDRS := -I include/
SHARED_LIBS := -lboost_filesystem -lboost_system
PATH_TO_LIBS := -L$(realpath .)/lib -Wl,-rpath=$(realpath .)/lib

###############################################################################

NAME := $(shell basename $(CURDIR))

###############################################################################

CC := g++
DEBUG_FLAGS := -std=gnu++98 -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS := -std=gnu++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3

VLG := valgrind
VLG_FLAGS := --leak-check=yes --track-origins=yes
HLG_FLAGS := --tool=helgrind

GDB := gdb

###############################################################################

DEBUG := bin/$(NAME)_debug.out
RELEASE := bin/$(NAME)_release.out

###############################################################################

TEST := test/test_$(NAME).cpp
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, obj/%.o, $(SRCS))
LOCAL_LIB := lib/lib$(NAME).so

###############################################################################

all: $(DEBUG) $(RELEASE)

###############################################################################

$(DEBUG): $(TEST) $(LOCAL_LIB) $(SHARED_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) $^ -o $@ $(HDRS)

$(RELEASE): $(TEST) $(LOCAL_LIB) $(SHARED_LIBS)
	$(CC) $(RELEASE_FLAGS) $(PATH_TO_LIBS) $^ -o $@ $(HDRS)

###############################################################################

$(LOCAL_LIB): $(OBJS)
	$(CC) $(DEBUG_FLAGS) $^ -o $@ -shared

obj/%.o: src/%.cpp
	$(CC) $(DEBUG_FLAGS) $^ -c -o $@ $(HDRS) -fPIC

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
