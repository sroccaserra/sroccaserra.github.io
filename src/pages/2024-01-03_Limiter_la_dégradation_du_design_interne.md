-- title: Limiter la dégradation du design interne
-- date: 2024-01-03

Dans mes conversations, j'ai souvent besoin de donner une vision claire
de choses qui font partie de "la programmation" à des personnes de
l'équipe qui ne font pas de dev. J'ai donc deux ou trois notions
classiques dans ma besace qui aident à présenter des aspects peu évidents
ou peu partagés sur ce métier.

Certaines choses sont très claires et bien intégrées par les personnes qui ne font pas de dev. Par exemple, le fait que "pour ajouter un bouton qui fait X, il est nécessaire d'ajouter du code" est évident pour tout le monde dans mon expérience. Mais dans mon activité pour ajouter ledit bouton qui fait X, je fais plein d'autres choses sans m'en rendre compte en plus d'ajouter ce code. Et en général ces choses ne sont pas évidentes, ou pas claires, ou pas connues des personnes qui ne font pas de dev.

Ce matin j'ai relu et ajouté dans ma besace la belle formulation
ci-dessous, qui peut m'aider à clarifier la notion de dégradation
progressive du design interne et le besoin de limiter activement cette
dégradation. C’est une des choses que j’essaie d’inclure dans l’ajout du
bouton qui fait X, en plus d’ajouter le code nécessaire.

> Without refactoring, the internal design—the architecture—of software tends to decay. As people change code to achieve short-term goals, often without a full comprehension of the architecture, the code loses its structure. It becomes harder for me to see the design by reading the code. Loss of the structure of code has a cumulative effect. The harder it is to see the design in the code, the harder it is for me to preserve it, and the more rapidly it decays. Regular refactoring helps keep the code in shape.
>
> Poorly designed code usually takes more code to do the same things, often because the code quite literally does the same thing in several places.

Martin Fowler, Refactoring, 2nd edition, p. 47

Une question pour notre produit / équipe / code : est-ce que notre système en place nous permet de limiter ces dégradations de design interne ? Si non, qu’est-ce qu’on voudrait changer dans notre système pour qu’il le permette ?

Exemples d'autres notions utiles à clarifier que j'ai dans ma besace et
qui ne sont pas "ajouter du code" (peut-être pour d’autres articles
?)&nbsp;:

- Ne pas casser l’existant
- Faciliter l’extension future

Tout ça se recouvre un peu mais n'est pas identique.

Autre point important, nous sommes toujours en temps contraint, et on
veut avoir du feedback fonctionnel rapide. Donc je vais arbitrer en
permanence entre toutes ces contraintes, en essayant de rester
pragmatique. C’est un vaste sujet en soi, et il commence par avoir une
vision et une compréhension partagées de nos contraintes.

Et vous, quelles formulations avez-vous dans votre besace pour avoir des conversations de qualité et clarifier vos contraintes ? 🧵 [@sroccaserra][masto]

[masto]: https://mastodon.social/@sroccaserra/111692273187108670
