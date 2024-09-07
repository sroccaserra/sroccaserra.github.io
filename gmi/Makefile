###############################################################################
# Config

MAKEFLAGS += --warn-undefined-variables
SHELL := /usr/bin/bash
.SHELLFLAGS := -eu -o pipefail -c

BUILD_HTML := build_html
CONVERT_TO_HTML := ../gemtext_to_html/build/gemtext_to_html

GMI_ARTICLES=$(wildcard **/*.gmi) index.gmi
HTML_ARTICLES=$(patsubst %.gmi,$(BUILD_HTML)/%.html,$(GMI_ARTICLES))


###############################################################################
# Building

all_html: $(HTML_ARTICLES) sync_public

$(BUILD_HTML)/pages/%.html: pages/%.gmi | $(BUILD_HTML)/pages
	BUILD="$(BUILD_HTML)" CONVERT="$(CONVERT_TO_HTML)" \
		  bash scripts/build_page.sh "$<" \
		  > "$@"

$(BUILD_HTML):
	mkdir -p "$@"

$(BUILD_HTML)/pages: | $(BUILD_HTML)
	mkdir -p "$@"

$(BUILD_HTML)/index.html: index.gmi | $(BUILD_HTML)
	BUILD=$(BUILD_HTML) CONVERT=$(CONVERT_TO_HTML) \
		  bash scripts/build_index.sh "$<" \
		  | sed 's/\.gmi"/\.html"/g' \
		  > "$@"

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
	rg --files $(GMI_ARTICLES) style images Makefile | entr make


###############################################################################
# Cleaning

.PHONY: clean
clean:
	rm -rf $(BUILD_HTML)
