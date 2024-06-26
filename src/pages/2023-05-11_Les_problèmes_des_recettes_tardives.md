-- title: Les problèmes des recettes tardives
-- date: 2023-05-11

Disclaimer: well, that’s just, like, my opinion, man.

Pourquoi on s’est mis à utiliser des méthodes agiles autour de l’an 2000 ?
Parce-que des dysfonctionnements systémiques étaient la norme, quasiment
systématiquement, et un peu les mêmes partout. C’est pour répondre à ces
dysfonctionnements qui étaient devenus des normes qu’on a changé de façon de
penser et de travailler. (By the way, autre opinion gratuite en passant, c’est
que “on” = “un faible pourcentage d’équipes”, même aujourd’hui, mais c’est un
autre sujet.)

C’est utile je trouve de connaître ces dysfonctionnements de systèmes, afin de
les reconnaître et de les éviter. En effet, j’ai pu observer plusieurs fois que
“appliquer” une “méthode” (agile ou pas) comme on suivrait une recette n’est
pas la chose qui apporte des résultats, ce qui apporte des résultats c’est
l’intention qu’on y met. Donc appliquer une méthode sans chercher à éviter les
dysfonctionnement qu’elle est censé éviter c’est passer à côté du problème (cf
les équipes qui deviennent “agiles” en calquant les mots “qui vont bien”
—sprint, PO, user story, roadmap, etc. — sur un process dysfonctionnel sans
trop changer ledit process ou sans s’attaquer aux dysfonctionnements).

Du coup, je réfléchis à mettre par écrit des exemples de dysfonctionnements
pour m’aider à expliquer au client / à la cliente pourquoi je lui demande de
travailler d’une certaine façon, et pourquoi c’est important pour lui ou pour
elle et pour les personnes qui vont utiliser le produit qu’on est en train de
développer ensemble.

Le dysfonctionnement du jour : la “recette tardive”. En quoi c’est un problème
?

Ce que j’appelle “la recette tardive”, c’est quand dans un process de
développement logiciel :

- il y a une étape “finale” qui “valide” qu’une tâche / un ticket / une story /
  un PBI (Scrumspeak pour Product Backlog Item) est “terminé”
- au lieu de recetter ces items au fil de l’eau (on dev → on recette le plus
  vite possible → terminé, etc.), on choisit de (ou donne notre accord pour) le
  faire plus tard, souvent parce-que “on n’a pas le temps maintenant”
- ces recettes non faites s’accumulent pendant plusieurs jours / semaines
- voilà, on a une “recette tardive”.

Autre mécanisme de recette tardive observé :

- “on a bien X et Y mais il manque encore Z, je ferai la recette quand il y
  aura tout pour être bien sûr”
- parfois, le “quand il y aura tout” = quand “l’application sera terminée”. On
  attend une livraison “finale”, livrée “clé en main” et on fera la “vraie
  recette” là dessus.

Alors, je me demandais pourquoi c’est un problème ? Quand on retarde la recette
à plus tard voire au dernier moment au lieu de recetter au fur et à mesure,
alors on met en risque le produit. J’ai mis ici quelques réflexions par écrit
pour tenter de rendre visible cette mise en risque du produit. J’essaie de
montrer un peu les enchaînements de conséquences que j’ai observées, pas
forcément dans l’ordre, mais au ralentit.

Quand on retarde la recette, alors :

- on détecte tard des défauts qui datent de longtemps
- on perd l’empathie utilisateur : quand ce qu’on fait ne va pas en prod
  rapidement, on perd le contact avec les personnes qui ont besoin du produit
- on accumule le travail en cours
- plein de travail en cours ⇒ plus personne ne sait réellement ce qui reste à
  faire
- le pire c’est qu’on s’habitue à vivre avec un reste à faire flou, des tickets
  qui s’éternisent avant de passer en Done, et des utilisateurs tellement loins
  de nous dans le temps qu’ils ne sont même plus dans nos pensés ⇒ plus rien
  n’est important ⇒ ça ou autre chose, bof : en perdant l’objectif on perd la
  motivation
- en rendant flou le reste à faire, on perd complètement prise sur notre
  capacité à réaliser X en un temps Y
- comme on ne va pas se tourner les pouces en attendant la recette, on se
  dépêche de commencer plein d’autres sujets (~ unpopular opinion : et pourtant
  dans cette situation se tourner les pouces serait en réalité “moins pire”
  pour le résultat final)
- en commençant beaucoup de choses sans les terminer, on a l’impression d’aller
  vite car on est occupé à 100 %
- mais en réalité on ne fait que créer une illusion sur notre capacité à faire
  en nous maintenant dans un sentiment d’urgence sur la mauvaise chose, urgence
  de commencer pour montrer qu’on est sur le pont, au lieu de l’urgence de
  terminer ces sujets qui sont devenus “old news” et moins valorisés
- on s’endort jusqu’au réveil, la fin de l’illusion : quand une date importante
  arrive, on se rend compte qu’on a vécu au dessus de nos moyens
- on détecte les défauts au dernier moment, juste avant l’ouverture de service
  ⇒ ça met le produit en risque et les équipes en stress au plus mauvais
  moment. Gros crunch en mode cowboy (allez les requêtes SQL en prod, on y va
  🤠) avec aucune garantie de résultat.
- en étant occupé à 100 % en permanence, on perd totalement notre capacité à
  gérer l’imprévu (note : la survenue de l’imprévu est paradoxalement la chose
  la plus certaine sur un projet)
- en étant occupé à 100 % en permanence, on rate complètement toutes les
  opportunités d’améliorer quoi que ce soit qui se présentent tous les jours
- en n’ayant pas le temps pour les améliorations, on ralentit notre vitesse de
  x % par mois — Attention ! Mefiat ! Beware ! Cave Canem ! Même un
  ralentissement de 1 % par mois c’est énorme car les intérêts cumulés c’est
  exponentiel 😨
- l’autre fin d’illusion sur notre capacité à faire, c’est quand l’ajout de
  nouvelles fonctionnalités devient si pénible qu’on accepte le big rewrite
  (quelle horreur). Mais si on ne change pas les conditions qui ont conduit à
  cette situation, on ne changera pas le résultat. Without changing the quality
  of the “building”, you can’t really change the quality of the thing built.

Bref, je n’aime pas les recettes tardives.

<img class="center" src="/images/that_s_just_like_your_opinion_man.jpg" width="450" height="340" />
