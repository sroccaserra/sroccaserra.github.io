### Site

- <https://sroccaserra.srht.site>
- <gemini://sroccaserra.srht.site>

### Intention

Coder un site pour collecter mes articles avec le moins d'outils possible, si
possible ce qui est déjà installé sur un Linux pour développer.

Quelques détails techniques :
- Les articles sont écrits en [gemtext][gt], avec l'extension `.gmi`.
- Un convertisseur gemtext -> HTML écrit en C et ne dépendant que de la libc se
  trouve dans le répertoire `gemtext_to_html`
- Le titre et la date des articles sont injectés dans le layout par [m4][m4],
  qui est souvent installé par défaut.
- Les fichiers HTML complets sont générés par une règle [Make][make],
  uniquement si leurs dépendances ont changé.
- La liste des articles dans l'index est générée automatiquement.
- La liste des items dans le fichier rss.xml est générée automatiquement.
- Tapper `make` suffit pour mettre à jour tout ce qui doit l'être.
- Le site peut être publié en version HTML/HTTP avec la target `publish_html`,
  et en version gemtext/Gemini avec la target `publish_gmi`.
- Optionel : pour visualiser mes changements, j'utilise Python, installé aussi
  par défaut, pour démarrer un serveur HTTP local.

### Références

Inspirations pour coder ce site le plus simplement possible :

- All you may need is HTML ~ <https://fabiensanglard.net/html/index.html>
- Phil Hagelberg's Colophon ~ <https://technomancy.us/colophon>
- Phil Hagelberg's Makefile ~ <https://p.hagelb.org/Makefile.html>
- Frugarilla ~ <https://www.frugarilla.fr/>
- <https://danluu.com/>
- <https://motherfuckingwebsite.com/>
- <https://chrisman.github.io/9.html>
- <https://github.com/vkitchen/apostl>

Refs techniques :

- Gemini ~ <https://geminiprotocol.net/>
- [Gemini hypertext format, aka "gemtext", specification][gt]
- RSS2 ~ <https://validator.w3.org/feed/docs/rss2.html>

[gt]: https://geminiprotocol.net/docs/gemtext-specification.gmi
[m4]: https://www.gnu.org/software/m4/
[make]: https://www.gnu.org/software/make/
