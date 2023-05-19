SRC_FILES=$(wildcard src/*.html src/**/*.html)
DST_FILES=$(patsubst src/%,%,$(filter-out src/header.html src/footer.html,$(SRC_FILES)))

.PHONY: all
all: $(DST_FILES)

%.html: src/%.html src/header.html src/footer.html
	m4 $< > $@

pages/%.html: src/pages/%.html src/header.html src/footer.html
	m4 $< > $@
