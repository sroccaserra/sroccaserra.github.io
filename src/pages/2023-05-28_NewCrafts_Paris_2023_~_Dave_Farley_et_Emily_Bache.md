Les 25 et 26 mai, j'ai assisté à la conférence NewCrafts Paris 2023. C'était
chouette de revoir plein de monde au même endroit ! Il y avait aussi des
interventions de qualité, voilà une partie de mes notes sur ce que j'ai appris
ou révisé.

- <https://ncrafts.io/>

Ce sont des notes très partielles, à mon usage personnel. Je vous invite à voir
les vidéos des conférences qui vous intéressent quand elles seront publiées (le
mois prochain normallement).

Dans ce premier article, mes notes sur les présentations de Dave Farley et
Emily Bache.

Dans les suivants, j'ai prévu de partager mes notes sur les interventions de :

- Laurent Bossavit
- Clare Sudbery
- Jessica Kerr
- Kent Beck


## Dave Farley

Dans le domaine du logiciel, Dave observe souvent une confusion entre
ingénierie et fabrication. Mais pour lui, la fabrication n'est jamais un
problème dans le logiciel. Pour lui, dans l'ingénierie comme dans le
développement logiciel, le sujet est toujours l'exploration et la découverte.
Il propose donc d'optimiser pour l'apprentissage.

Note : cet écart entre ingénierie logiciel et fabrication rejoint l'avis de
Jack Reeves dans son article "What is Software Design" de 1992.

> Optimize for learning.

Dave propose également de faire des choix qui favorise la modularité :

> Whenever you have a choice, prefer the choice that improve modularity,
> cohesion, separation of concerns, abstraction. If you have no good idea,
> gather a bunch of stupid ideas and find cheap ways to try some of them and
> learn more on the way.

On retrouvera cette idée dans l'intervention de Kent Beck à la fin de la conférence.

### Liens

- [La chaîne Youtube de Dave Farley][cd]
- [What is Software Design][wisd] ~ article de Jack Reeves, 1992

[cd]: https://www.youtube.com/c/ContinuousDelivery
[wisd]: http://www.bleading-edge.com/Publications/C++Journal/Cpjour2.htm

## Emily Bache

Emily Bache a animé un atelier de refactoring. Dans cet atelier, elle a présenté deux techniques simples de refactoring sur du code legacy : Peel & Slice.

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
- <https://github.com/emilybache> ~ La page GitHub d'Emily Bache, avec plein d'exercices de refactoring
- [Vidéo de Llewellyn Falco][ll] présentant Peel & Slice
- [Un très bon article][nc] de Nicolas Carlo présentant Peel & Slice

[sc]: https://sammancoaching.org/society/contributors/emilybache.html
[nc]: https://understandlegacycode.com/blog/another-way-of-refactoring-untested-code/
[ll]: https://www.youtube.com/watch?v=sXqRWXWiXYo

