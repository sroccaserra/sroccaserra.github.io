#!/usr/bin/env bash

set -euo pipefail
source "scripts/common.sh"

src="${1:?'Missing source file name.'}"

title="$(article_title "$src")"

html_header "$title"
up_to "## Articles" "$src" | tail +3 | ${CONVERT}
bash scripts/toc.sh | ${CONVERT}
after "## Articles" "$src" | ${CONVERT}
html_footer
