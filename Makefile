SRC_FILES=$(wildcard src/*.html src/**/*.html)
DST_FILES=$(patsubst src/%,%,$(filter-out src/index.html src/header.html src/footer.html,$(SRC_FILES)))

.PHONY: all
all: index.html $(DST_FILES)

index.html: src/index.html src/header.html src/footer.html
	m4 -D __date='' \
		-D __title="Journal d'exploration logicielle" \
		src/header.html "$<" src/footer.html > "$@"

$(DST_FILES): %.html: src/%.html src/header.html src/footer.html
	m4 -D __date=$(shell basename "$@" | cut -d_ -f1) \
		-D __title="$(shell basename "$@" .html | cut -d_ -f2- | tr _ ' ')" \
		src/header.html "$<" src/footer.html > "$@"

.PHONY: serve
serve:
	python3 -m http.server 8080
