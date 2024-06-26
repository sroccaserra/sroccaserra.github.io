-- title: NewCrafts Paris 2023 ~ Dave Farley et Emily Bache
-- date: 2023-05-28

Les 25 et 26 mai, j'ai assisté à la conférence NewCrafts Paris 2023. C'était
chouette de revoir plein de monde au même endroit ! Il y avait aussi des
interventions de qualité, voilà une partie de mes notes sur ce que j'ai appris
ou révisé.

- <https://ncrafts.io/>

Ce sont des notes très partielles, à mon usage personnel. Je vous invite à voir
les vidéos des conférences qui vous intéressent quand elles seront publiées (le
mois prochain normalement).

Dans ce premier article, mes notes sur les présentations de Dave Farley et
Emily Bache.

Dans les suivants, j'ai prévu de partager mes notes sur les interventions
de&nbsp;:

- [Laurent Bossavit][lb]
- [Clare Sudbery][cs]
- Jessica Kerr
- Kent Beck

[lb]: /pages/2023-05-29_NewCrafts_Paris_2023_~_Laurent_Bossavit.html
[cs]: /pages/2023-06-08_NewCrafts_Paris_2023_~_Clare_Sudbery.html

## Dave Farley

Dave Farley est co-auteur du livre Continuous Delivery, auteur du livre
Modern Software Engineering, et a travaillé sur des projets comme le LMAX
Disruptor.

Voici quelques notes sur sa keynote, qui a ouvert l'édition 2023 de NewCrafts
Paris.

Dans le domaine du logiciel, Dave observe souvent une confusion entre
ingénierie et fabrication. Mais pour lui, la fabrication n'est jamais un
problème dans le logiciel. Pour lui, dans l'ingénierie comme dans le
développement logiciel, le sujet est toujours l'exploration et la découverte.
Il propose donc d'optimiser pour l'apprentissage.

> Optimize for learning.

Dave propose également de faire des choix qui favorisent la modularité&nbsp;:

> Whenever you have a choice, prefer the choice that improve modularity,
> cohesion, separation of concerns, abstraction. If you have no good idea,
> gather a bunch of stupid ideas and find cheap ways to try some of them and
> learn more on the way.

On retrouvera une discussion sur couplage et cohésion dans l'intervention de
Kent Beck à la fin de la conférence.

Note&nbsp;: cet écart entre ingénierie logiciel et fabrication rejoint l'avis
de Jack Reeves dans son article "What is Software Design" de 1992.

### Liens

- [La chaîne Youtube de Dave Farley][cd]
- [Le livre Continuous Delivery][cdb]
- [Le livre Modern Software Engineering][mse]
- [Le projet LMAX Disruptor][lmd]
- [What is Software Design][wisd] ~ article de Jack Reeves, 1992

[cd]: https://www.youtube.com/c/ContinuousDelivery
[cdb]: https://martinfowler.com/books/continuousDelivery.html
[mse]: https://www.davefarley.net/?p=352
[lmd]: https://lmax-exchange.github.io/disruptor/
[wisd]: http://www.bleading-edge.com/Publications/C++Journal/Cpjour2.htm

## Emily Bache

Emily Bache est autrice des livres The Coding Dojo Handbook et Technical Agile
Coaching with the Samman Method. Elle a également publié de nombreux katas de
refactoring sur sa page GitHub.

Pour NewCrafts 2023, Emily Bache a animé un atelier de refactoring. Dans cet
atelier, elle a présenté deux techniques simples de refactoring sur du code
legacy : Peel & Slice.

Je vous invite à explorer les liens ci-dessous pour en savoir plus sur ces deux techniques.

L'idée de Peel est d'extraire dans une fonction le code testable qui est pris
entre deux tranches de code non testable. Ça permet de tester la nouvelle
fonction. Le nom Peel vient de l'image d'enlever la peau non testable d'une
banane.

L'idée de Slice est que dans du code testable, il y a un noyau non testable.
Dans ce cas, on peut extraire le code non testable dans une variable qui est
une fonction. Si on peut déplacer cette déclaration de variable / fonction en
haut de la méthode, on peut maintenant appliquer Peel, sans casser l'interface
publique. Et là on peut tester la méthode comme ci-dessus. Le nom de Slice
vient de l'idée de couper une cerise pour en enlever le noyau.

Avantages :

- Permet de caractériser du code legacy.
- Deux techniques très simples et qui se combinent.
- Slice : range les parties testables ensemble.

Inconvénients :

- Comme souvent dans du refactoring, les deux techniques dégradent un peu le.
  design (temporairement, c’est le pari) ~ il y a plus de méthodes package.
  accessibles, possibilité de conflits de noms similaires sur peel.
- Peel : il reste un peu de code pas couvert, qui peut être bien géré par un
  test de plus haut niveau (intégration, bout en bout).


Ces techniques ne sont pas nouvelles, mais j'ai trouvé très intéressant
l'aspect pédagogique et la façon de les présenter ensemble, avec l'image de la
banane et des cerises.

### Lien

- [Présentation d'Emily Bache sur le site Samman Coaching][sc]
- [Le livre Coding Dojo Handbook][cdh]
- [Le livre Technical Agile Coaching with the Samman method][scb]
- <https://github.com/emilybache> ~ La page GitHub d'Emily Bache, avec plein d'exercices de refactoring
- [Vidéo de Llewellyn Falco][ll] présentant Peel & Slice
- [Un très bon article][nc] de Nicolas Carlo présentant Peel & Slice

[sc]: https://sammancoaching.org/society/contributors/emilybache.html
[cdh]: https://leanpub.com/codingdojohandbook
[scb]: https://leanpub.com/techagilecoach
[nc]: https://understandlegacycode.com/blog/another-way-of-refactoring-untested-code/
[ll]: https://www.youtube.com/watch?v=sXqRWXWiXYo

## À Suivre...

C'est tout pour ce premier article. Comme indiqué en introduction, je prévois
de publier quelques autres notes sur cette conférence NewCrafts 2023. À
suivre :)
