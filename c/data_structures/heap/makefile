#for compiling
CC=gcc

DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#add relative path for external libraries if needed
INCLUDES=-I include/ -I ../dvector/include/ -I ../uid/include/ -I ../task/include/
#add absolute path for external libraries if needed
SHARED_LIBRARIES=-L$(realpath .)/lib -Wl,-rpath=$(realpath .)/lib -L~git/ds/dvector/lib -Wl,-rpath=~git/ds/dvector/lib -L~/git/ds/uid/lib -Wl,-rpath=~/git/ds/uid/lib -L~/git/ds/task/lib -Wl,-rpath=~/git/ds/task/lib

SRC=$(wildcard src/*.c)
OBJ=$(addprefix obj/,$(notdir $(SRC:.c=.o)))
#add relative path for external libraries if needed
LIBS=lib/lib$(NAME).so ../dvector/lib/libdvector.so ../uid/lib/libuid.so ../task/lib/libtask.so

#for running
VLG_FLAGS=--leak-check=yes --track-origins=yes

#general
NAME=$(shell basename $(CURDIR))

###################################################################
#compiling

all: obj1 obj2 obj3 lib debug release

.PHONY: obj1
obj1: src/heap.c
	$(CC) $(DEBUG_FLAGS) -c -o obj/heap.o -fPIC $^ $(INCLUDES) 

.PHONY: obj2
obj2: src/pq_heap.c
	$(CC) $(DEBUG_FLAGS) -c -o obj/pq_heap.o -fPIC $^ $(INCLUDES)

.PHONY: obj3
obj3: src/scheduler_heap.c
	$(CC) $(DEBUG_FLAGS) -c -o obj/scheduler_heap.o -fPIC $^ $(INCLUDES)

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
