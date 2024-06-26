-- title: Quelques références sur le couplage dans le code
-- date: 2020-10-31

Récemment j'ai fait un petit tour des tables des matières d'ouvrages classiques
pour trouver des références sur le couplage dans le code. Voici ce que j'ai
récolté, sans ordre de préférence.

## Livres

### The Pragmatic Programmer

Tout d'abord, The Pragmatic Programmer est une super référence sur le sujet.

Notamment dans la 2e édition, le topic 28, Decoupling, pp. 130-137.

Pour vous donner envie de le lire (et ça me donne super envie de le relire !!),
ça parle de&nbsp;:

- Structural Rigidity,
- Tip 44 : Decoupled code is easier to change,
- Train wrecks,
- Tip 45 : Tell, don’t ask,
- The law of Demeter,
- Tip 46 : Don’t chain method calls
- The evils of globalization
- Tip 47 : Avoid global data
- Tip 48 : If it’s important enough to be global, wrap it in an API
- Inheritance adds coupling
- Again, it’s all about change

### Refactoring

Dans Refactoring, il y a les code smells opposés “Divergent Change” et “Shotgun
Surgery” (p. 76 de la 2ème édition), et "Message Chain" (p. 81) avec les
refactorings associés.

### Code Complete

Dans Code Complete&nbsp;:

> Loose coupling: Loose coupling means designing so that you hold connections
> among different parts of a program to a minimum. Use the principles of good
> abstractions in class interfaces, encapsulation, and information hiding to
> design classes with as few interconnections as possible. Minimal
> connectedness minimizes work during integration, testing, and maintenance.

Et le chapitre Design Building Blocks: Heuristics, dont l’heuristique Keep
Coupling Loose, p. 100, qui parle de :

- Coupling Criteria (size, visibility, flexibility)
- Kinds of Coupling (simple data parameter coupling, simple object coupling, object parameter coupling, semantic coupling)

Et aussi l’heuristique “Aim for strong cohesion”, p. 105.

### Clean Architecture

Le livre Clean Architecture a un chapitre Component Cohesion, un chapitre
Component Coupling et un chapitre Independance, qui parle de Decoupling Layers,
Decoupling Use Cases et Decoupling Mode.

### Working Effectively with Legacy Code

Dans le livre Working Effectively with Legacy Code il y a le chapitre 25,
Dependency-Breaking Techniques, qui donne des techniques pour découpler des
classes suffisamment pour pouvoir les tester.

## Articles

Il y a aussi l’article sur le pattern Big Ball of Mud que j’aime bien :

- <http://www.laputan.org/mud/>

Cette conférence récente d’Arnaud Lemaire :

- [Votre application a besoin de son jardin secret : attention à la localité de l’information][al]

[al]: https://www.lilobase.me/votre-application-a-besoin-de-son-jardin-secret-attention-a-la-localite-de-linformation/

Et coïncidence, ce tweet d'aujourd'hui de Kent Beck :

- [twitter.com/KentBeck/status/1322545224220991488][kb]

[kb]: https://twitter.com/KentBeck/status/1322545224220991488

> Coupling vs cohesion.
>
> Coupling:
>
> - Can be hard to find
> - Can be really hard &amp;/| expensive to eliminate.
>
> Cohesive sub-elements are:
>
> - Usually easy to find
> - Cheap to achieve, &amp;
> - Help you find de-coupling.

## Conclusion

C’était chouette de faire ce petit tour de tables des matières dans ces
ouvrages, maintenant il me faut du temps pour les lire ou relire, et mettre en
pratique 😯 Bonne lecture, bonne pratique de vos apprentissages !

## Liens

Les livres cités :

- [The Pragmatic Programmer][pp]
- [Refactoring][r]
- [Clean Code][cc]
- [Clean Architecture][ca]
- [Working Effectively With Legacy Code][wewlc]

[pp]: https://pragprog.com/titles/tpp20/the-pragmatic-programmer-20th-anniversary-edition/
[r]: https://martinfowler.com/books/refactoring.html
[cc]: https://www.informit.com/store/code-complete-9780735619678
[ca]: https://www.informit.com/store/clean-architecture-a-craftsmans-guide-to-software-structure-9780134494166
[wewlc]: https://www.informit.com/store/working-effectively-with-legacy-code-9780131177055
