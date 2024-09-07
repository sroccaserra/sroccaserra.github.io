#!/bin/env bash

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

    echo ${LINE} | sed 's/-- [-_a-zA-Z0-9]*: //'
}

function article_date() {
    local IN_FILE=${1:?'Missing filename'}

    local LINE=`sed '2q;d' "${IN_FILE}"`
    check_header_line 'date' "${LINE}"

    echo ${LINE} | sed 's/-- [-_a-zA-Z0-9]*: //'
}

function up_to_contents_tag () {
    sed -n '0,/contents/p' "$1"
}

function html_header() {
    local TITLE="${1:?'Missing title.'}"
    local DATE="${2:-}"

    up_to_contents_tag layout.html | m4 -D __date="${DATE}" -D __title="${TITLE}"
}

function html_contents() {
    local IN_FILE=${1:?'Missing filename.'}
    tail +3 "${IN_FILE}" | ${CONVERT}
}

function html_contents_for_gmi() {
    local IN_FILE=${1:?'Missing filename.'}
    tail +3 "${IN_FILE}" | gemtext_to_html/build/gemtext_to_html
}

function after_contents_tag() {
    sed '0,/contents/d' "$1"
}

function html_footer() {
    after_contents_tag layout.html
}
