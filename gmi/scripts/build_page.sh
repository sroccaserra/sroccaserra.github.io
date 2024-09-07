#!/usr/bin/env bash

set -euo pipefail
source "scripts/common.sh"

src="${1:?'Missing source file name.'}"

title="$(article_title "$src")"
date="$(article_date "$src")"

html_header "$title" "$date"
html_contents "$src"
html_footer
