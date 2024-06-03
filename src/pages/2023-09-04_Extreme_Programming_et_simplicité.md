-- title: Extreme Programming et simplicité
-- date: 2023-09-04

Cet été j'ai relu quelques chapitres du livre Extreme Programming Explained, de Kent Beck, et j'ai discuté avec des collègues de la notion de simplicité, et de pourquoi c'est difficile à définir.

Ça m'a donné envie de croiser les deux sujets, ce que je propose dans cet article.

## Simplicité et Extreme Programming

Pour commencer, la simplicité est explicitement au cœur d'Extreme Programming (XP).

Notamment, on entent souvent citer l'expression YAGNI (You Aren't Gonna Need It), mais il y a aussi les deux principes _Small Release_ et _Simple Design_.

> - Small releases—Put a simple system into production quickly, then release new versions on a very short cycle.
> - Simple
 design—The system should be designed as simply as possible at any given
 moment. Extra complexity is removed as soon as it is discovered.

Et les _Four Rules of Simple Design_, toujours au cœur d'XP :

> - Passes the tests
> - Reveals intention
> - No duplication
> - Fewest elements

C'est un peu comme le jeu de Go, les règles sont simples mais on va pouvoir apprendre à les maîtriser tout au long de sa carrière.

## Simplicité et Agilité

Il y a ça aussi au cœur de l'agilité, dont deux des trois principes essentiels (\*) sont pour moi&nbsp;:

> - React to the unexpected by gathering feedback (not by thinking "better" up front)
> - When reality stops matching the plan, change the plan (instead of pushing the plan harder)

Quand on a ces deux principes en tête, on est encouragé à avoir un plan modérément compliqué, voire le moins possible. Car on sait qu'on va avoir de l'inattendu et qu'on vas avoir à adapter notre plan face à la réalité.

Il y a aussi une expression qui est présente depuis longtemps dans les communautés Agiles et XP, c'est :

> Do the simplest thing that could possibly work.

Je note que ce n'est pas une règle absolue mais une heuristique, et que la forme complète est plutôt :

> If you're not sure what to do yet, do the simplest thing that could possibly work.

À travers cette heuristique, on retrouve une notion importante en agilité : se donner la capacité de retarder une décision jusqu'au moment où on a assez d'info pour la prendre (mais pas plus tard). Ça demande pas mal de compétences tech pour pouvoir faire ça, comme pour "faire simple" d'ailleurs. Quand c'est nécessaire, en attendant plus d'info / de feedback (qu'on va activement chercher), on fait la chose la plus simple qui fonctionne.

En passant, même quand on a ces heuristiques, on va avoir du travail pour définir ensemble "le moment où on on a assez d'info pour prendre une décision". Par exemple il arrive qu'un enjeu politique s'invite à la discussion, et on met un Kafka en day 0 parce-que telle personne ayant le dernier mot l'a décidé en chambre 🤷

Quand on a ces deux principes en tête, on est encouragé à avoir un plan modérément compliqué, voire le moins possible. Car on sait qu'on va avoir de l'inattendu et qu'on vas avoir à adapter notre plan face à la réalité.

(\*)&nbsp;: Formulations piquées à J. B. Rainsberger, les trois qu'il propose :

> - React to the unexpected by gathering feedback (not by thinking "better" up front)
> - Treat people as people (not as fungible cogs)
> - When reality stops matching the plan, change the plan (instead of pushing the plan harder)

## Simplicité, tu emploies toujours ce mot…

> — C’est inconcevable !<br/>
> — Tu emploies toujours ce mot. Je ne sais pas s'il veut dire ce que tu penses.

(Vizzini et Inigo Montoya, Princess Bride.)

Attention cependant, car la simplicité ou la complexité, c’est très difficile à définir.

Pour donner un exemple du travail de définition qu’on peut faire, dans la communauté DDD on s’intéresse à la question "La complexité : laquelle” ? On trouve des outils pour séparer ce qui est quantifiable et ce qui ne l'est pas, et des outils pour séparer complexité accidentelle de complexité essentielle de complexité structurelle. La communauté DDD s’intéresse aussi beaucoup au rôle du couplage dans tout ça, et au rôle du contexte (\*\*).

Complexité, laquelle, mais aussi complexité "pour qui" ? Il y a également des enjeux de pouvoir.

Autre exemple, on connaît déjà ces problèmes de définition et de quantification quand on s'intéresse à la "qualité". Je n'ai pas encore trouvé de meilleure définition de la qualité que celle de Jerry Weinberg :

> De la valeur pour quelqu'un à un moment donné.

Bref, comme évoqué plus haut, on va avoir du travail pour définir ce qu’on veut réussir ensemble.

(\*\*)&nbsp;: Ce sont des points communs avec la communauté Extreme Programming, qui y apporte des réponses légèrement différentes —mais qui peuvent être compatibles— dans ce que je peux observer, mais c’est un autre sujet.

## La simplicité, c’est pas simple

Ce genre de notions (simplicité, qualité, ...) est difficile à appréhender donc. Ça m’évoque au moins les trois points communs ci-dessous.

A) Étant difficiles à définir, ces notions ne permettent pas de se contenter de suivre des règles ou des recettes. On va préférer se tourner vers des heuristiques et des systèmes auto régulés (inspect & adapt ?).

B) En général avec ces notions il est facile de trouver des réponses apparemment évidentes et séduisantes mais malheureusement fausses de manière subtile. Il va falloir affiner régulièrement notre compréhension (cf. système auto-régulé).

C) Ces notions créent une asymétrie de l'information entre expert·es et client·es qui favorise les mauvaises prestations, cf. market for lemons :(

Ce sont des choses que mes collègues et moi travaillons depuis longtemps heureusement, mais c'est sûr, la simplicité... c'est pas simple.

## Liens

- [Extreme Programing Explained][xpe]
- [L'eXtreme Programming][lxp]
- [You Aren't Gonna Need It (YAGNI)][yagni]
- [Beck Design Rules][bdr]
- [The Four Elements of Simple Design][fesd]
- [J. B. Rainsberger on "Agile rules"][jbr]
- Do the simplest thing that could possibly work
    - <http://wiki.c2.com/?DoTheSimplestThingThatCouldPossiblyWork>
    - <https://www.artima.com/articles/the-simplest-thing-that-could-possibly-work#part3>
- [The Market for "Lemons"][mfl]

[xpe]: https://www.goodreads.com/book/show/67833.Extreme_Programming_Explained
[lxp]: https://www.editions-eyrolles.com/Archive/9782212110517/l-extreme-programming
[yagni]: https://wiki.c2.com/?YouArentGonnaNeedIt
[bdr]: https://martinfowler.com/bliki/BeckDesignRules.html
[fesd]: https://blog.jbrains.ca/permalink/the-four-elements-of-simple-design
[jbr]: https://www.linkedin.com/feed/update/activity:6959914647567134721
[mfl]: https://fr.wikipedia.org/wiki/The_Market_for_%E2%80%9CLemons%E2%80%9D
