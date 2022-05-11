#for compiling
CC=gcc

DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#add relative path for external libraries if needed
INCLUDES=-I include/ -I ../slist/include/
#add absolute path for external libraries if needed
SHARED_LIBRARIES=-L$(realpath .)/lib -Wl,-rpath=$(realpath .)/lib -L~/git/ds/slist/lib -Wl,-rpath=~/git/ds/slist/lib

SRC=$(wildcard src/*.c)
OBJ=$(addprefix obj/,$(notdir $(SRC:.c=.o)))
LIBS=lib/lib$(NAME).so ../slist/lib/libslist.so

#for running
VLG_FLAGS=--leak-check=yes --track-origins=yes

#general
NAME=$(shell basename $(CURDIR))

###################################################################
#compiling

all: obj lib debug release

.PHONY: obj
obj: $(SRC)
	$(CC) $(DEBUG_FLAGS) -c -o $(OBJ) -fPIC $^ $(INCLUDES)

.PHONY: lib
lib: $(OBJ)
	$(CC) $(DEBUG_FLAGS) -o lib/lib$(NAME).so -shared $^ $(INCLUDES)

debug: test/test_$(NAME).c $(LIBS)
	$(CC) $(DEBUG_FLAGS) $(SHARED_LIBRARIES) -o bin/$(NAME)_debug.out $^ $(INCLUDES)

release: test/test_$(NAME).c $(LIBS)
	$(CC) $(RELEASE_FLAGS) $(SHARED_LIBRARIES) -o bin/$(NAME)_release.out $^ $(INCLUDES)

.PHONY: clean
clean:
	rm -f obj/* lib/* bin/*

####################################################################
#running/debugging

vlg: bin/$(NAME)_debug.out
	valgrind $(VLG_FLAGS) $^

run: bin/$(NAME)_release.out
	./$^
