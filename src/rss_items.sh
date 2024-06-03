#!/bin/env bash

source src/common.sh

function rss_item() {
    local HTML_FILE="${1:?'Missing html file name'}"
    local MD_FILE="src/${HTML_FILE%.html}.md"
    local URL="https://sroccaserra.github.io/${HTML_FILE}"

    local TITLE=`article_title ${MD_FILE}`
    local DATE=`article_date ${MD_FILE}`

    echo -en "<item><title>${TITLE}</title><link>${URL}</link><description/><pubDate>${DATE}</pubDate><guid>${URL}</guid></item>EOL"
}

for file in `echo "$@" | tr ' ' '\n' | sort -r`
do
    rss_item $file
done
