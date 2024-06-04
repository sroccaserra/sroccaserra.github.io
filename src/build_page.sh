#!/bin/env bash

source src/common.sh

IN_FILE="${1:?'Missing input file name'}"

TITLE=`article_title ${IN_FILE}`
DATE=`article_date ${IN_FILE}`

html_header "${TITLE}" "${DATE}"
html_contents "${IN_FILE}"
html_footer
