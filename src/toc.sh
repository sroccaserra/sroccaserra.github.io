#!/bin/env bash

source src/common.sh

function toc_item() {
    IN_FILE="src/${1%.html}.md"

    TITLE=`article_title ${IN_FILE}`
    DATE=`article_date ${IN_FILE}`

    echo -en "<li>${DATE} ~ <a href=\"/${1}\">${TITLE}</a></li>EOL"
}

for file in `echo "$@" | tr ' ' '\n' | sort -r`
do
    toc_item $file
done
