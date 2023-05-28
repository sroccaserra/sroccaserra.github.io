#!/bin/env bash

echo "$@" \
    | tr ' ' '\n' \
    | sort -r \
    | awk '{ \
    date=substr($0,7,10) ; \
    title=substr($0,18) ; \
    sub(/.html$/,"",title); \
    gsub(/_/," ",title); \
    printf "<li>%s ~ <a href=\"/%s\">%s</a></li>\n", date, $0, title \
    }'
