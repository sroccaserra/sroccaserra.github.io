-- title: NewCrafts Paris 2023 ~ Clare Sudbery
-- date: 2023-06-08

Les 25 et 26 mai, j'ai assisté à la conférence NewCrafts Paris 2023. C'était
chouette de revoir plein de monde au même endroit ! Il y avait aussi des
interventions de qualité, voilà une partie de mes notes sur ce que j'ai appris
ou révisé.

- <https://ncrafts.io/>

Ce sont des notes très partielles, à mon usage personnel. Il y a des choses
importantes que je n'ai pas notées car je les ai déjà bien en tête.

Je vous invite à voir les vidéos des conférences qui vous intéressent quand
elles seront publiées (le mois prochain normalement).

- <https://vimeo.com/newcrafts>

Dans ce troisième article, mes notes sur la présentation de Clare Sudbery.

Dans les articles suivants, j'ai prévu de partager mes notes sur les
interventions de&nbsp;:

- Jessica Kerr
- Kent Beck

## Clare Sudbery

J'ai trouvé cette présentation intéressante sur trois points : elle parle de ce
que le Refactoring n'est pas, ensuite elle parle des freins au Refactoring,
puis elle aborde le refactoring sous l'angle de la compassion.

Si vous souhaitez découvrir la notion de Refactoring, je vous invite à
consulter ce livre et les ressources associées&nbsp;:

- [Le livre Refactoring][rf], de Martin Fowler.

[rf]: https://martinfowler.com/books/refactoring.html

### Ce que le Refactoring n'est pas

J'entends souvent (et j'emploie parfois) le mot Refactoring pour désigner tout
ce qui n'ajoute pas de fonctionnalité pour les utilisateurs et utilisatrices,
et je trouve que c'est un peu dommage car ça peut conduire à une "Refactoring
Fatigue" et ajouter un frein supplémentaire à cette pratique indispensable.

Quand on dit "Refactoring" pour les choses ci-dessous, il vaut mieux remplacer
ce mot par... les termes ci-dessous&nbsp;:

- Une réécriture from scratch
- Un gain de performance
- Améliorer l'expérience utilisateur·ice
- Ajouter une nouvelle fonctionnalité
- Une correction de bug

### Astuces pour Refactorer

De bons conseils rappelés au passage&nbsp;:

- Refactorer par petits morceaux
- Commencer par rendre testable
- Toujours conserver les tests verts
- Refactorer les parties qui ont de l'impact

Refactorer par petits morceaux&nbsp;: en effet, on n'a pas envie de démonter
toute la voiture et de se retrouver avec toutes les pièces éparpillées sur le
sol.

Refactorer les parties qui ont de l'impact : oui, changer des parties stables
qui ont peu d'impact sur le reste du code, même si on tombe dessus par hasard
et qu'elles ne nous plaisent pas est une très mauvaises façon de prioriser les
choses.

### Les freins au Refactoring

Il y a de nombreux freins au Refactoring, et même un cercle vicieux&nbsp;:

> The less you refactor, the less you want to refactor
>
> — Ron Jeffries

Voilà les freins abordés par Clare&nbsp;

- La pression extérieure. Les deadlines. La croyance qu'on n'a pas le temps ou
  qu'on n'a pas la permission.
- Le manque de patience, ma propre impatience.
- La recherche de la perfection. Les autres font des choses parfaites
  (dirait-on), les autres nous racontent comment faire, comme dans les confs.
- La culpabilité, la honte, le désespoir. Ce n'est pas motivant. Je pourrais
  faire mieux, je m'en veux de ne pas le faire, je n'en parle même pas.
- Je ne sais pas faire. On n'a pas confiance en nos capacités, on n'a pas
  confiance en notre opinion.
- Le manque de compassion.

<!--

Ducks are the funniest animals. We need fun.

No spears, no spikes, just running and jumping. Let’s do our work without the
obstacles. But removing blockers is not easy.

-->

Dans ce qui suit, Clare propose d'utiliser la compassion pour réussir à
supprimer ces freins, qui sont bien tenaces.

La compassion peut permettre de&nbsp;:

- Mitiger la pression extérieure.
- Compenser l'impatience.
- Accepter l'imperfection.
- Croire en nous.
- Rechercher la joie, l'enthousiasme. Michael "GeePaw" Hill parle de "Geek
  Joy".

### Les Deadlines

Une astuce simple, mais difficile à faire : demander plus de temps. Déplacer la
deadline. De toutes façon en réalité la deadline qui a été décidée est
arbitraire et irréaliste.

D'autant plus que sur le long terme on gagne même du temps à faire ça en
pratique.

On n'y arrivera pas sans compassion.

Et il y aura toujours de nouvelles choses à faire&nbsp;: c'est une todo list
sans fond.

Au lieu de dire "nous allons livrer X pour une date Y", dire&nbsp;: "nous
allons faire une chose à la fois, priorisé, par ordre d'importance".

Promettre de livrer des chose à une date donnée ne suffit pas pour que ça
arrive de toutes façon. On ne réussit qu'à mettre les gens en colère à cause
des dates non tenues.

Ces conversations sont plus faciles si on fait preuve de compassion.

Il faut du temps pour penser. Si on n'a pas de temps, on ne pense pas. C'est ok
de demander du temps&nbsp;: "J'ai besoin de temps et d'espace de réflexion pour
y penser".

### L'Impatience

C'est ok de se pardonner pour ne pas avoir écrit un code parfait. Faire montre
de compassion entre nous.

### L'injonction à la perfection

Tout est imparfait. Accepter l'imperfection. Même les célébrités qui font des
conférences et écrivent des livres sont imparfaits&nbsp;:

> There are things that I think are good but that I don’t always do, and things
> that I think are not so good, that I sometimes do.
>
> — Ron Jeffries

Acceptons nos propres limites.

Contrairement aux sculpteurs, on n'a pas de bloc de pierre pour commencer, on
n'a pas de matière première pour commencer&nbsp;: on doit générer notre
matière. Ergo, conseil&nbsp;: faites votre bloc de pierre. Faite une première
version qui sera mauvaise. Ensuite commencer à la sculpter pour lui faire
prendre la bonne forme.


Pour ça, une compétence très importante est de savoir faire de petites
améliorations. Michael "GeePaw" Hill a un nom pour ça&nbsp;: MMMSS, ou Many
More Much Smaller Steps.

- [Many More Much Smaller Steps (MMMSS)][mmmss]

Clare dit même que si on ne retient qu'une chose de cette présentaion, ce sont les MMMSS.

Compassion: accepter de petites améliorations.

[mmmss]: https://www.geepawhill.org/series/many-more-much-smaller-steps/

### Se faire confiance

Dans l'équipe on discute d'énormément de sujet en permanence, et on entend
toutes ces personnes parler si brillamment de tous ces sujets ! Suite à ça on
est souvent victime de ce que Clare appelle "la roue de la confusion". Je crois
que Bob et Alice sont extras et que moi j'ai du mal. Mais en réalité, tout le
monde a la même impression, chacun et chacune s'inquiète aussi, pas
nécessairement sur la même chose que moi. Bob croit que Alice et moi sommes
extras, mais qu'il a du mal. Alice croit que Bob et moi sommes extras, mais
qu'elle a du mal.  C'est la roue de la confusion.

On peut aussi inverser une croyance&nbsp; "Je ne peux pas refactorer parce-que
je ne le comprend pas" --> "Je peux me servir du refactoring pour le
comprendre" (super astuce).

### Chercher la joie

Ça peut être enthousiasmant, ça peut être satisfaisant. Travailler à créer les
conditions pour que le travail intellectuel soit agréable, pour qu'il soit
valorisé. Pour que les personnes n'aient pas besoin de demander la permission.
Tout sera plus efficace. Et ça n'arrive pas au hasard.

Trouver des façons de faire que ce qu'on aime fasse partie de notre travail.
Les choses qu'on aime ont de la valeur.

## En résumé

Refactoring rend les choses plus facile à comprendre et moins coûteuses à
modifier.

Le refactoring se fait&nbsp;:

- En continu.
- Par petites étapes peu risquées.
- De manière testable.

Le refactoring est moins probable quand&nbsp;:

- Peu de compassion
- Dates cibles déraisonnables
- Standards élevés irréalistes
- Sentiment de culpabilité ou de honte

Le refactoring est plus probable avec :

- De la COMPASSION
- Du Temps
- L'Acceptation de l'imperfection
- La Concentration sur de petites améliorations (MMMSS)
- La Confiance en nous
- Trouver des façons d'aimer ce qu'on fait

## Liens

- [Site Medium de Clare Sudbery][ws]
- [Mastodon de Clare Sudbery][ms]
- [Le livre Refactoring][rf], de Martin Fowler.
- [Le site de GeePaw Hill][gp]

[ws]: https://medium.com/a-woman-in-technology
[ms]: https://mastodon.social/@claresudbery
[rf]: https://martinfowler.com/books/refactoring.html
[gp]: https://www.geepawhill.org/
