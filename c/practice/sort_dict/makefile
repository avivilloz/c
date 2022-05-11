CC=gcc
DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g
SPECIAL_FLAGS=-lpthread #-pg

NAME=$(shell basename $(CURDIR))

DEBUG=bin/$(NAME).out

SRC=src/$(NAME).c

TIME=time

###################################################################

all: $(DEBUG)

$(DEBUG): $(SRC)
	$(CC) $(DEBUG_FLAGS) $^ -o $@ $(SPECIAL_FLAGS) 

.PHONY: clean
clean:
	rm -f bin/* gmon.out

run: $(DEBUG)
	$^ /usr/share/dict/words 500 0

runprof: $(DEBUG)
	gprof $^ gmon.out


#time bin/sort_dict.out /usr/share/dict/words 500 0
#hlg bin/sort_dict.out /usr/share/dict/words 500 0
#vlg bin/sort_dict.out /usr/share/dict/words 500 0
