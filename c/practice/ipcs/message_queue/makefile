###############################################################################

CC := gcc
DEBUG_FLAGS := -ansi -pedantic-errors -Wall -Wextra -g

VLG := valgrind
VLG_FLAGS := --leak-check=yes --track-origins=yes
HLG_FLAGS := --tool=helgrind

GDB := gdb

###############################################################################

P1 := p1.out
P2 := p2.out

###############################################################################

all: $(P1) $(P2)

$(P1): p1.c
	$(CC) $(DEBUG_FLAGS) $^ -o $@

$(P2): p2.c
	$(CC) $(DEBUG_FLAGS) $^ -o $@ 

.PHONY: clean
clean:
	rm -f *.out

###############################################################################

open:
	vim -p makefile p1.c p2.c

pp:
	./$(P1)
	./$(P2)
	./$(P2)
	./$(P2)

p1: $(P1)
	./$^

p2: $(P2)
	./$^
