-- title: Interface ou classe ? Exemple de micro design
-- date: 2023-09-06

Aujourd'hui j'ai feuilleté Implementation Patterns de Kent Beck, et ça m'a remis en mémoire quelques détails utiles, comme à chaque fois.

Par exemple : un vieil adage est de coder vers les interfaces, pas vers les implémentations. Interface au sens "un ensemble d'opérations sans implémentations". Comment est-ce qu'on implémente cette idée ? S'il y a plusieurs façons, quels en sont les compromis ?

## Design et compromis

En Java, il y a au moins deux façons de représenter cette "interface - ensemble d'opérations". On peut soit définir cet ensemble d'opérations dans une classe de base qui n'a pas vocation à être implémentée, soit les définir dans... une `interface`, puisque Java a introduit cette notion dès la v1. Pourquoi est-ce qu'on aurait envie d'utiliser une façon plutôt que l'autre ? Je trouve que c'est ce genre de question qui peuvent nous freiner dans le design au quotidien.

Le livre donne une réponse intéressante je trouve, il rend visibles les conséquences de choisir l'une ou l'autre, ce qui permet de prendre une décision en connaissance de cause.

L'interface permet de laisser disponible la place de l'héritage, puisqu'en Java il n'y a pas d'héritage multiple, et avec une classe de base je pose une contrainte forte sur la hiérarchie des implémentations.

Mais la classe de base permet quelque-chose de très intéressant aussi : de la souplesse face à un changement d'interface. En effet, si je modifie une interface --au sens Java-- qui est très utilisée (changement de signature d'une méthode par exemple), alors je dois aussi changer toutes les implémentations concrètes. Avec une classe de base, j'ai la possibilité de conserver l'ancienne signature, et de fournir une implémentation par défaut de la nouvelle signature qui appelle l'ancienne => pas besoin de changer toutes les implémentations.

Je note aussi que depuis Java 8 (le livre date d'avant), une interface a la possibilité de fournir une implémentation par défaut. Avec le caveat qu'elle n'aura pas accès aux variables membres puisqu'une interface n'a pas de variables membres. Mais pour une redirection vers une méthode, ça devrait le faire dans la grande majorité des cas. Best of both world?

## Ralentir le "durcissement" du "software"

En tout cas j'ai trouvé très intéressant d'avoir ce genre de réflexions de micro design. Je trouve que quand on a l'habitude de faire cet exercice on prend de meilleurs décisions plus rapidement. Et comme on l'a vu dans l'exemple, ça permet de faire des choix qui baissent le coût du changement, ce qui est essentiel si on veut que le "software" reste "soft" le plus longtemps possible, et ne se durcisse pas comme une pierre avec le temps.

## Liens

- <https://www.goodreads.com/book/show/781559.Implementation_Patterns>
