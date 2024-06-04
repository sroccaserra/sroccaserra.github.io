#!/usr/bin/env bash

source src/common.sh

IN_FILE="${1:?'Missing input file name'}"
PAGES="${@:2}"

TITLE='Apprendre + Équipe = Programmes'
TOC=`src/toc.sh "${PAGES}"`

html_header "${TITLE}"
m4 -P -D__toc="[[${TOC}]]" "${IN_FILE}"
html_footer
