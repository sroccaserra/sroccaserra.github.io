#!/bin/env bash

source scripts/common.sh

function toc_item() {
    local IN_FILE="$1"

    local TITLE=`article_title ${IN_FILE}`
    local DATE=`article_date ${IN_FILE}`

    echo "=> ${1} ${DATE} ~ ${TITLE}"
}

for file in `find pages -type f | sort -r`
do
    toc_item $file
done
