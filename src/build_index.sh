#!/usr/bin/env bash

source src/common.sh

IN_FILE="${1:?'Missing input file name'}"
OUT_FILE="${2:?'Missing output file name'}"
PAGES="${@:3}"

TITLE='Apprendre + Équipe = Programmes'
TOC=`src/toc.sh "${PAGES}"`

html_header "${TITLE}" > "${OUT_FILE}"
m4 -P -D__toc="[[${TOC}]]" "${IN_FILE}" >> "${OUT_FILE}"
html_footer >> "${OUT_FILE}"
