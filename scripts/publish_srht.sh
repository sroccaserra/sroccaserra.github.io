#!/bin/env bash

set -eu -o pipefail

echo "Archiving ./${BUILD}..."
tar -C ${BUILD} -cz . > site.tar.gz

echo "Publishing ${PROTOCOL:-HTML}..."

source .env && \
    curl --oauth2-bearer "$srht_token" \
    -Fcontent=@site.tar.gz \
    -Fprotocol=${PROTOCOL:-} \
    https://pages.sr.ht/publish/sroccaserra.srht.site
