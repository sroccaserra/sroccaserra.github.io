#!/usr/bin/env bash

set -euo pipefail
source "scripts/common.sh"

src="${1:?'Missing source file name.'}"

title="$(article_title "$src")"

html_header "$title"
html_contents "$src"
bash scripts/toc.sh | ${CONVERT}
html_footer
