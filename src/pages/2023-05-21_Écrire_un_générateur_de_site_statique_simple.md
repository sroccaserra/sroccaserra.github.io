-- title: Écrire un générateur de site statique simple
-- date: 2023-05-21

J'en avais assez de publier mes textes persos sur dev.to, où je restais
parce-que je ne savais pas vraiment où publier sans trop m'embêter. Comme j'ai
récemment écrit un article sur l'utilité de savoir construire ses outils, je me
suis dit que je n'avais qu'à me construire mon propre générateur de site
statique. J'ai fait ça en quelques heures pour m'amuser 🎉

Résultat :

- 28 loc de Makefile pour convertir le markdown en html et appliquer le layout
  commun.
- 11 loc de shell pour générer la table des matières.
- Une seule dépendance de 18 ko qui ne change plus depuis 2004 (markdown
  basique).
- Utilise quelques commandes qu'on a déjà sur un Linux de dev (`make`, `m4`,
  `grep`, `cut`, `tr`, `awk`, perl 5 pour markdown).
- Zéro framework.
- Zéro tracker addictif.
- Zéro scroll infini addictif.
- Zéro recommandations addictives.
- Je suis passé d'un éco index de 56 sur dev.to à 95 environ (?)

Et ça juste marche 😮

Il me reste à trouver un vrai titre à ce site (le titre actuel est nul), et à
faire un aspect visuel correct en quelques lignes de CSS. Il y a un lien vers
le code source en bas de la page.

- <https://sroccaserra.github.io/> (normalement le site où est cet article)

Ce que j'ai me semble suffisant :

- Tapper `make` suffit pour mettre à jour tout ce qui doit l'être.
- Un layout commun est appliqué automatiquement.
- La liste des articles est générée automatiquement.
- J'écris mes articles en markdown basique (pas de fioritures => le script
  markdown original de 18 ko suffit, c'est stable depuis 2004, pas de fancy
  générateur de 150+ Mo qui fait le café).
- La dépendance vers markdown est facile à annuler : je peux revenir à du HTML
  pur en quelques minutes en utilisant les pages générées.
- Pour le code, la balise `<pre>` plus quelques balises `<b>` pour mettre en
  valeur une ou deux choses suffisent largement à mes besoins, pas besoin de
  syntax highlighter.
- Pour visualiser mes changements j'utilise le Python installé par défaut pour
  démarrer un serveur HTTP local (un one-liner, voir Makefile).
- J'héberge le site statique sur GitHub Pages, pour un développeur ça me paraît
  largement suffisant.

L'expérience, en plus d'être amusante, m'a fait ressentir non pas une plus
grande contrainte mais au contraire une libération, une plus grande légèreté.
En m'appuyant sur des technologies de base que je connais déjà depuis 20 ans,
qui existent depuis encore plus longtemps, qui sont déjà installées partout, et
qui sont stables, je me libère&nbsp;:

- D'avoir à choisir le "meilleur" générateur de site statique (SSG ?) du
  moment.
- Du poids d'avoir à mettre à jour en permanence mes dépendances.
- D'avoir à lire des changelogs et réparer des breaking changes tous les X ans
  ou Y mois.
- D'avoir à installer le framework X en version Y sur un nouveau PC pour
  travailler sur mon site.
- D'avoir à installer Node.js en version X ou Ruby en version Y ou Go en
  version Z sur un nouveau PC pour travailler sur mon site.
- Du risque qu'un beau matin mon générateur de site statique soit cassé car
  Node.js, Ruby, ou Go, ou une dépendance d'une dépendance, ou autre a changé
  par surprise.

## Liens

- Les 28 loc de Makefile ~ [Makefile][mf]
- Les 11 loc de script shell ~ [src/toc.sh][sh]
- Le script markdown 1.0.1 de 2004 ~ [daringfireball.net/projects/markdown/][md]

[mf]: https://github.com/sroccaserra/sroccaserra.github.io/blob/5e17de3/Makefile
[sh]: https://github.com/sroccaserra/sroccaserra.github.io/blob/aeb8c9b/src/toc.sh
[md]: https://daringfireball.net/projects/markdown/

Les inspirations qui m'ont permis de construire ce générateur simplement et en
peu de temps&nbsp;:

- All you may need is HTML ~ [fabiensanglard.net/html][fs]
- Phil Hagelberg's Colophon ~ [technomancy.us/colophon][tm]
- Phil Hagelberg's Makefile ~ [p.hagelb.org/Makefile.html][ph]
- Les collègues de Frugarilla ~ [frugarilla.fr][fr]
- [danluu.com][dl]
- [motherfuckingwebsite.com][mfws]
- [chrisman.github.io/9.html][ch]
- [github.com/vkitchen/apostl][ap]

[fs]: https://fabiensanglard.net/html/index.html
[tm]: https://technomancy.us/colophon
[ph]: https://p.hagelb.org/Makefile.html
[fr]: https://www.frugarilla.fr/
[dl]: https://danluu.com/
[mfws]: https://motherfuckingwebsite.com/
[ch]: https://chrisman.github.io/9.html
[ap]: https://github.com/vkitchen/apostl
