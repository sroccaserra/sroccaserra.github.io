-- title: Découverte du langage Go
-- date: 2022-07-16

Cette semaine j'ai fait un peu de Go et j'aime bien, voilà ce que j'ai observé en résolvant quelques problèmes d'Advent of Code.

## TL;DR

C'est top d'avoir un langage curly brackets qui soit typé statiquement et qu'on peut lancer en ligne de commande aussi facilement que du JavaScript, c'est pas si fréquent que ça, et c'est ce que je recherchais en ce moment, c'est une belle découverte pour moi.

## Plus de détails

### Un langage typé statiquement

Go est un langage typé statiquement, ce qui fait qu'on a beaucoup de feedback en temps réel sur son code, impossible d'oublier un paramètre dans un appel de fonction ou de passer un paramètre du mauvais type par exemple. Ça va plus loin, car s'il y a une variable déclarée mais non inutilisée, le programme ne compile pas. J'apprécie, ça aide à la rigueur.

<pre>
<b>func</b> solve_01_1(numbers []<b>int</b>) <b>int</b> {
	previous := huge
	result := 0
	<b>for</b> _, n := <b>range</b> numbers {
		<b>if</b> n > previous {
			result += 1
		}
		previous = n
	}
	<b>return</b> result
}
</pre>

Ci-dessus on peut observer la signature de la fonction, `func solve_01_1(numbers []int) int`, qui prend en entrée une liste d'entiers (`[]int`) et qui renvoit un entier (`int`). Du classique.

On peut observer aussi le mécanisme d'inférence de type à la déclaration des variables bien pratique. Les variables `previous` et `result` sont déclarées sans type mais sont bien typées statiquement et vérifiées par le type checker. On n'arrive pas au niveau de Haskell qui peut inférer quasi tous les types d'un programme mais c'est déjà bien.

### Exemple de Generics

Le système de generics a l'air bien, j'ai pu m'en servir assez intuitivement.

<pre>
///
// Declaration

<b>func</b> GetParsedLines[T <b>any</b>](parse <b>func</b>(<b>string</b>) T) []T {
    //...
}

///
// Uses

<b>func</b> GetInputLines() []<b>string</b> {
	<b>return</b> GetParsedLines(Id[string])
}

func GetInputInts() []<b>int</b> {
	return GetParsedLines(ParseInt)
}
</pre>

Ci dessus on peut observer une utilisation des generics, avec la définition d'une fonction `GetParsedLines()` paramétrable, et son utilisation avec deux types différents dans `GetInputLines()` et `GetInputInts()`.

`GetParsedLines()` prend en argument une fonction `parse()`. Cette fonction `parse()` doit prendre en argument une `string` et doit renvoyer une valeur de type `T`, qui peut être n'importe quel type. La fonction `GetParsedLines` déclare qu'elle renvoit une liste de `T`, qui doit être le même type renvoyé par `parse()`.

J'ai trouvé ça facile à découvrir, j'ai quasiment écrit cette fonction à l'instinct en m'aidant des erreurs du compilateur.

On peut imposer des contraintes sur les types paramétriques, comme `comparable` ou `Ordered`, mais je n'en ai pas trouvé beaucoup, et je ne sais pas dans quelle mesure c'est extensible.

### Go en ligne de commande

C'est un langage typé statiquement qu'on peut lancer très facilement en ligne de commande 🎉, une super feature pour moi :) `go run monscript.go` et hop. Ça compense le manque de REPL (il n'y a pas de REPL officiel 😔).

### Un langage raisonnablement petit

Le langage est petit, on peut lire une grosse partie de la doc sans se faire trop mal, j'apprécie beaucoup les petits langages (Scheme, Lua, Smalltalk ❤️). La contrepartie c'est qu'il peut manquer certaines choses dont on a l'habitude.

- Pas de `try` / `catch`, on récupère les erreurs en sortie de fonctions un peu comme en C
- Les collections sont limitées (pas de set ni de tuple par exemple, un peu comme en Lua - mais : on a quand même droit à une heap et une liste doublement chaînée en plus des maps et tableaux dynamiques)
- Pas de `map` / `reduce` / `filter` génériques out of the box. Il y a bien quelques personnes qui tentent de fournir des genres de libs équivalentes à LoDash mais si j'ai bien compris les devs Go préfèrent tout faire à coup de boucles `for` (voir le premier exemple ci-dessus), et pourquoi pas, on assume la simplicité des briques de base et un côté impératif.
- Pas d’héritage (mais du polymorphisme avec les interfaces)

Encore une fois, l’avantage de ces omissions c’est que le langage reste petit, et avec un peu de créativité on s’en sort. Tant que j'ai des tableaux dynamiques, des hashmap et des fonctions du premier ordre je peux travailler en général.

### Autres Features

Le système d'interface est super souple, on dirait du duck typing en langage statique. Je n'ai pas vraiment pu me faire une opinion là dessus, ça a l'air pas mal pour développer de manière opportuniste tout en gardant les avantages du type checker.

Le système d'erreur est bien pensé, ça compense un peu le manque d'exception.

Je n'ai pas utilisé les killer features de concurrence (les goroutines), ça a l'air bien 🤷

Le système de packages / modules m'a un peu mis des bâtons dans les roues, ça s'est mieux passé quand j'ai compris qu'il y avait un seul package par répertoire, et que les fichiers du package se partagent le même namespace pour la compilation. Si j'ai bien compris ça fait qu'on a un namespace par répertoire, que se partagent tous les fichiers du répertoire. Je ne suis pas fan de çe point, j'aime bien quand le scope de chaque fichier est isolé mais je peux vivre avec.

## Docs et outils

Les docs sont bien, mais je suis le genre de personne qui trouve beaucoup de docs bien, je vous laisse vous faire votre opinion. C'est facile de trouver les docs de référence et plein d'article pour préciser des points du langage sur le blog Go (il y a un blog Go).

La lib standard est pas mal, pas aussi fournie que celle de Python mais on y trouve quand même de quoi décoder des png par exemple.

Le langage est livré avec pas mal d'outils, dont un formateur de code, et il y a même un language server officiel (gopls) ! Top, je peux faire des renames à tire larigot dans Vim 🎉 Globalement ça présage d'un langage bien outillé pour travailler. Dommage : le formateur `go fmt` impose des tabs, dans mon éditeur ça passe quand je les affiche comme 4 espaces, mais github les affiche comme huit espaces, je trouve ça moche 🤷 Heureusement il y a un réglage perso pour la largeur des tabs dans github.

C'est facile d'installer et de gérer des dépendances avec `go get`, beaucoup plus simple qu'en Java par exemple pour comparer avec un autre langage curly brackets typé statiquement.

## Conclusion

Dans mon usage j'ai trouvé que ça ressemble à un Lua typé statiquement ou un meilleur TypeScript (des types non optionels, plus exigent, pas de point virgules, on peut le lancer facilement en ligne de commande sans installer et configurer des libs de transpilation, ça juste marche). Je comprends mieux l'intérêt du coup, en plus c'est moins compliqué que Rust et un peu dans le même esprit (ça compile en WebAssembly par exemple).

J'en ressors avec l'impression qu'avec un peu plus d'expérience je pourrais très bien faire un projet côté serveur en Go, en plus de m'en servir comme un langage de script typé statiquement, je suis très content d'y avoir passé un peu de temps 👍🏼

## Références

Pour aller plus loin, plein de docs :

- Documentation ~ <https://go.dev/doc/>
- A Tour of Go ~ <https://go.dev/tour/list>
- Using Go Modules ~ <https://go.dev/blog/using-go-modules>
- How to Write Go Code ~ <https://go.dev/doc/code>
- The Go Programming Language Specification ~ <https://go.dev/ref/spec>
- Go Modules Reference ~ <https://go.dev/ref/mod>
- Standard Library ~ <https://pkg.go.dev/std>
- Frequently Asked Questions (FAQ) ~ <https://go.dev/doc/faq>
- Error Handling and Go ~ <https://go.dev/blog/error-handling-and-go>

Outils :

- gopls ~ <https://pkg.go.dev/golang.org/x/tools/gopls>

## Random

C’est quoi les langages curly brackets ? C'est les langages avec beaucoup de `{` et de `}` dans leur syntaxe, pour délimiter les scopes de fonctions, boucles for, if et autres switch, les classes ou les structures...
Exemples de langages avec beaucoup de curly brackets : C, C++, Java, C#, JavaScript, TypeScript, Go, Rust.
Exemples de langages avec peu de curly brackets : Python, Ruby, Lisp, Lua, Smalltalk, Haskell, Elixir.

Je cherchais un langage typé statiquement que je pourrais lancer facilement en ligne de commande et pour lequel installer des dépendances serait simple. Un genre de croisement des avantages combinés de Java et de JavaScript. C'est un peu ce que j'ai trouvé en Go, je trouve ça chouette.

Je n'aime pas forcément les curly brackets, je suis content d'en avoir trouvé un qui a ces avantages combinés. Il redore un peu le blason de la famille curly brackets.
J'apprécie beaucoup Java pour sa robustesse et ses réfactos autos dans IntelliJ, sans doute C# me plairait aussi, mais pour lancer un script Java en ligne de commande, ou installer une lib en faisant du XML dans un .pom, je trouve ça un peu triste.
J'apprécie JavaScript pour se lancer superfacilement en ligne de commande, et tout installer avec npm install, et aussi pour sa souplesse, mais dans une grosse base de code quand je vois une variable "user" au fin fond d'un appel de fonctions et que je suis incapable de dire quels champs il a et il n'a pas, je trouve ça un peu triste.
Go a l'air de réconcilier un peu tout ça, sans doute qu'il apporte aussi son lot de problèmes.

Dans la famille non curly brackets, j'avais déjà trouvé mon bonheur, avec Python et Ruby qui font quand même un poil plus de vérifications que JavaScript (par exemple le nombre d'arguments) et qui arrivent avec une lib standard bien fournie, et Haskell qui fonctionne très bien en ligne de commande. en plus de son système de types costaud.
