#!/usr/bin/env bash

for f in $(ls **/*.gmi)
do
    echo "tail +3 $f | ${CONVERT} > ${BUILD}/\"${f%.gmi}.html\""
done
