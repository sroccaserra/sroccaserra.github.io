SRC_FILES=$(wildcard src/*.html src/**/*.html)
DST_FILES=$(patsubst src/%,%,$(filter-out src/header.html src/footer.html,$(SRC_FILES)))

.PHONY: all
all: $(DST_FILES)

$(DST_FILES): %.html: src/%.html src/header.html src/footer.html
	m4 -D __date=$(shell basename "$@" | cut -d_ -f1) \
		-D __title="$(shell basename "$@" .html | cut -d_ -f2- | tr _ ' ')" \
		"$<" > "$@"

.PHONY: serve
serve:
	python3 -m http.server 8080
