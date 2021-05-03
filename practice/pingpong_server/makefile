###############################################################################
#add information if needed

HDRS := -I include/
SHARED_LIBS :=
PATH_TO_LIBS := -L$(realpath .)/lib -Wl,-rpath=$(realpath .)/lib 

###############################################################################

CC := gcc
DEBUG_FLAGS := -ansi -pedantic-errors -Wall -Wextra -g
EXTRA_FLAGS := -D_POSIX_C_SOURCE=200112L

###############################################################################

SERVER := bin/server.out
CLIENT := bin/client.out
LOCAL_LIB := lib/libshared.so
SERVER_SRC := test/server.c
CLIENT_SRC := test/client.c src/broadcast.c

###############################################################################

all: $(SERVER) $(CLIENT)

###############################################################################

$(SERVER): $(SERVER_SRC) $(LOCAL_LIB) $(SHARED_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) $^ -o $@ $(HDRS) $(EXTRA_FLAGS)

$(CLIENT): $(CLIENT_SRC) $(LOCAL_LIB) $(SHARED_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) $^ -o $@ $(HDRS) $(EXTRA_FLAGS)

$(LOCAL_LIB): obj/shared.o
	$(CC) $(DEBUG_FLAGS) $^ -o $@ -shared

obj/shared.o: src/shared.c
	$(CC) $(DEBUG_FLAGS) $^ -c -o $@ $(HDRS) -fPIC $(EXTRA_FLAGS)

###############################################################################

.PHONY: clean
clean:
	rm -f obj/*.o lib/*.so bin/*.out
	killall -9 server.out

###############################################################################
