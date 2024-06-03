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

    echo ${LINE} | cut -d':' -f2- | xargs
}

function article_date() {
    local IN_FILE=${1:?'Missing filename'}

    local LINE=`sed '2q;d' "${IN_FILE}"`
    check_header_line 'date' "${LINE}"

    echo ${LINE} | cut -d':' -f2- | xargs
}
