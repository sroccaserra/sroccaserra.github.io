-- title: Quelques bonnes références classiques sur TDD
-- date: 2023-09-07

Suite à des conversations avec des collègues, voilà la liste des refs classiques sur TDD (Test-Driven Development) auxquelles je me réfère souvent. Super pour s’inspirer et approfondir le sujet.

Note : il y en a d’autres, si vous avez de bonnes refs classiques passez les moi 🙏 [@sroccaserra](https://mastodon.social/@sroccaserra)

## Livres

- [Test-Driven Development: By Example](https://www.goodreads.com/book/show/387190.Test_Driven_Development)
    - Super introduction de Kent Beck, "the" référence
- [xUnit Test Patterns: Refactoring Test Code](https://www.goodreads.com/book/show/337302.xUnit_Test_Patterns)
    - Version gratuite en html : <http://xunitpatterns.com/>
    - Gros pavé
    - Énormément de patterns de références
    - Toutes les astuces classiques y sont ?
- [Growing Object-Oriented Software, Guided by Tests](https://www.goodreads.com/book/show/4268826-growing-object-oriented-software-guided-by-tests)
    - Un super exemple de dev en TDD
    - Comment récupérer du feedback rapidement
    - Plein de conseils sur l'écriture des test, par ex. un chapitre "Test Flexibility"
    - En bonus, des principes de programmation orientée objet ~ Tell don't ask, Follow the Messages, ...
    - A popularisé l'idée de mocks ~ ni trop, ni trop peu : si vous avez trop de mocks c'est que vous ne suivez pas les conseils de ce livre
        - Don't mock values
        - Only mock types that you own
        - Allow Queries; Expect Commands

## Articles

- [c2:Test-Driven Development](http://wiki.c2.com/?TestDrivenDevelopment)
    - Discussion sur c2.com, "the" wiki
- [bliki:UnitTest](https://martinfowler.com/bliki/UnitTest.html)
    - Article sur le bliki de Martin Fowler
- [Don't Mock What You Don't Own](https://github.com/testdouble/contributing-tests/wiki/Don%27t-mock-what-you-don%27t-own)
    - Pourquoi il n'est pas recommandé de mocker ce qui ne nous appartient pas, et que faire à la place
    - Voir aussi : [That's Not Yours](https://8thlight.com/insights/thats-not-yours)
- [Mocks for Commands, Stubs for Queries](https://blog.ploeh.dk/2013/10/23/mocks-for-commands-stubs-for-queries/)
    - Explication détaillée du principe _Allow Queries; Expect Commands_ trouvé dans le livre Growing Object-Oriented Software
- [You Don't Hate Mocks; You Hate Side-Effects](https://blog.thecodewhisperer.com/permalink/you-dont-hate-mocks-you-hate-side-effects)
    - Un bon exemple / explication du lien mock / side effect et comment faire évoluer notre design en écoutant ce que dit le code

## Vidéos

- [Rails Conf 2013: The Magic Tricks of Testing by Sandi Metz](https://www.youtube.com/watch?v=URSWYvyc42M)
    - Explication de critères pour décider quoi tester, quoi ne pas tester, pourquoi et comment
    - J'utilise très souvent le tableau montré dans la conf, qui résume très bien l'ensemble
    - Regardez la conf pour bien comprendre le tableau :

<div class="center">
<table class="">
    <thead>
        <tr>
            <th>Message</th>
            <th>Query</th>
            <th>Command</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Incoming</td>
            <td><i>Assert</i><br/>result</td>
            <td><i>Assert</i><br/>direct public<br/>side effects</td>
        </tr>
        <tr>
            <td>Sent to self</td>
            <td style="color: grey;">Ignore</td>
            <td style="color: grey;">Ignore</td>
        </tr>
        <tr>
            <td>Outgoing</td>
            <td style="color: grey;">Ignore</td>
            <td><i>Expect</i><br/>to send</td>
        </tr>
    </tbody>
</table>
</div>

- Présentation d'Outside-In TDD par l'exemple (Sandro Mancuso) :
    - [Outside In TDD part I](https://www.youtube.com/watch?v=XHnuMjah6ps)
    - [Outside In TDD part II](https://www.youtube.com/watch?v=gs0rqDdz3ko)
    - [Outside In TDD part III](https://www.youtube.com/watch?v=R9OAt9AOrzI)
