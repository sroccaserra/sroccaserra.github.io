-- title: Cycle de vie et abstraction
-- date: 2024-02-13

Je refais un peu de C++ en feuilletant la troisième édition de "A Tour of C++",
et j'aime bien. C'est amusant, car j'ai fait beaucoup de C++ en début de
carrière et j'en avais gardé un souvenir peu ému, je me souvenais surtout des
footguns. Il a même dû m'arriver d'en dire du mal quand j'en avais l'occasion.
Aujourd'hui, je suis à nouveau intéressé par ce que j'ai appris grâce à ce
langage. J'ai l'impression que mes opinions suivent des phases.

Dans les choses que j'ai apprises, je suis content d'en avoir fait
suffisamment à l'époque pour éviter les `new` et avoir en tête RAII, ça
semble encore pertinent en C++ moderne.

Je note aussi que le principe RAII (Resource Acquisition Is
Initialization) m'a donné le goût de la symétrie dans le cycle de vie.
J'apprécie que la création d'un objet et sa destruction / sortie de
scope, ou que les ouvertures et fermetures de ressources aient lieu au
même niveau d'abstraction, et si possible dans des positions symétriques.

Je repense souvent à ce principe, même dans des langages où on ne gère
pas explicitement la mémoire. Pour essayer de le décrire, souvent il y a
des traitements qui peuvent bien se modéliser en poupées gigognes de&nbsp;:

- "préparation"
- "exécution"
- "conclusion"

La préparation et la conclusion pouvant être symétriques et au même
niveau d'abstraction. Et la phase exécution pouvant être une descente
dans le niveau d'abstraction qui à son tour peut se modéliser comme une
"préparation" / "exécution" / "conclusion" (avec des tortues jusqu'en
bas).


J'apprécie ce genre de mini patterns, ça m'aide souvent à structurer ma
pensée. Je le perçois comme du "micro-design" (nom inspiré des
"microtests", un nom que je préfère à Unit Test). Un autre exemple connu
auquel je pense aussi comme du "micro-design" est les Four Elements of
Simple Design (voir liens ci-dessous).

Autre exemple : en plissant les yeux on peut voir le pattern Functional Core,
Imperative Shell comme un pattern "préparation" / "exécution" (fonctionnelle
pure) / "conclusion".

🧵&nbsp;[@sroccaserra](https://mastodon.social/@sroccaserra/111924533437429454)

## Liens

- <https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization>
- <https://www.stroustrup.com/tour3.html>
- <https://en.wikipedia.org/wiki/Turtles_all_the_way_down>
- <http://anarchycreek.com/2009/05/20/theyre-called-microtests/>
- <https://blog.jbrains.ca/permalink/the-four-elements-of-simple-design>
- <https://www.destroyallsoftware.com/screencasts/catalog/functional-core-imperative-shell>
