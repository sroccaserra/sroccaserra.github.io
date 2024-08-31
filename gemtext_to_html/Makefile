###############
# ~ Testing ~ #
###############

.PHONY: test
test: gemtext_to_html_test
test: text_test

%_test: build/%_test
	@$<

build/gemtext_to_html_test: src/gemtext_to_html_test.c
build/gemtext_to_html_test: src/gemtext_to_html.h
build/gemtext_to_html_test: src/gemtext_to_html.c
build/gemtext_to_html_test: src/arena.c
build/gemtext_to_html_test: src/arena.h
build/gemtext_to_html_test: src/astring.c
build/gemtext_to_html_test: src/astring.h
build/gemtext_to_html_test: src/testing.h
build/gemtext_to_html_test: src/text.h
build/gemtext_to_html_test: | build
	cc -g -Og -o "$@" \
		src/gemtext_to_html_test.c \
		src/gemtext_to_html.c \
		src/arena.c \
		src/astring.c

build/text_test: src/text_test.c
build/text_test: src/text.h
build/text_test: src/arena.c
build/text_test: src/arena.h
build/text_test: | build
	cc -g -Og -o "$@" \
		src/text_test.c \
		src/arena.c

.PHONY: mem_check
mem_check:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full build/gemtext_to_html_test

################
# ~ Building ~ #
################

build:
	@mkdir -p build

################
# ~ Cleaning ~ #
################

.PHONY: clean
clean:
	rm -rf build
