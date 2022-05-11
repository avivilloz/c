MODULE_NAME := $(shell basename $(CURDIR))

CPPC := g++
VERSION := -std=gnu++98
FLAGS := -std=gnu++98 -Weffc++ -pedantic-errors -Wall -Wextra
DEBUG_FLAGS := -g
RELEASE_FLAGS := -DNDEBUG -O3

DEBUG_COMPILER := $(CPPC) $(VERSION) $(FLAGS) $(DEBUG_FLAGS)
RELEASE_COMPILER := $(CPPC) $(VERSION) $(FLAGS) $(RELEASE_FLAGS)

LIB_DIR := lib
OBJ_DIR := obj
SRC_DIR := src
HDR_DIR := include
BIN_DIR := bin
TEST_DIR := test

TEST := $(TEST_DIR)/test_$(MODULE_NAME).cpp
HDRS := -I include/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
LIB := $(LIB_DIR)/lib$(MODULE_NAME).so
DEBUG := $(BIN_DIR)/debug_$(MODULE_NAME).out
RELEASE := $(BIN_DIR)/release_$(MODULE_NAME).out

PATH_TO_LIBS := -L$(realpath .)/$(LIB_DIR) -Wl,-rpath=$(realpath .)/$(LIB_DIR) 

INCLUDE_LIBS := -lboost_system

all: $(DEBUG)

$(DEBUG): $(TEST) $(LIB) $(INCLUDE_LIBS)
	$(DEBUG_COMPILER) $(PATH_TO_LIBS) $^ $(HDRS) -o $@

$(LIB): $(OBJS)
	$(CPPC) $^ -shared -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(DEBUG_COMPILER) $(INCLUDE_LIBS) $^ $(HDRS) -c -fPIC -o $@

PHONY: clean
clean:
	rm $(OBJS)
	rm $(LIB)
	rm $(DEBUG)

run: $(DEBUG)
	./$^

vlg: $(DEBUG)
	valgrind --leak-check=yes --track-origins=yes $^
