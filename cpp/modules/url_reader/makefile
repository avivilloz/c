ARGS := sample_urls.txt _urls_data/ 20

#configuration file

REGEX := \"^\([^=]+\)=\(.+\)\"
CONFIG_FILE := \"./config.txt\"

#keys

CURL_POLL_TIMEOUT := \"curl_poll_timeout\"
PATH_TO_URLS_STORAGE_FILE := \"path_to_urls_storage_file\"
RAW_URL := \"raw_url\"

#compilation details

CC := g++
VERSION := -std=gnu++98
DEBUG_FLAGS := $(VERSION) -pedantic-errors -Wall -Wextra -g

LIBS := _libs
BIN := _bin

PATH_TO_LIBS := -L$(realpath .)/$(LIBS) -Wl,-rpath=$(realpath .)/$(LIBS) 

#utils (implemented completely in header file)

UTILS_HDRS := -I utils/

#singleton (implemented completely in header file)

SINGLETON_HDRS := -I singleton/

#runtime_config

RUNTIME_CONFIG := $(LIBS)/libruntime_config.so
RUNTIME_CONFIG_HDRS := -I runtime_config/
RUNTIME_CONFIG_SRCS := $(wildcard runtime_config/*.cpp)
RUNTIME_CONFIG_INCLUDE_HDRS := $(RUNTIME_CONFIG_HDRS) $(SINGLETON_HDRS) $(UTILS_HDRS)
RUNTIME_CONFIG_LIBS := -lboost_regex
RUNTIME_CONFIG_DEFINES := -DREGEX=$(REGEX) -DCONFIG_FILE=$(CONFIG_FILE)

#url_shortener

URL_SHORTENER := $(LIBS)/liburl_shortener.so
URL_SHORTENER_HDRS := -I url_shortener/
URL_SHORTENER_SRCS := $(wildcard url_shortener/*.cpp)
URL_SHORTENER_INCLUDE_HDRS := $(URL_SHORTENER_HDRS) $(SINGLETON_HDRS) $(RUNTIME_CONFIG_HDRS) $(UTILS_HDRS)
URL_SHORTENER_LIBS := -lboost_system -lboost_regex $(RUNTIME_CONFIG)
URL_SHORTENER_DEFINES := -DPATH_TO_URLS_STORAGE_FILE=$(PATH_TO_URLS_STORAGE_FILE) -DRAW_URL=$(RAW_URL)

#url_reader

URL_READER := $(LIBS)/liburl_reader.so
URL_READER_HDRS := -I url_reader/
URL_READER_SRCS := $(wildcard url_reader/*.cpp)
URL_READER_INCLUDE_HDRS := $(URL_READER_HDRS) $(RUNTIME_CONFIG_HDRS) $(SINGLETON_HDRS) $(UTILS_HDRS)
URL_READER_LIBS := -lcurl -lboost_regex -lboost_system -lboost_thread -lpthread $(RUNTIME_CONFIG)
URL_READER_DEFINES := -DCURL_POLL_TIMEOUT=$(CURL_POLL_TIMEOUT)

#test

TEST := $(BIN)/test.out
TEST_SRCS := test/test.cpp
TEST_INCLUDE_HDRS := $(URL_READER_HDRS) $(UTILS_HDRS) $(SINGLETON_HDRS) $(RUNTIME_CONFIG_HDRS) $(URL_SHORTENER_HDRS)
TEST_LIBS := -lcurl -lboost_regex -lboost_system -lboost_thread -lpthread $(RUNTIME_CONFIG) $(URL_READER) $(URL_SHORTENER)

test: $(TEST)

#libs

$(RUNTIME_CONFIG): $(RUNTIME_CONFIG_SRCS) $(RUNTIME_CONFIG_LIBS)
	$(CC) $(DEBUG_FLAGS) -shared -fPIC $^ -o $@ $(RUNTIME_CONFIG_INCLUDE_HDRS) $(RUNTIME_CONFIG_DEFINES)

$(URL_SHORTENER): $(URL_SHORTENER_SRCS) $(URL_SHORTENER_LIBS)
	$(CC) $(DEBUG_FLAGS) -shared -fPIC $^ -o $@ $(URL_SHORTENER_INCLUDE_HDRS) $(URL_SHORTENER_DEFINES)

$(URL_READER): $(URL_READER_SRCS) $(URL_READER_LIBS)
	$(CC) $(DEBUG_FLAGS) -shared -fPIC $^ -o $@ $(URL_READER_INCLUDE_HDRS) $(URL_READER_DEFINES)

#test

$(TEST): $(TEST_SRCS) $(TEST_LIBS) 
	$(CC) $(DEBUG_FLAGS) $(PATH_TO_LIBS) $^ -o $@ $(TEST_INCLUDE_HDRS) $(TEST_DEFINES)

#utilss

VALGRIND := valgrind --leak-check=yes --track-origins=yes
URLS_DATA_DIR := _urls_data

.PHONY: clean
clean:
	rm -f $(LIBS)/*.so 
	rm -f $(BIN)/*.out 
	rm -f $(URLS_DATA_DIR)/* 
	rm -f urls_storage.txt
	rm -f vg*
	rm -f core

run:
	sudo $(BIN)/test.out $(ARGS)

runvlg:
	sudo $(VALGRIND) $(BIN)/test.out $(ARGS)
