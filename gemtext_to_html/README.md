## Why

Allow my blog to move from Markdown to gemtext for the input, and then remove
the dependency on Perl for the Markdown script I use at the moment.

## What

Convert a gemtext file to an HTML view.

Will not generate a &lt;head> or &lt;body> tags, only the content.

The input comes from stdin and is output to stdout.

How I could use it:

```
cat src/pages/test.gmi | gemtext_to_html > pages/test.html
```

## Decisions

### HTML markup in the input

In a line of text, we could want to allow some HTML markup in the input, like
\&nbsp; or &lt;b>. Markdown allows this.

So if: "toto & tata" > "toto \&amp; tata"

We could also want not to convert an already present \&amp;.
"toto \&amp; tata" > "toto \&amp; tata"

In the original markdown, it is implemented by a complex regex.

Decision: I don't support HTML in the input for the moment.

## Run test

The test files are named `*_test.c`.

To run the tests:

```
$ make test
gemtext_to_html... ✅
text... ✅
```

## References

Specifications:

- https://geminiprotocol.net/docs/gemtext-specification.gmi
