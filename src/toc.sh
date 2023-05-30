#!/bin/env bash

echo "$@" \
    | tr ' ' '\n' \
    | sort -r \
    | awk -f src/toc.awk
