#!/usr/bin/env bash

set -euo pipefail
source "scripts/common.sh"

function build_page() {
    local src="${1:?'Missing source file name.'}"
    local dst="${BUILD}/${src%.gmi}.html"
    mkdir -p "$(dirname $dst)"

    local title="$(article_title "$src")"
    local date="$(article_date "$src")"

    html_header "$title" "$date" > "$dst"
    html_contents "$src" >> "$dst"
    html_footer >> "$dst"
}

function build_pages() {
    for src in $(ls *.gmi **/*.gmi)
    do
        echo "$src"
        build_page "$src"
    done
}

build_pages
