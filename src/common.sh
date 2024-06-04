#!/bin/env bash

MARKDOWN='lib/Markdown_1.0.1/Markdown.pl'

##
# Utility functions

function check_header_line() {
    local PREFIX="-- ${1:?}"
    local LINE="${2:?}"

    if [[ "${PREFIX}" != `echo "${LINE}" | cut -d':' -f1` ]]
    then
        echo Line not found: \""${PREFIX}": ...\"
        echo Check spelling and position?
        exit 1
    fi
}

function article_title() {
    local IN_FILE=${1:?'Missing filename'}

    local LINE=`sed '1q;d' "${IN_FILE}"`
    check_header_line 'title' "${LINE}"

    echo ${LINE} | cut -d':' -f2- | xargs
}

function article_date() {
    local IN_FILE=${1:?'Missing filename'}

    local LINE=`sed '2q;d' "${IN_FILE}"`
    check_header_line 'date' "${LINE}"

    echo ${LINE} | cut -d':' -f2- | xargs
}

function html_header() {
    local TITLE="${1:?'Missing title.'}"
    local DATE="${2}"

    sed -n '0,/contents/p' src/layout.html | m4 -D __date="${DATE}" -D __title="${TITLE}"
}

function html_contents() {
    local IN_FILE=${1:?'Missing filename.'}
    tail +3 "${IN_FILE}" | perl "${MARKDOWN}"
}

function html_footer() {
    sed '0,/contents/d' src/layout.html
}
