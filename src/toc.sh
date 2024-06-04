#!/bin/env bash

source src/common.sh

function toc_item() {
    local IN_FILE="src/${1%.html}.md"

    local TITLE=`article_title ${IN_FILE}`
    local DATE=`article_date ${IN_FILE}`

    echo "<li>${DATE} ~ <a href=\"/${1}\">${TITLE}</a></li>"
}

for file in `echo "$@" | tr ' ' '\n' | sort -r`
do
    toc_item $file
done
