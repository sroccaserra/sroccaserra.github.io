Je refais un peu de C++ en feuilletant la troisième édition de "A Tour of
C++", et j'aime bien. C'est amusant, car j'ai fait beaucoup de C++ en
début de carrière, avant de passer à Java, JS, Python et Lua au bout de
quelques années. Depuis, j'avais gardé un souvenir peu ému de C++, me
souvenant surtout des footguns. Il a même dû m'arriver d'en dire du mal
quand j'en avais l'occasion. Aujourd'hui, je suis à nouveau intéressé par
ce que j'ai appris grâce à ce langage. J'ai l'impression que mes opinions
suivent des phases.

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
- "bouclage"

La préparation et le bouclage pouvant être symétriques et au même niveau
d'abstraction. Et la phase exécution pouvant être une descente dans le
niveau d'abstraction qui à son tour peut se modéliser comme une
"préparation" / "exécution" / "bouclage" (avec des tortues jusqu'en bas).

🧵&nbsp;[@sroccaserra](https://mastodon.social/@sroccaserra/111924533437429454)

## Liens

- <https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization>
- <https://www.stroustrup.com/tour3.html>
- <https://en.wikipedia.org/wiki/Turtles_all_the_way_down>
