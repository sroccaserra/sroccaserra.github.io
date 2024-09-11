#!/usr/bin/env bash

set -euo pipefail
source "scripts/common.sh"

src="${1:?'Missing source file name.'}"

function rss_item() {
    local IN_FILE="$1"
    local URL="${BASE_URL}/${IN_FILE%.gmi}.html"

    local TITLE=`article_title ${IN_FILE}`
    local DATE=`article_date ${IN_FILE}`

    cat <<EOF
        <item>
            <title>${TITLE}</title>
            <link>${URL}</link>
            <description/>
            <pubDate>${DATE}</pubDate>
            <guid>${URL}</guid>
        </item>
EOF
}

function rss_items() {
    for file in `find pages -type f | sort -r`
    do
        rss_item $file
    done
}

up_to "-- contents --" "$src"
rss_items
after "-- contents --" "$src"
