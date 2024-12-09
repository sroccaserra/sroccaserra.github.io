MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := main

CFLAGS := -g -Og

MAIN_DEPENDENCIES := src/gemtext_to_html.c \
					 src/gemtext_to_html.h \
					 src/arena.c \
					 src/arena.h \
					 src/text.c \
					 src/text.h
MAIN_C_FILES := $(filter %.c,$(MAIN_DEPENDENCIES))

###############
# ~ Running ~ #
###############

.PHONY: run
run: build/gemtext_to_html
	@cat test.gmi | $<

build/gemtext_to_html: src/main.c
build/gemtext_to_html: $(MAIN_DEPENDENCIES)
build/gemtext_to_html: | build
	cc $(CFLAGS) -o "$@" "$<" $(MAIN_C_FILES)

###############
# ~ Testing ~ #
###############

.PHONY: test
test: gemtext_to_html_test
test: text_test

%_test: build/%_test
	@$<

build/gemtext_to_html_test: src/gemtext_to_html_test.c
build/gemtext_to_html_test: $(MAIN_DEPENDENCIES)
build/gemtext_to_html_test: src/testing.h
build/gemtext_to_html_test: | build
	@echo -n building "$@"...
	@cc $(CFLAGS) -o "$@" "$<" $(MAIN_C_FILES)
	@echo ✅

build/text_test: src/text_test.c
build/text_test: src/text.c
build/text_test: src/text.h
build/text_test: src/arena.c
build/text_test: src/arena.h
build/text_test: | build
	@echo -n building "$@"...
	@cc $(CFLAGS) -o "$@" "$<" src/arena.c src/text.c
	@echo ✅

.PHONY: mem_check
mem_check:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full build/gemtext_to_html_test

################
# ~ Building ~ #
################

.PHONY: main
main: build/gemtext_to_html

build:
	@mkdir -p build

################
# ~ Cleaning ~ #
################

.PHONY: clean
clean:
	rm -rf build
