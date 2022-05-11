#configuration file

REGEX := \"^\([^=]+\)=\(.+\)\"
CONFIG_FILE := \"./config.txt\"

#keys

NUM_OF_THREADS_KEY := \"num_of_threads\"
DLLS_DIR_KEY := \"dlls_dir\"
NBD_FILE_KEY := \"nbd_file\"
NBD_SIZE_KEY := \"nbd_size\"
ATTEMPTS_LIMIT_KEY := \"attempts_limit\"
RESCHEDULE_DELAY_KEY := \"reschedule_delay\"
MINION_KEY := \"minion\"

#current nbd file for utilss in the end of makefile

NBD_FILE=$(shell grep -Po "(?<=nbd_file=)(.*)" config.txt)

#compilation details

CC := g++
VERSION := -std=gnu++98
DEBUG_FLAGS := $(VERSION) -Weffc++ -pedantic-errors -Wall -Wextra -g

LIBS := _libs
DLLS := _dlls
BIN := _bin
STORAGES := _storages
MOUNT := _mount

PATH_TO_LIBS := -L$(realpath .)/$(LIBS) -Wl,-rpath=$(realpath .)/$(LIBS) 

#dispatcher (implemented completely in header file)

DISPATCHER_HDRS := -I dispatcher/include/

#waitable_queue (implemented completely in header file)

WAITABLE_QUEUE_HDRS := -I waitable_queue/include/

#priority_queue (implemented completely in header file)

PRIORITY_QUEUE_HDRS := -I priority_queue/include/

#factory (implemented completely in header file)

FACTORY_HDRS := -I factory/include/

#utils (implemented completely in header file)

UTILS_HDRS := -I utils/include/

#handleton (implemented completely in header file)

HANDLETON_HDRS := -I handleton/include/

#thread pool

THREAD_POOL := $(LIBS)/libthread_pool.so
THREAD_POOL_HDRS := -I thread_pool/include/
THREAD_POOL_SRCS := $(wildcard thread_pool/src/*.cpp)
THREAD_POOL_INCLUDE_HDRS := $(THREAD_POOL_HDRS) $(PRIORITY_QUEUE_HDRS) $(WAITABLE_QUEUE_HDRS)
THREAD_POOL_LIBS := -lboost_system -lboost_thread -lpthread

#dll loader

DLL_LOADER := $(LIBS)/libdll_loader.so
DLL_LOADER_HDRS := -I dll_loader/include/
DLL_LOADER_SRCS := $(wildcard dll_loader/src/*.cpp)
DLL_LOADER_INCLUDE_HDRS := $(DLL_LOADER_HDRS) $(DISPATCHER_HDRS) $(UTILS_HDRS)
DLL_LOADER_LIBS := -lboost_system -lboost_thread -lpthread -ldl

#reactor

REACTOR := $(LIBS)/libreactor.so
REACTOR_HDRS := -I reactor/include/
REACTOR_SRCS := $(wildcard reactor/src/*.cpp)
REACTOR_INCLUDE_HDRS := $(REACTOR_HDRS) $(UTILS_HDRS)
REACTOR_LIBS := -lboost_system

#runtime_config

RUNTIME_CONFIG := $(LIBS)/libruntime_config.so
RUNTIME_CONFIG_HDRS := -I runtime_config/include/
RUNTIME_CONFIG_SRCS := $(wildcard runtime_config/src/*.cpp)
RUNTIME_CONFIG_INCLUDE_HDRS := $(RUNTIME_CONFIG_HDRS) $(HANDLETON_HDRS) $(UTILS_HDRS)
RUNTIME_CONFIG_LIBS := -lboost_regex
RUNTIME_CONFIG_DEFINES := -DREGEX=$(REGEX) -DCONFIG_FILE=$(CONFIG_FILE)

#extensions_api

EXTENSIONS_API := $(LIBS)/libextensions_api.so
EXTENSIONS_API_HDRS := -I extensions_api/include/
EXTENSIONS_API_SRCS := $(wildcard extensions_api/src/*.cpp)
EXTENSIONS_API_INCLUDE_HDRS := $(EXTENSIONS_API_HDRS)
EXTENSIONS_API_LIBS := -lboost_system

#framework

FRAMEWORK := $(LIBS)/libframework.so
FRAMEWORK_HDRS := -I framework/include/
FRAMEWORK_SRCS := $(wildcard framework/src/*.cpp)
FRAMEWORK_INCLUDE_HDRS := $(FRAMEWORK_HDRS) $(DLL_LOADER_HDRS) $(DISPATCHER_HDRS) $(UTILS_HDRS) $(REACTOR_HDRS) $(THREAD_POOL_HDRS) $(PRIORITY_QUEUE_HDRS) $(WAITABLE_QUEUE_HDRS) $(FACTORY_HDRS) $(RUNTIME_CONFIG_HDRS) $(HANDLETON_HDRS) $(EXTENSIONS_API_HDRS)
FRAMEWORK_LIBS := -lboost_system -lboost_thread -lpthread -ldl -lboost_regex $(DLL_LOADER) $(REACTOR) $(THREAD_POOL) $(RUNTIME_CONFIG) $(EXTENSIONS_API)
FRAMEWORK_DEFINES := -DNUM_OF_THREADS=$(NUM_OF_THREADS_KEY) -DDLLS_DIR=$(DLLS_DIR_KEY)

#handleton explicit instantiation

HANDLETON_INSTANCES := $(LIBS)/libhandleton_instances.so
HANDLETON_INSTANCES_SRCS := $(wildcard handleton/src/*.cpp)
HANDLETON_INSTANCES_INCLUDE_HDRS := $(HANDLETON_HDRS) $(FRAMEWORK_HDRS) $(DLL_LOADER_HDRS) $(DISPATCHER_HDRS) $(UTILS_HDRS) $(REACTOR_HDRS) $(THREAD_POOL_HDRS) $(PRIORITY_QUEUE_HDRS) $(WAITABLE_QUEUE_HDRS) $(FACTORY_HDRS) $(RUNTIME_CONFIG_HDRS) $(EXTENSIONS_API_HDRS)
HANDLETON_INSTANCES_LIBS := -lboost_system -lboost_thread -lpthread -ldl -lboost_regex $(DLL_LOADER) $(REACTOR) $(THREAD_POOL) $(RUNTIME_CONFIG) $(FRAMEWORK) $(EXTENSIONS_API)

#test

TEST := $(BIN)/test.out
TEST_SRCS := test/test.cpp
TEST_INCLUDE_HDRS := $(FRAMEWORK_HDRS) $(DLL_LOADER_HDRS) $(DISPATCHER_HDRS) $(UTILS_HDRS) $(REACTOR_HDRS) $(THREAD_POOL_HDRS) $(PRIORITY_QUEUE_HDRS) $(WAITABLE_QUEUE_HDRS) $(FACTORY_HDRS) $(HANDLETON_HDRS) $(EXTENSIONS_API_HDRS)
TEST_LIBS := -lboost_regex -lboost_system -lboost_thread -lpthread -ldl $(DLL_LOADER) $(REACTOR) $(THREAD_POOL) $(FRAMEWORK) $(RUNTIME_CONFIG) $(HANDLETON_INSTANCES) $(EXTENSIONS_API)
TEST_DEFINES := -DTEST

#data_repository

DATA_REPOSITORY := $(DLLS)/libdata_repository.so
DATA_REPOSITORY_HDRS := -I data_repository/include/
DATA_REPOSITORY_SRCS := $(wildcard data_repository/src/*.cpp)
DATA_REPOSITORY_INCLUDE_HDRS := $(DATA_REPOSITORY_HDRS) $(RUNTIME_CONFIG_HDRS) $(UTILS_HDRS) $(HANDLETON_HDRS)
DATA_REPOSITORY_LIBS := -lboost_system $(RUNTIME_CONFIG)
DATA_REPOSITORY_DEFINES := -DMINION=$(MINION_KEY)

#scheduler

SCHEDULER := $(DLLS)/libscheduler.so
SCHEDULER_HDRS := -I scheduler/include/
SCHEDULER_SRCS := $(wildcard scheduler/src/*.cpp)
SCHEDULER_INCLUDE_HDRS := $(SCHEDULER_HDRS) $(HANDLETON_HDRS) $(UTILS_HDRS)
SCHEDULER_LIBS := -lboost_system -lboost_thread -lpthread

#requests_manager/kamikaze

REQUESTS_MANAGER := $(DLLS)/librequests_manager.so
REQUESTS_MANAGER_HDRS := -I requests_manager/include/
REQUESTS_MANAGER_SRCS := $(wildcard requests_manager/src/*.cpp)
REQUESTS_MANAGER_INCLUDE_HDRS := $(REQUESTS_MANAGER_HDRS) $(RUNTIME_CONFIG_HDRS) $(HANDLETON_HDRS) $(DATA_REPOSITORY_HDRS) $(UTILS_HDRS) $(SCHEDULER_HDRS) $(EXTENSIONS_API_HDRS) 
REQUESTS_MANAGER_LIBS := -lboost_system -lboost_thread -lpthread $(RUNTIME_CONFIG) $(SCHEDULER) $(DATA_REPOSITORY) $(EXTENSIONS_API)
REQUESTS_MANAGER_DEFINES := -DATTEMPTS_LIMIT=$(ATTEMPTS_LIMIT_KEY) -DRESCHEDULE_DELAY=$(RESCHEDULE_DELAY_KEY)

#commands

COMMANDS := $(DLLS)/libcommands.so
COMMANDS_HDRS := -I commands/include/
COMMANDS_SRCS := $(wildcard commands/src/*.cpp)
COMMANDS_INCLUDE_HDRS := $(COMMANDS_HDRS) $(FRAMEWORK_HDRS) $(DLL_LOADER_HDRS) $(DISPATCHER_HDRS) $(UTILS_HDRS) $(REACTOR_HDRS) $(THREAD_POOL_HDRS) $(PRIORITY_QUEUE_HDRS) $(WAITABLE_QUEUE_HDRS) $(FACTORY_HDRS) $(HANDLETON_HDRS) $(EXTENSIONS_API_HDRS) 
COMMANDS_LIBS := -lboost_system -lboost_thread -lpthread -ldl $(DLL_LOADER) $(REACTOR) $(THREAD_POOL) $(FRAMEWORK) $(HANDLETON) $(EXTENSIONS_API)

#nbd

NBD := $(DLLS)/libnbd.so
NBD_HDRS := -I nbd/include/
NBD_SRCS := $(wildcard nbd/src/*.cpp)
NBD_INCLUDE_HDRS := $(NBD_HDRS) $(FRAMEWORK_HDRS) $(DLL_LOADER_HDRS) $(DISPATCHER_HDRS) $(UTILS_HDRS) $(REACTOR_HDRS) $(THREAD_POOL_HDRS) $(PRIORITY_QUEUE_HDRS) $(WAITABLE_QUEUE_HDRS) $(FACTORY_HDRS) $(RUNTIME_CONFIG_HDRS) $(HANDLETON_HDRS) $(EXTENSIONS_API_HDRS)
NBD_LIBS := -lboost_system -lboost_thread -lpthread -ldl $(DLL_LOADER) $(REACTOR) $(THREAD_POOL) $(FRAMEWORK) $(RUNTIME_CONFIG) $(EXTENSIONS_API)
NBD_DEFINES := -DNBD_FILE=$(NBD_FILE_KEY) -DNBD_SIZE=$(NBD_SIZE_KEY)

test: $(TEST)

dlls: $(DATA_REPOSITORY) $(SCHEDULER) $(REQUESTS_MANAGER) $(COMMANDS) $(NBD)

#libs/framework

$(THREAD_POOL): $(THREAD_POOL_SRCS) $(THREAD_POOL_LIBS)
	$(CC) $(DEBUG_FLAGS) -shared -fPIC $^ -o $@ $(THREAD_POOL_INCLUDE_HDRS)

$(DLL_LOADER): $(DLL_LOADER_SRCS) $(DLL_LOADER_LIBS)
	$(CC) $(DEBUG_FLAGS) -shared -fPIC $^ -o $@ $(DLL_LOADER_INCLUDE_HDRS)

$(REACTOR): $(REACTOR_SRCS) $(REACTOR_LIBS)
	$(CC) $(DEBUG_FLAGS) -shared -fPIC $^ -o $@ $(REACTOR_INCLUDE_HDRS)

$(RUNTIME_CONFIG): $(RUNTIME_CONFIG_SRCS) $(RUNTIME_CONFIG_LIBS)
	$(CC) $(DEBUG_FLAGS) -shared -fPIC $^ -o $@ $(RUNTIME_CONFIG_INCLUDE_HDRS) $(RUNTIME_CONFIG_DEFINES)

$(EXTENSIONS_API): $(EXTENSIONS_API_SRCS) $(EXTENSIONS_API_LIBS)
	$(CC) $(DEBUG_FLAGS) -shared -fPIC $^ -o $@ $(EXTENSIONS_API_INCLUDE_HDRS)

$(FRAMEWORK): $(FRAMEWORK_SRCS) $(FRAMEWORK_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) -shared -fPIC $^ -o $@ $(FRAMEWORK_INCLUDE_HDRS) $(FRAMEWORK_DEFINES) 

#test

$(HANDLETON_INSTANCES): $(HANDLETON_INSTANCES_SRCS) $(HANDLETON_INSTANCES_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) -shared -fPIC $^ -o $@ $(HANDLETON_INSTANCES_INCLUDE_HDRS)

$(TEST): $(TEST_SRCS) $(TEST_LIBS) 
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) $^ -o $@ $(TEST_INCLUDE_HDRS) $(TEST_DEFINES)

#data_repository

$(DATA_REPOSITORY): $(DATA_REPOSITORY_SRCS) $(DATA_REPOSITORY_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) -shared -fPIC $^ -o $@ $(DATA_REPOSITORY_INCLUDE_HDRS) $(DATA_REPOSITORY_DEFINES)

#scheduler

$(SCHEDULER): $(SCHEDULER_SRCS) $(SCHEDULER_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) -shared -fPIC $^ -o $@ $(SCHEDULER_INCLUDE_HDRS)

#requests_manager

$(REQUESTS_MANAGER): $(REQUESTS_MANAGER_SRCS) $(REQUESTS_MANAGER_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) -shared -fPIC $^ -o $@ $(REQUESTS_MANAGER_INCLUDE_HDRS) $(REQUESTS_MANAGER_DEFINES)

#commands

$(COMMANDS): $(COMMANDS_SRCS) $(COMMANDS_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) -shared -fPIC $^ -o $@ $(COMMANDS_INCLUDE_HDRS)

#nbd

$(NBD): $(NBD_SRCS) $(NBD_LIBS)
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) -shared -fPIC $^ -o $@ $(NBD_INCLUDE_HDRS) $(NBD_DEFINES)

#utils

.PHONY: clean
clean:
	rm -f $(LIBS)/*.so 
	rm -f $(BIN)/*.out 
	rm -f $(DLLS)/*.so 
	rm -f $(STORAGES)/*/file*
	rm -f core

reset:
	rm -f $(DLLS)/*.so  
	rm -f $(STORAGES)/*/file*
	rm -f core

run:
	sudo $(BIN)/test.out

nbds:
	sudo modprobe nbd

kbs:
	echo "4" | sudo tee /sys/block/nbd*/queue/max_sectors_kb

ext2:
	sudo mkfs.ext2 $(NBD_FILE)

ext4:
	sudo mkfs.ext4 $(NBD_FILE)

mount:
	sudo mount $(NBD_FILE) ./$(MOUNT)/

##############################################################################
