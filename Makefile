SRC_ARTICLES=$(wildcard src/**/*.md)
DST_ARTICLES=$(patsubst src/%.md,%.html,$(SRC_ARTICLES))

.PHONY: all
all: index.html rss.xml $(DST_ARTICLES)

index.html: src/index.html src/layout.html $(SRC_ARTICLES) src/toc.sh
	@echo Updating Index...
	@m4 \
		-D __date='' \
		-D __title="Apprendre + Équipe = Programmes" \
		-D __toc="$(shell bash src/toc.sh $(DST_ARTICLES))" \
		-D __contents="$<" \
		src/layout.html > "$@"

$(DST_ARTICLES): %.html: fragments/%.html
	@m4 \
		-D __date=$(shell basename "$@" | cut -d_ -f1) \
		-D __title="$(shell basename "$@" .html | cut -d_ -f2- | tr _ ' ')" \
		-D __contents="$<" \
		src/layout.html > "$@"

fragments/%.html: fragments/pages src/%.md src/layout.html
	markdown "$(word 2, $^)" > "$@"

fragments/pages:
	mkdir -p fragments/pages

rss.xml: index.html src/rss.xml
	@echo Updating RSS...
	@m4 -P \
		-D __items="$(shell bash src/rss_items.sh "$(DST_ARTICLES)")" \
		src/rss.xml > "$@"

.PHONY: clean
clean:
	rm -f index.html rss.xml pages/*
	rm -rf fragments

.PHONY: serve
serve:
	python3 -m http.server 8080

.PHONY: watch
watch:
	rg --files src style images Makefile | entr make
