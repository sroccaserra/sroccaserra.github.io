Cette semaine j'avais envie d'explorer un nouveau langage. Je souhaitais avoir un typage fort et des fonctions [currifiées][cu] par défaut : j'ai essayé OCaml, et j'ai été agréablement surpris.

[cu]: https://fr.wikipedia.org/wiki/Curryfication

## Kata Bowling en OCaml

Pour découvrir le langage, je me suis lancé sur une implémentation du [kata bowling](https://codingdojo.org/kata/Bowling/) :

<pre>
<b>type</b> roll = Roll <b>of int</b>

<b>type</b> frame = Frame <b>of int</b>
<b>let</b> next (Frame n) = Frame (n + 1)

<b>let rec</b> score ?(f=Frame 1) = <b>function</b>
  | [] -> 0
  | [Roll x; Roll y; Roll z] <b>when</b> is_last_frame f ->
      x + y + z
  | r1 :: (Roll y <b>as</b> r2) :: (Roll z <b>as</b> r3) :: rest <b>when</b> is_strike r1 ->
      10 + y + z + score ~f:(next f) (r2 :: r3 :: rest)
  | r1 :: r2 :: (Roll z <b>as</b> r3) :: rest <b>when</b> is_spare r1 r2 ->
      10 + z + score ~f:(next f) (r3 :: rest)
  | Roll x :: Roll y :: rest ->
      x + y + score ~f:(next f) rest
  | [_] -> failwith "wrong number of rolls"
<b>and</b> is_strike = (=) @@ Roll 10
<b>and</b> is_spare (Roll x) (Roll y) = 10 == x + y
<b>and</b> is_last_frame = (=) @@ Frame 10
</pre>

Le répo github est ici, la liste des commits montre le cheminement :

- <https://github.com/sroccaserra/bowling-game-kata-ocaml>

## Ce que j'ai apprécié

- Quand on connait un peu Haskell, on se sent vite à la maison
- La [documentation en français][df]
- Il y a des [guidelines][gl] et des [cheatsheets][cs] pour démarrer
- Le [paradigme fonctionnel][fn] et le pattern matching
- En OCaml, il n'y a que des [expressions][ex]
- Ne pas avoir à répéter le nom de la fonction pour chaque pattern
- Le pattern matching implicite avec `function`
- Les paramètres nommés et avec valeurs par défaut (voir ci-dessus, `?(f=Frame 1)`)
- Je n'ai pas essayé, mais je suis curieux de l'aspect orienté objet
- L'inférence de type et le typage fort, c'est chouette d'être aidé par un compilateur
- Avoir une erreur de compilation par défaut pour les patterns non exhaustifs et les variables non utilisées
- Le système de build ([dune][du]), je n'ai pas eu de mal à le prendre en main (pour ce tout petit projet)
- C'est facile de lancer les tests en mode watch (`dune runtest -w`)
- Installer des libs avec opam, ça fonctionne
- C'est facile de visualiser les erreurs de compilation à la volée dans Vim
- Les sources de gros projets sont dispos pour s'inspirer ([JaneStreet][js] et [Mirage][mi] par exemple)
- OCaml a des variantes plus ou moins populaires, comme F# (une base de OCaml sous .NET), et Reason /  ReScript.

[df]: https://ocaml.org/learn/index.fr.html
[gl]: https://ocaml.org/learn/tutorials/guidelines.html
[fn]: https://ocaml.org/learn/tutorials/functional_programming.fr.html
[cs]: https://ocaml.org/docs/cheat_sheets.html
[du]: https://github.com/ocaml/dune
[js]: https://github.com/janestreet
[mi]: https://github.com/mirage
[ex]: https://fsharpforfunandprofit.com/posts/expressions-vs-statements/

## Ce que j'ai moins apprécié

- <strike>On ne peut pas suivre la step down rule (définir la fonction appelante au dessus de la fonction appelée) si j'ai bien compris</strike> <-- en fait si, avec `and`, voir la fonction `is_strike` ci-dessus
- Devoir répéter le pattern pour chaque guarde `when`
- Des symbols un peu plus présents qu'en Haskell (`::` pour `:`, `@@` pour `$`, les `~` devant les paramètres nommés)
- Le `;;` pour finir une instruction dans le repl

## Kata Bowling en Haskell

Pour explorer les ressemblances, j'ai fait le même kata en Haskell :

<pre>
<b>module</b> Bowling (score, Roll(..)) <b>where</b>

<b>data</b> Roll = Roll Int
  <b>deriving</b> (Eq)

<b>data</b> Frame = Frame Int
  <b>deriving</b> (Eq)
next (Frame n) = Frame (n + 1)

score = score' $ Frame 1
score' f xs = <b>case</b> xs <b>of</b>
  [] -> 0
  r1@(Roll x):r2@(Roll y):r3@(Roll z):rest
    | isLastFrame f ->
      x + y + z
    | isStrike r1 ->
      10 + y + z + score' (next f) (r2:r3:rest)
    | isSpare r1 r2 ->
      10 + z + score' (next f) (r3:rest)
  Roll x:Roll y:rest ->
    x + y + score' (next f) rest
  [_] -> error "Wrong number of rolls"
  <b>where</b>
    isStrike = (==) $ Roll 10
    isSpare (Roll x) (Roll y) = 10 == x + y
    isLastFrame = (==) $ Frame 10
</pre>

Sur cet exemple, les deux implémentations sont vraiment proches.

Le répo github est ici, la liste des commits montre le cheminement :

- <https://github.com/sroccaserra/bowling-game-kata-haskell>

## Conclusion

Je suis content d'avoir découvert OCaml, je pense en refaire plus tard, par exemple pour explorer l'orientation objet. Ou peut-être découvrir F# pour explorer encore un autre langage de ce type ?

Note : je ne suis un expert ni en OCaml, ni en Haskell. Je suis preneur d'avis pour améliorer tout ça.
