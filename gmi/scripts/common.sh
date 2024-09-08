#!/bin/env bash

##
# Utility functions

function check_header_line() {
    local PREFIX="-- ${1:?}"
    local LINE="${2:?}"

    if [[ "${PREFIX}" != `echo "${LINE}" | cut -d':' -f1` ]]
    then
        >&2 echo Line not found: \""${PREFIX}": ...\"
        >&2 echo Check spelling and position?
        exit 1
    fi
}

function article_date() {
    local IN_FILE=${1:?'Missing filename'}

    local LINE=`sed '1q;d' "${IN_FILE}"`
    check_header_line 'date' "${LINE}"

    echo ${LINE} | sed 's/-- [-_a-zA-Z0-9]*: //'
}

function article_title() {
    local IN_FILE=${1:?'Missing filename'}

    local LINE=`sed '2q;d' "${IN_FILE}"`
    local PREFIX="${LINE:0:2}"
    if [[ '# ' != "${PREFIX}" ]]
    then
        >&2 echo Title not found.
        exit 1
    fi

    echo ${LINE:2}
}

function up_to () {
    sed -n "0,/$1/p" "$2"
}

function after() {
    sed "0,/$1/d" "$2"
}

function html_header() {
    local TITLE="${1:?'Missing title.'}"
    local DATE="${2:-}"

    up_to 'contents' layout.html | m4 -D __date="${DATE}" -D __title="${TITLE}"
}

function html_contents() {
    local IN_FILE=${1:?'Missing filename.'}
    tail +3 "${IN_FILE}" | ${CONVERT}
}

function html_footer() {
    after 'contents' layout.html
}
