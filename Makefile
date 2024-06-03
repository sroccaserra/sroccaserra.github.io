SRC_ARTICLES=$(wildcard src/**/*.md)
DST_ARTICLES=$(patsubst src/%.md,%.html,$(SRC_ARTICLES))
MARKDOWN=perl lib/Markdown_1.0.1/Markdown.pl

.PHONY: all
all: index.html rss.xml $(DST_ARTICLES)

index.html: src/index.html src/layout.html $(SRC_ARTICLES) src/toc.sh
	@echo Updating Index...
	@m4 -P \
		-D __date='' \
		-D __title="Apprendre + Équipe = Programmes" \
		-D __toc='`'"$(shell src/toc.sh $(DST_ARTICLES))""'" \
		-D __contents="$<" \
		src/layout.html > "$@"

$(DST_ARTICLES): %.html: src/%.md | pages
	src/build_page.sh "$<" "$@"

pages:
	mkdir -p pages

rss.xml: index.html src/rss.xml
	@echo Updating RSS...
	@m4 -P \
		-D __items='`'"$(shell src/rss_items.sh "$(DST_ARTICLES)")""'" \
		src/rss.xml > "$@"

site.tar.gz: index.html
	tar --exclude-vcs --exclude-vcs-ignore -cvz . > site.tar.gz

.PHONY: clean
clean:
	rm -f index.html rss.xml pages/*

.PHONY: serve
serve:
	python3 -m http.server 8080

.PHONY: watch
watch:
	rg --files src style images Makefile | entr make
