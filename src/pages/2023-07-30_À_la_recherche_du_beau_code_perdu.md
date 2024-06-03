-- title: À la recherche du beau code perdu
-- date: 2023-07-30

Ça fait plusieurs fois que dans des conversations Web je pose ou que je vois poser la question :

> Avez-vous des exemples disponibles en open source d'une appli qui ne serait pas un hello world ou un kata qui vous parait intéressante comme modèle? (idéalement dans un langage relativement courant comme java/python/js/C# ou ce genre de truc)

## Proposition de beau code

Un exemple de réponse que j'ai vu donner ou que j'ai donné est :

> Les libs standard de Java.

Et cette réponse commence à révéler la difficulté de la question, ou plutôt la difficulté de répondre.

Par exemple, on pourrait argumenter que la lib Java n'est pas partout exemplaire, que par endroits on dirait du C car on y trouve beaucoup de `if (x == null)`, alors que la même lib standard propose un type `Optional`.

Exemple de la classe `LinkedList`, où on trouve beaucoup de `if (x == null)` :

<pre>
    void linkBefore(E e, Node<E> succ) {
        final Node<E> pred = succ.prev;
        final Node<E> newNode = new Node<>(pred, e, succ);
        succ.prev = newNode;
        <b>if (pred == null)</b>
            first = newNode;
        else
            pred.next = newNode;
        size++;
        modCount++;
    }
</pre>


On pourrait proposer des éléments de réponse à cette objection. Par exemple, je pense que les libs standard Java c'est très vaste, et qu'il y a des parties comme la classe `LinkedList` (date de Java 1.2) qui restent intéressantes si on les lit en contexte (temporel et d'implémentation et d'usage).

Dans ce contexte (du code d'implémentation de lib standard utilisée par des millions de personnes), les `if (prev == null) first = next;` me semblent un meilleur choix d'implémentation qu'un `Optional`. On dirait du C, mais c'est une implémentation de linked list assez standard, donc je trouve que ça va dans le sens du bois dans ce contexte.

Ce que je trouve intéressant également sur ce point, c'est que l'interface de la classe pour l'utilisateur expose assez peu de valeurs null (les fonctions pour peek et poll si j'ai bien lu). Donc on peut faire l'hypothèse que ces null sont un détail d'implémentation qui ne sont pas imposés aux clients de la classe, ça me va dans ce cas.

Le choix de ne pas introduire `Optional` s'explique aussi par l'intention de rétro compatibilité. Une interface publique (au sens API) a valeur de contrat, donc conserver les `null` dans l'API permet de ne pas casser le code existant. À ce propos, j'ai trouvé que l'introduction de l'interface `Stream` en Java 8 résolvait de façon élégante le problème d'introduire des patterns inspirés de la programmation fonctionnelle sans casser les contrats existants.

Donc j'apprécie la lib standard Java, et surtout son interface publique (par opposition à son implémentation), car c'est la première fois que j'ai vu un design objet en vrai pendant mes études. Sans parler de la lib standard Smalltalk bien plus tard.

Mais ça me fait penser que cette proposition de beau code n'est pas universelle, et comme on l'a vu je remarque qu'elle s'accompagne souvent d'une conversation, qui est souvent intéressante d'ailleurs et qui montre que la question mérite d'être posée.

## Difficulté de trouver des réponses

Trouver une réponse est difficile. Je n'ai pas souvenir d'avoir vu beaucoup de réponses à cette question, on dirait la question à un million de dollars. Est-ce que le beau code est si rare ?

### Plusieurs sortes de beautés

Moi même je n'ai pas souvenir d'avoir lu du code et de me dire "ça y est ! le voilà ! c'est à n'en pas douter du beau code !" J'ai l'impression de toujours avoir quelque-chose à redire sur du code que je lis (sans parler du code que j'écris). Avoir quelque-chose à redire, ou mieux quand j'y arrive, voir les tradeoffs, ce que le code a dû abandonner en "beauté X" pour gagner en "beauté Y".

Exemples de beautés parfois incompatibles :

- Expressivité
- Concision
- Uniformité
- Familiarité
- Simplicité
- Élégance
- Extensibilité
- Évolutivité
- Cohésion
- Découplage
- Performance
- Sécurité
- Adaptation au problème à résoudre
- Découvrabilité
- Conformité à un pattern
- Conformité à un standard
- ...

### Les murs bougent...

Il y a peut-être aussi l'idée que dans la pratique du terrain, tout code commence souvent par être "beau", au moins au yeux de celui qui l'a écrit. Mais autour de ce beau code, tout change, les besoins, la quantité de fonctionnalités du logiciel, les membres de l'équipe, les contraintes technologiques, les contraintes de performances, etc.

Et peu à peu, soit le code initialement beau est devenu compliqué et moche, soit il n'a pas changé mais dans ce nouveau contexte il n'est plus adapté, il est devenu moche.

### Souvent des réponses d'outils

Une autre difficulté est que souvent, les réponses données sont des outils abstraits et génériques, comme la lib standard Java.  D'autres réponses sont des extraits de code venant de livres. Cependant je trouve que c'est déjà beaucoup et que ce sont des réponses valides.

Un bon exemple de ça, c'est le livre "Smalltalk Best Practice Patterns" de Kent Beck, ou son petit frère Java "Implementation Patterns" : il y a plein de patterns assez simples, et c'est des petits bouts de code pris dans un bouquins, mais accompagnés de discussions sur les tradeoffs et le contexte. C'est des patterns tellement simples que j'ai parfois du mal à le lire, mais chaque fois que je fais l'effort de le faire je suis content, car soit j'apprends un détail intéressant, soit je me souviens de ce que je sais implicitement et que c'est important de l'expliciter à d'autres.

Mais personnellement, je serais très intéressé par trouver du code exemplaire qui soit du code applicatif, le code des libs standards ou des livres ne donne pas ça. J'avais posé la question à Michael Feathers dans une formation, et il m'a répondu : "Ah, je ne sais pas, le code de Junit4 ?". Encore un outil, je cherche toujours du "beau" code applicatif public.

### Difficulté de trouver du beau code applicatif

Un des problème d'avoir une réponse sur quelque-chose de plus gros est que ça dépend beaucoup du contexte, et de la personne qui va le lire.

Par exemple si je réponds que le plus beau code de gros applicatif que j'ai pris le temps de parcourir, c'est le code de Quake III, hors contexte ça risque de ne pas intéresser ni convaincre beaucoup de monde.

C'est 300k+ lignes de C des années 90 😨, et il faut être pas mal accompagné (ou faire beaucoup de devoirs du soir) pour commencer à y voir clair : ce n'est pas facilement "découvrable". D'expérience, ce n'est pas la tasse de thé de tout le monde, il faut y avoir un intérêt particulier pour y passer le temps nécessaire.

Mais une fois qu'on s'est mis dans le contexte, alors ça peut devenir intéressant et "beau". Un code produit par une petite équipe qui a fait plusieurs fois le même jeu pendant 7 ans (Wolfenstein 3D, Doom, Doom II, Quake, Quake II) et qui a appris de ses erreurs et raffiné ses compétences au fil de l'eau pour finalement se déclarer satisfait de Quake III, moi ça m'émeut un peu.

Donc je pense qu'en plus du pb de la disponibilité du code (beaucoup de code reste privé), il y a aussi ce problème qu'il y a parfois un gros prix d'entrée même pour du code beau et gros, et qu'il faut que ça corresponde à un intérêt de la personne qui va le lire pour justifier l'investissement du ticket d'entrée.

## Conclusion

Je suis toujours à la recherche de beau code, pour une définition assez large de "beau". Que ce soit des petits extraits, des librairies, ou plus difficile à trouver, du code applicatif, j'apprécie de découvrir de nouvelles choses, et d'avoir des conversations sur des exemples concrets.

Et peut-être qu'un des moyens d'avoir plus de réponse à cette question serait d'accepter de proposer du code qui ne soit pas parfait, mais qui soit beau au moins pour une raison, et au moins pour vous, et d'avoir de la curiosité et des conversations autour de ce code.

- "Pourquoi tu le trouves beau ?"
- "Quelle genre de beauté ?"
- "Dans quel contexte ?"
- ...

## Liens

Exemple de code ci-dessus tiré de&nbsp;:

- <https://github.com/AdoptOpenJDK/openjdk-jdk11/blob/master/src/java.base/share/classes/java/util/LinkedList.java>

Si le code de Quake III vous intéresse, pour gagner un peu de temps&nbsp;:

- <https://fabiensanglard.net/quake3/>
