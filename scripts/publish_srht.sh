tar -cvz *.html robots.txt rss.xml favicon.ico pages images style \
    > site.tar.gz
source .env && \
    curl --oauth2-bearer "$srht_token" \
    -Fcontent=@site.tar.gz \
    https://pages.sr.ht/publish/sroccaserra.srht.site
