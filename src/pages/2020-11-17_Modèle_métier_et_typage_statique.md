Pour moi, comprendre un modèle métier précisément est plus difficile dans des langages typés dynamiquement (comme JavaScript, Python, Ruby) que dans des langages à typages forts (comme Java, C#, Haskell).

Pour illustrer les difficultés que je peux avoir, voici un exemple qui utilise une modélisation un peu riche, tirée du livre [Domain Modeling Made Functional](https://pragprog.com/titles/swdddf/domain-modeling-made-functional/) (chapitre 4 : *Understanding Types)*.

## Dans un langage typé dynamiquement

Dans un langage typé dynamiquement, quand on observe une fonction, il est souvent très difficile de savoir ce que peuvent et ne peuvent pas contenir ses arguments. Par exemple quand on voit une fonction comme :

<pre>
<b>function</b> isAuthorized(payment) {
  // ...
}
</pre>

Ou même :

<pre>
<b>function</b> isAuthorized({amount, currency, method}) {
  // ...
}
</pre>

Comment savoir avec rigueur ce que contiendront exactement les arguments de cette fonction quand elle sera appelée au runtime ? Est-ce que parfois le paramètre `method` sera une simple string, un objet structuré, avec la bonne structure, autre ? Qu'est-ce qu'on va récupérer comme devise ?

On peut se contenter de lire l'implémentation actuelle : ce qui est utilisé dans l'implémentation est un sous ensemble probablement suffisant si le code fonctionne. Mais quand on change ce code, sur quels autres champs peut-on s'appuyer ? Seront-ils présents dans tous les cas d'usage ?

Peut-être qu'il y a une classe `Payment` déclarée quelque-part, mais même si je la trouve, rien n'empêche le code d'ajouter ou de supprimer des champs avant l'appel de cette fonction, ou même d'utiliser un simple `Object` qui a à peu près la bonne forme à la place, comme dans la deuxième version ci-dessus.

En pratique on se retrouve souvent à utiliser grep sur tout le code pour explorer les appels de cette fonction, et à déboguer le code dans plusieurs cas d'usage si on veut avoir la réponse.

## Dans un langage avec typage fort

Pour montrer le niveau d'information apporté par une modélisation métier avec un typage fort, voici la même fonction déclarée en Haskell :

<pre>
isAuthorized :: Payment -> Bool
isAuthorized p =
  -- ...
</pre>

La grosse différence est que dans ce cas je peux aller observer la déclaration du type `Payment`, je n'ai pas à lancer grep sur tout le code ou à poser des points d'arrêt et autres `console.log` un peu partout. La vérification de type me garantit que cette fonction sera toujours appelée avec une valeur de type `Payment`, et que cette valeur aura toujours la bonne forme.

Voici par exemple ce qu'on pourrait trouver comme déclaration riche du type `Payment` :

<pre>
<b>data</b> CardNumber = CardNumber Int
<b>data</b> CheckNumber = CheckNumber Int

<b>data</b> CardType = Visa | Mastercard
<b>data</b> CreditCardInfo = CreditCardInfo { cardType :: CardType
                                     , cardNumber :: CardNumber
                                     }

<b>data</b> PaymentMethod = Cash
                   | Check CheckNumber
                   | Card CreditCardInfo

<b>data</b> PaymentAmount = PaymentAmount Decimal
<b>data</b> Currency = EUR | USD

<b>data</b> Payment = Payment { amount :: PaymentAmount
                       , currency :: Currency
                       , method :: PaymentMethod
                       }
</pre>

On peut observer que ce type est à la fois riche et définit très précisément. On est aussi certain en un coup d’œil de ce qu'il contient exactement au runtime. En le lisant de bas en haut, on sait qu'on va avoir :

- un montant qui est un nombre décimal
- une devise soit en euros soit en dollars
- une méthode de paiement qui est à son tour précisément définie : c'est soit du cash, soit un chèque avec un numéro, soit une carte bancaire qui à son tour définit un type et un numéro de carte.

On peut aussi voir avec certitude tous les cas qu'on devra traiter lorsqu'on utilise une valeur de ce type. Paiement cash, par chèque, par carte, paiements en euro et en dollars.

De même quand on remanie l'implémentation d'une fonction utilisant ce type, on connait précisément les éléments dont on dispose pour la nouvelle implémentation.

Il est rare d'avoir autant de connaissances et ce niveau de certitude dans un langage typé dynamiquement.

## Conclusion

Les difficultés des langages à typage dynamique illustrées ici n'apparaissent pas toujours. Sur des projets de petite taille, avec deux ou trois personnes bien alignées qui réinjectent régulièrement leurs compréhension du métier dans le code (ce qui est une discipline très difficile à avoir), grâce par exemple à TDD et au refactoring systématique, on peut trouver du code facile à suivre.

Et c'est vrai que malgré mes difficultés, j'apprécie beaucoup des langages comme Ruby, Smalltalk, Lisp, Python, et même Lua, Awk et JavaScript (qui décrochent le pompon en terme de permissivité ?). C'est dans ces langages que j'ai travaillé quasiment exclusivement depuis 2015.

Cependant, pour mes prochains projets je souhaite retrouver un typage fort afin de travailler avec plus de confort la modélisation du métier dans le code. Et en bonus, afin d'avoir le plus d'expressivité possible, je souhaite pouvoir profiter :

- des [types sommes](https://en.wikipedia.org/wiki/Tagged_union),
- du [filtrage par motif](https://en.wikipedia.org/wiki/Pattern_matching),
- de l'[inférence de type](https://en.wikipedia.org/wiki/Type_inference) (disponible depuis [ML](https://en.wikipedia.org/wiki/ML_(programming_language)), soit bientôt 50 ans ?).

Je crois que c'est le cas pour Kotlin, Rust, Haskell, F# / OCaml, Elm, PureScript, Reason, ReScript ce qui laisse pas mal de choix.

Ce qui est certain, c'est que si je participe au démarrage d'un projet en JavaScript ou Node.js, je vais militer pour partir sur TypeScript dès le départ.
