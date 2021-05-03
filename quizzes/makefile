#for compiling
CC=g++

DEBUG_FLAGS=-std=gnu++98 -pedantic-errors -Wall -Wextra -g
RELEASE_FLAGS=-std=gnu++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3

###################################################################
#compiling

all: debug release

debug:
	$(CC) $(DEBUG_FLAGS) quiz_pointers.cpp -o test_debug.out

release:
	$(CC) $(RELEASE_FLAGS) quiz_pointers.cpp -o test_release.out

.PHONY: clean
clean:
	rm -f test*

