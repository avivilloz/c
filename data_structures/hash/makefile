#for compiling
CC=gcc

DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#add relative path for external libraries if needed
INCLUDES=-I include/ -I ../dlist/include/
#add absolute path for external libraries if needed
SHARED_LIBRARIES=-L$(realpath .)/lib -Wl,-rpath=$(realpath .)/lib -L~git/ds/dlist/lib -Wl,-rpath=~git/ds/dlist/lib

SRC=$(wildcard src/*.c)
OBJ=$(addprefix obj/,$(notdir $(SRC:.c=.o)))
#add relative path for external libraries if needed
LIBS=lib/lib$(NAME).so ../dlist/lib/libdlist.so

#for running
VLG_FLAGS=--leak-check=yes --track-origins=yes

#general
NAME=$(shell basename $(CURDIR))

###################################################################
#compiling

all: obj lib debug release

sc: obj lib spell_checker_debug spell_checker_release

.PHONY: obj
obj: $(SRC)
	$(CC) $(DEBUG_FLAGS) -c -o $(OBJ) -fPIC $^ $(INCLUDES)

.PHONY: lib
lib: $(OBJ)
	$(CC) $(DEBUG_FLAGS) -o lib/lib$(NAME).so -shared $^ $(INCLUDES) -lm

debug: test/test_$(NAME).c $(LIBS)
	$(CC) $(DEBUG_FLAGS) $(SHARED_LIBRARIES) -o bin/$(NAME)_debug.out $^ $(INCLUDES)

release: test/test_$(NAME).c $(LIBS)
	$(CC) $(RELEASE_FLAGS) $(SHARED_LIBRARIES) -o bin/$(NAME)_release.out $^ $(INCLUDES)

spell_checker_debug: test/spell_checker.c $(LIBS) 
	$(CC) $(DEBUG_FLAGS) $(SHARED_LIBRARIES) -o bin/sc_debug.out $^ $(INCLUDES)

spell_checker_release: test/spell_checker.c $(LIBS)
	$(CC) $(RELEASE_FLAGS) $(SHARED_LIBRARIES) -o bin/sc_release.out $^ $(INCLUDES)

.PHONY: clean
clean:
	rm -f obj/* lib/* bin/*

####################################################################
#running/debugging

vlg: bin/$(NAME)_debug.out
	valgrind $(VLG_FLAGS) $^

run: bin/$(NAME)_release.out
	$^
