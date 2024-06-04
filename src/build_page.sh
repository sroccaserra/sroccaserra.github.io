#!/bin/env bash

source src/common.sh

IN_FILE="${1:?'Missing input file name'}"
OUT_FILE="${2:?'Missing output file name'}"

TITLE=`article_title ${IN_FILE}`
DATE=`article_date ${IN_FILE}`

html_header "${TITLE}" "${DATE}" > "${OUT_FILE}"
html_contents "${IN_FILE}" >> "${OUT_FILE}"
html_footer >> "${OUT_FILE}"
