## why

Avoir un blog sans dépendances autre que build-essentials. À l'heure actuel mon
blog dépend de Perl pour convertir markdown en HTML.

## what

convertir depuis le format gemtext vers le format HTML

Ne génère pas de head ni de body, uniquement le contenu.

L'input arrive par stdin et sort par stdout, c'est l'usage utile pour mon
process actuel.

Exemple d'usage:

```
cat src/pages/test.gmi | gemtext_to_html > pages/test.html
```

Spécifications :

- https://geminiprotocol.net/docs/gemtext-specification.gmi
