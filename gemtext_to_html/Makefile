###############
# ~ Testing ~ #
###############

.PHONY: test
test: test_begin gemtext_to_html_test text_test

.PHONY: test_begin
test_begin:
	@echo '~ Testing ~'

%_test: build/%_test
	@$<

.PRECIOUS: build/%_test
build/%_test: src/%_test.c src/testing.h src/arena.c src/arena.h src/astring.h src/%.h | build
	cc $? -o $@

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
