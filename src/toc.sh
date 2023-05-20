#!/bin/env bash

echo "$@" \
    | tr ' ' '\n' \
    | sort -r \
    | awk '{ \
    label=$1 ; \
    sub(/^pages\//, "", label) ; \
    sub(/\.html$/, "", label); \
    sub(/_/, " ~ ", label) ; \
    gsub(/_/, " ", label) ; \
    printf "<li><a href=\"/%s\">%s</a></li>\n", $1, label \
    }'
