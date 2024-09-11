###############################################################################
# Config

MAKEFLAGS += --warn-undefined-variables
SHELL := /usr/bin/bash
.SHELLFLAGS := -eu -o pipefail -c

BUILD_HTML := build_html
BUILD_GMI := build_gmi
CONVERT_TO_HTML := gemtext_to_html/build/gemtext_to_html -c center
BASE_URL := https://sroccaserra.shrt.site

GMI_IN_FILES=$(wildcard pages/*.gmi) index.gmi
GMI_OUT_FILES=$(patsubst %.gmi,$(BUILD_GMI)/%.gmi,$(GMI_IN_FILES))
HTML_OUT_FILES=$(patsubst %.gmi,$(BUILD_HTML)/%.html,$(GMI_IN_FILES))


###############################################################################
# Building

.PHONY: all_html
all_html: $(HTML_OUT_FILES) sync_public $(BUILD_HTML)/rss.xml

.PHONY: all_gmi
all_gmi: $(GMI_OUT_FILES)

$(BUILD_HTML)/pages/%.html: pages/%.gmi | $(BUILD_HTML)/pages
	BUILD="$(BUILD_HTML)" CONVERT="$(CONVERT_TO_HTML)" \
		  bash scripts/build_page.sh "$<" \
		  > "$@"

$(BUILD_GMI)/pages/%.gmi: pages/%.gmi | $(BUILD_GMI)/pages
	tail +2 "$<" > "$@"

$(BUILD_HTML):
	mkdir -p "$@"

$(BUILD_GMI):
	mkdir -p "$@"

$(BUILD_HTML)/pages: | $(BUILD_HTML)
	mkdir -p "$@"

$(BUILD_GMI)/pages: | $(BUILD_GMI)
	mkdir -p "$@"

$(BUILD_HTML)/index.html: index.gmi | $(BUILD_HTML)
	BUILD=$(BUILD_HTML) CONVERT="$(CONVERT_TO_HTML)" \
		  bash scripts/build_index.sh "$<" \
		  | sed 's/\.gmi"/\.html"/g' \
		  > "$@"
	sed -i'' 's/<li>\([^>]\+>\)\([0-9-]\+ \~ \)/<li>\2\1/' \
		$(BUILD_HTML)/index.html
	sed -i'' 's/>Mastodon</ rel="me">Mastodon</' \
		$(BUILD_HTML)/index.html
	sed -i'' 's/>RSS</>RSS <img class="pixel rss_sticker" \/></' \
		$(BUILD_HTML)/index.html
	awk 'NR==1,/<ul>/{sub(/<ul>/, "<ul class=\"banner\">")} 1' \
		$(BUILD_HTML)/index.html > $(BUILD_HTML)/tmp.html
	mv $(BUILD_HTML)/{tmp,index}.html

$(BUILD_HTML)/rss.xml: rss_layout.xml $(BUILD_HTML)/index.html
	@echo Updating RSS...
	BASE_URL=$(BASE_URL) \
			 bash scripts/build_rss.sh "$<" \
			 > "$@"

$(BUILD_GMI)/index.gmi: index.gmi | $(BUILD_GMI)
	tail +2 "$<" | sed -n '0,/## Articles/p' > "$@"
	bash scripts/toc.sh >> "$@"
	sed '0,/## Articles/d' "$<" >> "$@"

.PHONY: sync_public
sync_public: | $(BUILD_HTML)
	@rsync -au public/ $(BUILD_HTML)

###############################################################################
# Serving

.PHONY: serve
serve:
	python3 -m http.server 8080 --directory $(BUILD_HTML)

.PHONY: watch
watch:
	rg --files $(GMI_IN_FILES) style images Makefile | entr make

###############################################################################
# Publishing

.PHONY: publish_html
publish_html: all_html
	BUILD=$(BUILD_HTML) bash scripts/publish_srht.sh

.PHONY: publish_gmi
publish_gmi: all_gmi
	BUILD=$(BUILD_GMI) PROTOCOL=GEMINI bash scripts/publish_srht.sh

###############################################################################
# Cleaning

.PHONY: clean
clean:
	rm -rf $(BUILD_HTML)
	rm -rf $(BUILD_GMI)
