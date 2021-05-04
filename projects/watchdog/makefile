CC=gcc
FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

###############################################################################

SRCS=~/git/ds/uid/src/uid.c ~/git/ds/task/src/task.c ~/git/ds/dlist/src/dlist.c ~/git/ds/sorted_list/src/sorted_list.c ~/git/ds/pq/src/pq.c ~/git/ds/scheduler/src/scheduler.c

HDRS=-I include/ -I ~/git/ds/uid/include/ -I ~/git/ds/task/include/ -I ~/git/ds/dlist/include/ -I ~/git/ds/sorted_list/include/ -I ~/git/ds/pq/include/ -I ~/git/ds/scheduler/include/

###############################################################################

WATCHDOG=bin/watchdog.out

CLIENT=bin/client.out

WATCHDOG_SRC=src/watchdog.c

CLIENT_SRC=src/live_and_let_die.c test/client.c

###############################################################################

SHARED_SRC=src/shared.c

SHARED_OBJ=obj/shared.o

SHARED_LIB=lib/libshared.so

PATH_TO_LIB=-L$(realpath .)/lib -Wl,-rpath=$(realpath .)/lib

###############################################################################

all: $(SHARED_LIB) $(WATCHDOG) $(CLIENT)

$(SHARED_LIB): $(SHARED_OBJ) 
	$(CC) $(FLAGS) $^ -o $@ -shared

$(SHARED_OBJ): $(SHARED_SRC)
	$(CC) $(FLAGS) $^ -c -o $@ $(HDRS) -fPIC

$(WATCHDOG): $(WATCHDOG_SRC) $(SHARED_LIB) $(SRCS)
	$(CC) $(FLAGS) $(PATH_TO_LIB) $^ -o $@ $(HDRS) -lpthread

$(CLIENT): $(CLIENT_SRC) $(SHARED_LIB) $(SRCS)
	$(CC) $(FLAGS) $(PATH_TO_LIB) $^ -o $@ $(HDRS) -lpthread

###############################################################################

.PHONY: clean
clean:
	rm -f obj/* lib/* bin/* /tmp/watchdog_sem
	ipcrm -a

.PHONY: kill
kill: 
	pkill watchdog.out
	pkill client.out
	
###############################################################################

run: $(CLIENT) $(WATCHDOG) 
	$^

