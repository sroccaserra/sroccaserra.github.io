SRC_FILES=$(wildcard src/*.html src/**/*.html)
DST_ARTICLES=$(patsubst src/%,%,$(filter-out src/index.html src/layout.html,$(SRC_FILES)))

.PHONY: all
all: index.html $(DST_ARTICLES)

index.html: src/index.html src/layout.html $(shell find src/pages/ -type f)
	m4 \
		-D __date='' \
		-D __title="Journal d'exploration logicielle" \
		-D __toc="$(shell bash src/toc.sh $(DST_ARTICLES))" \
		-D __contents="$<" \
		src/layout.html > "$@"

$(DST_ARTICLES): %.html: src/%.html src/layout.html
	m4 \
		-D __date=$(shell basename "$@" | cut -d_ -f1) \
		-D __title="$(shell basename "$@" .html | cut -d_ -f2- | tr _ ' ')" \
		-D __contents="$<" \
		src/layout.html > "$@"

.PHONY: serve
serve:
	python3 -m http.server 8080
