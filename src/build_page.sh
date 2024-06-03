#!/bin/env bash

source src/common.sh

##
# Configuration

FRAGMENTS_DIR=fragments
MARKDOWN='lib/Markdown_1.0.1/Markdown.pl'

##
# Extracting info

IN_FILE="${1:?'Missing input file name'}"
OUT_FILE="${2:?'Missing output file name'}"
FRAGMENT_FILE="${FRAGMENTS_DIR}"/"${OUT_FILE}"

TITLE=`article_title ${IN_FILE}`
DATE=`article_date ${IN_FILE}`

##
# Building page

# Intermediary content file
mkdir -p `dirname "${FRAGMENT_FILE}"`
tail +3 "${IN_FILE}" | perl "${MARKDOWN}" > "${FRAGMENT_FILE}"

# Add layout and values
m4  -P \
    -D __date="${DATE}" \
    -D __title="${TITLE}" \
    -D __contents='`'"${FRAGMENT_FILE}'" \
    src/layout.html > "${OUT_FILE}"
