#for compiling
CC=gcc

DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#add relative path for external libraries if needed
INCLUDES=-I include/
#add absolute path for external libraries if needed
SHARED_LIBRARIES=-L$(realpath .)/lib -Wl,-rpath=$(realpath .)/lib

SRC=$(wildcard src/*.c)
OBJ=$(addprefix obj/,$(notdir $(SRC:.c=.o)))
#add relative path for external libraries if needed
LIBS=lib/lib$(NAME).so

#general
NAME=$(shell basename $(CURDIR))

###################################################################
#compiling

all: obj1 lib debug release

.PHONY: obj1
obj1: src/$(NAME).c
	$(CC) $(DEBUG_FLAGS) -c -o obj/$(NAME).o -fPIC $^ $(INCLUDES)

.PHONY: lib
lib: $(OBJ)
	$(CC) $(DEBUG_FLAGS) -o lib/lib$(NAME).so -shared $^ $(INCLUDES)

debug: test/test_$(NAME).c $(LIBS)
	$(CC) $(DEBUG_FLAGS) $(SHARED_LIBRARIES) -o bin/$(NAME)_debug.out $^ $(INCLUDES) -lpthread

release: test/test_$(NAME).c $(LIBS)
	$(CC) $(RELEASE_FLAGS) $(SHARED_LIBRARIES) -o bin/$(NAME)_release.out $^ $(INCLUDES) -lpthread

.PHONY: clean
clean:
	rm -f obj/* lib/* bin/*
