SRC_ARTICLES=$(wildcard src/**/*.md)
DST_ARTICLES=$(patsubst src/%.md,%.html,$(SRC_ARTICLES))

.PHONY: all
all: index.html $(DST_ARTICLES)

index.html: src/index.html src/layout.html $(SRC_ARTICLES)
	m4 \
		-D __date='' \
		-D __title="Journal d'Exploration Logicielle" \
		-D __toc="$(shell bash src/toc.sh $(DST_ARTICLES))" \
		-D __contents="$<" \
		src/layout.html > "$@"

$(DST_ARTICLES): %.html: fragments/%.html src/layout.html
	m4 \
		-D __date=$(shell basename "$@" | cut -d_ -f1) \
		-D __title="$(shell basename "$@" .html | cut -d_ -f2- | tr _ ' ')" \
		-D __contents="$<" \
		src/layout.html > "$@"

fragments/%.html: fragments/pages src/%.md
	markdown "$(word 2, $^)" > "$@"

fragments/pages:
	mkdir -p fragments/pages

.PHONY: clean
clean:
	rm -f index.html $(DST_ARTICLES)
	rm -rf fragments

.PHONY: serve
serve:
	python3 -m http.server 8080
