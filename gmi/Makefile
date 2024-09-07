###############################################################################
# Config

BUILD := build
CONVERT := ../gemtext_to_html/build/gemtext_to_html

###############################################################################
# Building

.PHONY: pages
pages: | $(BUILD)
	BUILD=$(BUILD) CONVERT=$(CONVERT) bash scripts/build_pages.sh

$(BUILD):
	mkdir -p $@

$(BUILD)/pages: $(BUILD)
	mkdir -p $@

###############################################################################
# Cleaning

.PHONY: clean
clean:
	rm -rf $(BUILD)
