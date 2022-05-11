CC := g++
VERSION := -std=gnu++98
DEBUG_FLAGS := $(VERSION) -Weffc++ -pedantic-errors -Wall -Wextra -g

DEFINE_PATH_TO_STORAGE := -DPATH_TO_STORAGE=\"./storage\"
DEFINE_RAW_URL := -DRAW_URL=\"www.shorturl.com/\"

bin/url_shortener_debug.out: test/test_url_shortener.cpp src/url_shortener.cpp
	$(CC) $(DEBUG_FLAGS) $^ -o $@ -I include/ $(DEFINE_PATH_TO_STORAGE) $(DEFINE_RAW_URL)

.PHONY: clean
clean:
	rm -rf bin/* core vg* storage

open: 
	vim -p include/* src/* test/* makefile

run: bin/url_shortener_debug.out
	$^
