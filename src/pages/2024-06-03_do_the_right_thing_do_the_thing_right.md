-- title: Do the right thing, do the thing right = ??
-- date: 2024-06-03

Dans une discussion avec des collègues, on a abordé un dicton qu'on lit ou
qu'on entend souvent :

> Do the right thing, do the thing right.

On a discuté sur les sens possibles de ce dicton, et quelqu'un se demandait si
il n'invitait pas à commencer par faire quelque-chose qui fonctionne, sans se
soucier de comment c'est fait, et s'inquiétait même d'une possible invitation à
faire vite et mal, en reportant le fait de rendre le code maintenable à "un
jour quand on aura le temps".

On a aussi évoqué le parallèle avec une pratique comme TDD (Test-Driven
Development), qui nous invite à suivre un cycle "red > green > refactor".

Et c'est proche d'un autre dicton, qu'on retrouve dans les mondes Unix et
Extreme Programming :

> Make it work, make it right, make it fast.


Voilà ce que ce dicton, "do the right thing, do the thing right" évoque pour
moi en général, et que j'ai pris le temps de noter à cette occasion.

En effet, si on observe beaucoup de projets où on n'a pas le temps de penser à
"do the thing right", on peut se demander si ce dicton est une bonne chose, et
s'inquiéter que si on s'arrête au milieu du gué, on ne prendra pas le temps de
faire "the thing right".

Cependant, pour moi ce dicton n'invite pas du tout à faire vite et mal, et je
pense qu'il n'est pas du tout suivi sur les projets qui perdent le contrôle de
leur base de code.

La première chose à laquelle j'ai pensé, c'est que "do the right thing, do the
thing right" ne dit rien sur la vitesse. Donc ce n'est pas forcément "le plus
vite possible". On peut tout à fait imaginer que justement, on va prendre le
temps de s'intéresser à "comment la saucisse est faite".

On trouve un parallèle avec une pratique comme TDD. Quand on choisit de faire
du TDD, on va effectivement commencer par écire ("red") puis faire passer
("green") un test qui vérifie qu'on fait la bonne chose, et on le fait passer
le plus simplement possible, même si c'est objectivement fait n'importe
comment. Et donc ça va vite, parce-qu'en plus le test couvre une toute partie
de la fonctionnalité. On parle même de micro test et j'aime bien cette
expression. Et ensuite on commence à réfléchir, une fois que le test passe, sur
toutes les façons dont on pourrait améliorer notre implémentation ("refactor").
Et on l'améliore dans la foulée.

Comme c'est un micro test, tout ça ne prend que quelques minutes à quelques
dizaines de minutes max. Donc à la fin de la journée, on n'est pas censé avoir
du code moche, puisqu'on l'améliore au fil de l'eau. Le cycle "right thing"
"thing right" est très très rapide, donc on n'est pas censé retarder "thing
right".

En agilité on suit la même idée, d'où l'importance du feedback très rapide. Et
c'est souvent là que ça pèche en premier d'expérience. Quand on commence à
allonger le feedback, on perd l'agilité.

L'image que j'aime bien pour faire ressentir cette idée, c'est qu'on préfère
gérer nos projets comme une cuisine que comme un garage.

Quand on fait un peu de cuisine, on se rend compte tout de suite que si on
accumule les ustensiles pas lavés et pas rangés, ça ne va pas le faire. Donc on
alterne tâches / lavage / rangement. Pendant qu'on fait revenir les oignons, on
lave la planche à découper, etc. Tout est entremêlé, mais c'est ce qui nous
permet de continuer à travailler, on veut en permanence avoir un plan de
travail utilisable.

Par contre, le garage, bon, on y met les raquettes de tennis, la petite table
basse qu'on n'utilise plus, les jeux de société qui ne servent plus, le tapis
du grand père, tout s'accumule. Et une fois par an si on a le courage, on se
dit "allez, aujourd'hui je range le garage". Et ça nous prend des heures, voir
plusieurs jours, et on n'aime pas ça. 

Donc "do the right thing, do the thing right" et autres, ça marche bien si on
le fait dans une cuisine, avec alternance rapide. Et ça commence à coincer
quand on accumule les améliorations à faire plus tard, on se retrouve avec le
garage à ranger.

Pour revenir à la vitesse, on peut développer très lentement avec un rythme de
feedback très rapide. C'est en général le "rythme du feedback" que je préfère
accélérer, pas le "rythme de développement". On pourrait imaginer que si on
accélère le feedback, le rythme de dev sera aussi amélioré. Probablement, mais
c'est un effet secondaire pour moi, et surtout je ne sais pas le mesurer. Ce
qui est plus probable et souhaitable, c'est qu'en améliorant le feedback, on
évitera de faire tellement de choses inutiles qu'il sera évident qu'on a choisi
le bon chemin. Parfois c'est difficile à voir cependant, car comme sur nos
projets on veut toujours aller plus vite que la musique (mon interprétation),
on se sent toujours en retard quoi qu'on fasse (mon ressenti).

En tout cas, alterner "do the right thing" et "do the thing right" à un bon
rythme est la meilleure façon de développer du logiciel que je connaisse, et
c'est ma préférence.

## Liens

- <http://wiki.c2.com/?MakeItWorkMakeItRightMakeItFast>
