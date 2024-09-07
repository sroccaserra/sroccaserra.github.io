tar -C build -cvz . > site.tar.gz
source .env && \
    curl --oauth2-bearer "$srht_token" \
    -Fcontent=@site.tar.gz \
    -Fprotocol=${PROTOCOL} \
    https://pages.sr.ht/publish/sroccaserra.srht.site
