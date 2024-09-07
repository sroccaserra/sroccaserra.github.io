###############################################################################
# Config

BUILD := build
CONVERT_TO_HTML := ../gemtext_to_html/build/gemtext_to_html

GMI_ARTICLES=$(wildcard **/*.gmi) index.gmi
HTML_ARTICLES=$(patsubst %.gmi,$(BUILD)/%.html,$(GMI_ARTICLES))


###############################################################################
# Building

html_all: $(HTML_ARTICLES) sync_public

$(BUILD)/pages/%.html: pages/%.gmi | $(BUILD)/pages
	BUILD="$(BUILD)" CONVERT="$(CONVERT_TO_HTML)" \
		  bash scripts/build_page.sh "$<" \
		  > "$@"

$(BUILD):
	mkdir -p "$@"

$(BUILD)/pages: | $(BUILD)
	mkdir -p "$@"

$(BUILD)/index.html: index.gmi | $(BUILD)
	BUILD=$(BUILD) CONVERT=$(CONVERT_TO_HTML) \
		  bash scripts/build_index.sh "$<" \
		  | sed 's/\.gmi"/\.html"/g' \
		  > "$@"

.PHONY: sync_public
sync_public: | $(BUILD)
	@rsync -au public/ build

###############################################################################
# Serving

.PHONY: serve
serve:
	python3 -m http.server 8080 --directory build

.PHONY: watch
watch:
	rg --files $(GMI_ARTICLES) style images Makefile | entr make


###############################################################################
# Cleaning

.PHONY: clean
clean:
	rm -rf $(BUILD)
