#!/bin/env awk

{
    date = substr($0,7,10);
    title = substr($0,18);
    sub(/.html$/, "", title);
    gsub(/_/, " ", title);
    url = "https://sroccaserra.github.io/"$0 ;
    printf "<item><title>%s</title><link>%s</link><description/><pubDate>%s</pubDate><guid>%s</guid></item>\\n", title, url, date, url;
}
