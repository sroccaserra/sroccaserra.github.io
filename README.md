### Site

- <https://sroccaserra.github.io/>

### Intention

Coder un site pour collecter mes articles avec le moins d'outils possible, si
possible ce qui est déjà installé sur un Linux pour développer.

Quelques détails techniques :
- Tous les fichiers sources sont dans `src/`, sauf le Makefile qui est à la
  racine.
- Pour le moment j'expérimente d'écrire mes articles directement en HTML dans
  Vim.
- Le header et footer sont ajoutés par [m4][m4], qui est souvent installé par
  défaut.
- Les fichiers HTML complets sont générés par une règle [Make][make],
  uniquement si leurs dépendances ont changé.
- La liste des articles dans l'index est générée automatiquement par une
  commande [awk][awk].
- Tapper `make` suffit pour mettre à jour tout ce qui doit l'être.
- Pour visualiser mes changements, j'utilise Python, installé aussi par défaut,
  pour démarrer un serveur HTTP local.

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

[m4]: https://www.gnu.org/software/m4/
[make]: https://www.gnu.org/software/make/
[awk]: https://www.gnu.org/software/gawk/
