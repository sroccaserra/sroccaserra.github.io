L'injection de dépendances, c'est à la fois simple et compliqué.

C'est simple car on voit souvent l'idée que&nbsp;: "c'est juste passer les
dépendances en paramètre du constructeur". Et dans un sens, "c'est pas faux".

Les choses commencent à se compliquer quand on essaie de la définir. Une
définition pourrait être par exemple&nbsp;:

> On appelle "Injection de Dépendances" un ensemble de principes et de patterns
> logiciels qui permettent de développer du code faiblement couplé.

Et quand on commence à vouloir utiliser ces principes et patterns dans notre
code, on commence à se poser plusieurs questions. Par exemple&nbsp;:

- À quoi ça ressemble concrètement ?
- Qui est responsable d'injecter ces dépendances ?
- À quel moment est-ce que j'injecte mes dépendances ?
- Où est-ce que je vais instancier ces dépendances ?
- Est-ce que je suis obligé de passer par un framework ?
- Quelle est la différence entre Injection de Dépendances et Inversion de Dépendances ?
- Quels sont les patterns classiques ?
- Est-ce qu'il y a des anti-patterns ?

Donc c'est aussi potentiellement un peu compliqué.

J'ai récemment lu le livre [Dependency Injection: Principles, Practices, and
Patterns][di], de Stephan van Deursen et Mark Seemann. Ce livre apporte
beaucoup de réponses, et j'ai été surpris et très intéressé par la richesse du
sujet. (Et si vous êtes comme moi, vous apprécierez la virgule de série du
sous-titre).

Pour partager une petite partie de ce que j'ai vu, je propose de regarder
l'exemple de code du livre, décrit en détail dans le chapitre 3. À chaque
étape, j'essaierai de mettre en valeur quelques points qui m'ont
particulièrement intéressé.

Note : cet article sera sans doute beaucoup plus intéressant si vous avez déjà
quelques notions sur l'injection de dépendances. Si vous voulez en savoir plus,
vous pouvez commencer par lire l'article [Inversion of Control Containers and
the Dependency Injection pattern][mf] de Martin Fowler.

[mf]: https://martinfowler.com/articles/injection.html

Note : l'exemple est en C#, mais les principes appliqués devraient fonctionner
quel que soit le langage et le framework. Ici le choix est fait de ne pas
utiliser de container d'injection de dépendance, afin de bien voir toutes les
parties.

Avertissement / Disclaimer : ce qui suit est un exemple qui illustre très bien
de nombreux points mais ce n'est pas "the only true way" pour gérer les
dépendances. Si vous avez d'autres façons de faire, si vous utilisez le
framework X ou Y, c'est très bien, voyez ce qui fonctionne pour vous.
L'important est que vous ayez une bonne compréhension de vos pratiques et de ce
qu'elles vous apportent.

## La fonctionnalité

L'exemple décrit une fonctionnalité d'un site d'e-commerce. Cette
fonctionnalité consiste à afficher une liste de *featured products* (produits
phares) avec leurs prix. Si le client connecté est un *preffered customer*
(client privilégié), alors il a droit à un *discount* (rabais) de 5 % sur ces
*featured products* et les prix affichés doivent tenir compte de ce rabais.

Exemple de résultat attendu (imaginer une vue en joli HTML ici):

<pre>
<b>Featured Products</b>

- Criollo Chocolate ($34.95)
- Gruyère ($48.50)
- White Asparagus ($39.80)
- Anchovies ($18.75)
- Arborio Rice ($22.75)
</pre>


## La vue

Je vais commencer à décrire tout le code en commençant par la vue. Ce n'est pas
très intéressant tout de suite, mais ça permet de bien voir l'ensemble en
partant de l'aspect visible de la fonctionnalité.

Les parties en gras font le lien d'un bout de code à l'autre.

<pre>
<i>@* src/Commerce.Web/Views/Home/Index.cshtml *@</i>
@model FeaturedProductsViewModel

&lt;h2&gt;Featured Products&lt;/h2&gt;
&lt;ul&gt;
    @foreach (<b>ProductViewModel</b> product in this.Model.Products)
    {
        &lt;li&gt;<b>@product.SummaryText</b>&lt;/li&gt;
    }
&lt;/ul&gt;
</pre>

Ci dessus, on voit qu'on itère sur des `ProductViewModel` pour afficher leur
`SummaryText`. Comme on l'a vu dans la liste de Featured Products affichée
ci-dessus, ces `SummaryText` montrent un nom et un prix. Voyons d'où viennent
ces informations.

<!--
// src/Commerce.Web/Models/FeaturedProductsViewModel.cs
public class FeaturedProductsViewModel
{
    public FeaturedProductsViewModel(
        IEnumerable<ProductViewModel> products)
    {
        this.Products = products;
    }

    public IEnumerable<ProductViewModel> Products
        { get; }
}
-->

<pre>
<i>// src/Commerce.Web/Models/ProductViewModel.cs</i>
public class ProductViewModel
{
    private static CultureInfo PriceCulture = new CultureInfo("en-US");

    public ProductViewModel(<b>DiscountedProduct product</b>)
    {
        this.SummaryText = string.Format(PriceCulture,
            "{0} ({1:C})", <b>product.Name</b>, <b>product.UnitPrice</b>);
    }

    public string SummaryText { get; }
}
</pre>

On peut voir ci-dessus que les infos nécessaires à fabriquer `SummaryText`, le
nom et le prix des produits, sont passées à la construction des instances de
`ProductViewModel` sous la forme d'un `DiscountedProduct`, qu'on verra plus
bas.

Ça va commencer à devenir intéressant, descendons dans le controller qui traite
la requête pour voir qui nous fournit ces `DiscountedProducts`.

## Le controller

<pre>
<i>// src/Commerce.Web/Controllers/HomeController.cs</i>
public class HomeController : Controller
{
    private readonly IProductService productService;

    public HomeController(
        <b>IProductService productService</b>)  <i>// 1) Dépendance au service injectée</i>
    {
        if (productService == null)
            throw new ArgumentNullException(
                "productService");

        this.productService = productService;
    }

    public ViewResult Index()
    {
        IEnumerable<DiscountedProduct> products =
            <b>this.productService.GetFeaturedProducts()</b>;  <i>// 2) Récupération des DiscountedProduct</i>

        var vm = new FeaturedProductsViewModel(
            from product in products
            select <b>new ProductViewModel(product)</b>);  <i>// 3) Instanciation des ProductViewModel</i>

        return this.View(vm);
    }
}
</pre>

Comme on le voit ci-dessus, c'est un `IProductService` qui a la responsabilité
de fournir la liste des *featured products* au controller. On voit aussi que ce
service est injecté, c'est le premier exemple de cette fameuse injection par
paramètre de constructeur.

Allons voir en quoi consiste ce service.

## Le service

Le `IProductService` est ici ce qu'on appelle parfois un *Application Service*.
À la place du mot *service*, on voit aussi parfois un répertoire `usecases`,
avec des classes qui ont ce type de responsabilités d'orchestration, ça
pourrait correspondre.

<pre>
<i>// src/Commerce.Domain/IProductService.cs</i>
public interface IProductService
{
    <b>IEnumerable<DiscountedProduct> GetFeaturedProducts()</b>;
}
</pre>

L'*application service*, c'est avant tout l'interface `IProductService`
ci-dessus, une liste de méthodes publiques. Le `HomeController` n'a pas à en
savoir plus, et ne doit pas dépendre de l'implémentation du service. Mais comme
on veut faire tout le chemin, allons observer cette fameuse implémentation.

<pre>
<i>// src/Commerce.Domain/ProductService.cs</i>
public class ProductService : IProductService
{
    private readonly IProductRepository repository;
    private readonly IUserContext userContext;

    public ProductService(
        <b>IProductRepository repository</b>,  <i>// 1) Dépendances, injectées par constructeur</i>
        <b>UserContext userContext</b>)
    {
        if (repository == null)
            throw new ArgumentNullException("repository");
        if (userContext == null)
            throw new ArgumentNullException("userContext");

        this.repository = repository;
        this.userContext = userContext;
    }

    public IEnumerable<DiscountedProduct> <b>GetFeaturedProducts</b>()
    {
        return
            from product in this.repository
                .GetFeaturedProducts()                <i>// 2) récupération des produits phares</i>
            select product
                .ApplyDiscountFor(<b>this.userContext</b>);  <i>// 3) application des rabais en fonction du userContext</i>
    }
}
</pre>

Il y a trois points à observer ici.

On peut voir à nouveau en 1) de l'injection de dépendances par paramètres de
constructeur.

On peut voir également en 2) la récupération des featured products à partir
d'un repository.

Et en 3) on peut voir un élément moins courant, le passage d'un userContext à
la méthode `ApplyDiscountFor()` de l'entité `Product`. On verra le détail de
cette méthode plus bas. Pour le moment, on peut noter que ce `IUserContext` est
également injecté dans le service au niveau du constructeur.

Comme on le verra plus bas, ce `IUserContext` est résolu et injecté à chaque
requête.

## L'entité Product et l'objet DiscountedProduct

On peut observer ici un exemple d'entité qui porte des responsabilités métier,
comme appliquer un *discount*. Ce n'est pas un simple sac de données.

<pre>
<i>// Product Entity
// src/Commerce.Domain/Product.cs</i>
public class Product
{
    public string Name { get; set; }
    public decimal UnitPrice { get; set; }
    public bool IsFeatured { get; set; }

    public <b>DiscountedProduct ApplyDiscountFor</b>(  <i>// 1) Application d'un rabais</i>
        <b>IUserContext user</b>)                      <i>// 2) Injection de contexte par méthode</i>
    {
        bool preferred =
            <b>user.IsInRole(Role.PreferredCustomer)</b>;  <i>// 3) Utilisation du contexte pour déterminer si l'utilisateur est "preferred"</i>

        decimal discount = preferred ? .95m : 1.00m;

        return <b>new DiscountedProduct</b>(               <i>// 4) Construction d'un autre type</i>
            name: this.Name,
            unitPrice: this.UnitPrice * discount);
    }
}
</pre>

Il y a à nouveau beaucoup de choses intéressantes ici.

1) Comme dit plus haut, cette entité sait faire des choses, comme appliquer un
*discount*.

2) Pour appliquer ce *discount*, l'entité a besoin du contexte utilisateur, qui
est variable et peut changer à chaque requête. Ce contexte est injecté par
méthode, c'est un pattern moins discuté que l'injection par constructeur, mais
très pertinent ici. C'est pertinent ici car l'injection par constructeur ne va
pas fonctionner : on ne veut pas avoir besoin de connaître des choses sur
l'utilisateur connecté au moment de la construction des entités `Product`, qui
a probablement lieu dans une implémentation de *product repository*.

3) Ici l'entité pose une question au contexte, elle ne dépend pas de sa
structure interne. "Est-ce que l'utilisateur est preffered ?" Ce qui veut dire
qu'on peut changer la structure interne du UserContext sans avoir à changer
l'entité.

4) Appliquer un *discount* ne modifie pas l'entité Product, mais crée un nouvel
objet de type "DiscountedProduct", qu'on va voir ci-dessous.

<pre>
<i>// DiscountedProduct POCO class
// src/Commerce.Domain/DiscountedProduct.cs</i>
public class DiscountedProduct
{
    public DiscountedProduct(string name, decimal unitPrice) {
        if (name == null) throw new ArgumentNullException("name");

        this.Name = name;
        this.UnitPrice = unitPrice
    }

    public string Name { get; }
    public decimal UnitPrice { get; }
}
</pre>

Cet objet `DiscountedProduct` est lui un sac de données. C'est un objet
d'échange. C'est lui qui est passé à la vue, qui l'utilise pour produire ses
`SummaryText` comme on l'a vu plus haut.

## Le IUserContext

Voyons maintenant un exemple simple d'implémentation de `IUserContext`.

<pre>
<i>// src/Commerce.Domain/IUserContext.cs</i>
public interface IUserContext
{
    bool IsInRole(Role role);
}

// src/Commerce.Domain/Role.enum.cs
public enum Role { PreferredCustomer }
</pre>

C'est avant tout une interface, avec des méthodes publiques. Ici, une méthode
publique, `IsInRole()`. Cette méthode a la responsabilité de dire si
l'utilisateur possède tel ou tel rôle. En passant, les rôles sont définis par
exemple par une enum, pourquoi pas.

Comme on le voit ci-dessous, l'implémentation nécessitera une adaptation vers
le framework.

<!--
De l’autre côté, un CommerceContext héritant de DbContext, initialisé avec la chaîne de connexion SQL, peut être injecté par constructeur aux repositories.

<pre>
<i>// SqlProductRepository, not dependent on connection string
// src/Commerce.SqlDataAccess/SqlProductRepository.cs</i>
public class SqlProductRepository : IProductRepository
{
    private readonly CommerceContext context;

    public SqlProductRepository(CommerceContext context)
    {
        if (context == null) throw new ArgumentNullException("context");

        this.context = context;
    }

    public IEnumerable<Product> GetFeaturedProducts()
    {
        return
            from product in this.context.Products
            where product.IsFeatured
            select product;
    }
}

<i>// CommerceContext, manages the Entity Framework & configuration stuff
// src/Commerce.SqlDataAccess/CommerceContext.cs</i>
public class CommerceContext : DbContext
{
    private readonly string connectionString;

    public CommerceContext(string connectionString)
    {
        if (string.IsNullOrWhiteSpace(connectionString))
            throw new ArgumentException(
                "connectionString should not be empty.",
                "connectionString");

        this.connectionString = connectionString;
    }

    public DbSet<Product> Products { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder builder)
    {
        builder.UseSqlServer(this.connectionString);
    }
}
</pre>

- https://learn.microsoft.com/en-us/dotnet/api/system.data.entity.dbcontext?view=entity-framework-6.2.0

-->

## UserContext et adaptation vers le Framework

Dans cet exemple en ASP.NET, une façon d'implémenter ce UserContext est
d'utiliser le `HttpContextAccessor` fourni par le framework. Le framework nous
dit que cet objet connait les rôles de l'utilisateur dans le contexte de la
requête. Ici c'est un peu magique à mon goût mais je fais confiance au
framework. Par exemple :

<pre>
<i>// src/Commerce.Web/AspNetUserContextAdapter.cs</i>
public class AspNetUserContextAdapter : IUserContext
{
    private static HttpContextAccessor Accessor = new HttpContextAccessor();

    public bool IsInRole(Role role)
    {
        return Accessor.HttpContext.User.IsInRole(role.ToString());
    }
}
</pre>

On voit que pour le framework, les rôles sont des strings, et qu'on a choisi
une enum plus haut. C'est très bien, l'adaptation est faite ici, et on ne se
plie pas aveuglément aux choix du framework.

On voit aussi que cette adaptation nécessitera de bien connaître votre
framework, et peut-être d'adapter les choses à votre cas.

La dernière étape sera de voir comment tout ça se connecte : comment est-ce qu'on va brancher toutes ces dépendances ?

## Composition Root

C'est bien beau toutes ces dépendances, mais on n'a pas encore vu comment tout
se branche concrètement.

Un des patterns important du livre est la notion de *Composition Root*. C'est
dans le Composition Root que le graphe de toutes les dépendances qu'on a vues
jusqu'ici est enfin résolu.

Si on utilise un container d'injection de dépendance, cette résolution sera
faite pour vous. Mais comme on le voit ci-dessous, on n'est pas obligé
d'utiliser un container, une résolution KISS peut aussi fonctionner.

Ici on observe ce qui se passe dans notre implémentation du
`IControllerActivator`, interface du framework qui est au bon endroit pour
servir de *Composition Root*.

<pre>
<i>// The application's object graph
// more or less in the IControllerActivator.Create() method

// src/Commerce.Web/CommerceControllerActivator.cs</i>
new <b>HomeController</b>(
    new <b>ProductService</b>(
        new <b>SqlProductRepository</b>(
            new CommerceContext(connectionString)),
        new <b>AspNetUserContextAdapter</b>()));

</pre>

On peut voir explicitement comment les dépendances sont injectées, un peu comme
des poupées russes. Le `HomeController`, le `ProductService`, le `SqlProductRepository` (`IProductRepository`), et le `AspNetUserContextAdapter` (`IUserContext`).

Note : je n'ai pas décrit l'implémentation du IProductRepository, car c'est
souvent quelque-chose qui est connu et que l'article est déjà très long.

Il y a quelques finesses qui méritent d'être soulignées avant de terminer ce
tour d'horizon.

Tout d'abord, il est important que ce graphe soit résolu à un seul endroit, le
*Composition Root*. Si on rend les dépendances disponibles dans tout le code,
et qu'à n'importe quel endroit du code on peut accéder à une dépendance par une
forme de *Registry* ou de *ServiceLocator*, on va avoir le même problème que
quand on utilise des variables globales : potentiellement, tout peut dépendre
de tout, et le code devient très difficile à changer avec confiance.

Ensuite, la résolution est faite au plus prêt possible du point d'entrée de
l'application. Ici, dès qu'une requête arrive, on instancie tout et les
dépendances sont branchées pour tout le reste de l'exécution de la requête.

Note : on pourrait avoir peur pour les performances si on résout tout à chaque
requête, mais en pratique c'est rarement un problème. Si vous mesurez que dans
votre cas c'est effectivement un problème, le livre propose des solutions mais
je ne rentre pas dans ce détail.

## Pour aller plus loin

Pour aller plus loin, on pourrait observer que certaines dépendances sont
stables, et ne nécessitent pas d'être injectées. Le livre parle de *stable
dependencies* et de *volatile dependencies*. Ce sont les dépendances volatiles
qui nécessitent d'être injectées.

Une dépendance est "volatile" quand elle n'est pas toujours disponible (bases
de données, services Web, ...), quand elle contient un comportement non
déterministe (temps, ...) ou qu'elle a besoin d'être remplacée, encapsulée, ou
interceptée (il reste peu de choses ici normalement une fois qu'on a vu les
deux premiers groupes).

On pourrait aussi chercher si dans le *Composition Root* il n'y a pas une
partie configuration des dépendances, et une partie résolution. Un pattern
possible est de séparer configuration et résolution, en mettant la
configuration dans un fichier par exemple. Typiquement, la configuration est
faite au démarrage de l'application, et la résolution peut se faire à chaque
requête.

On peut également s'intéresser à comment utiliser notre framework ou un
container d'injection de dépendances, maintenant qu'on a vu une façon de faire
un peu complète.

Je vous invite à consulter le livre [Dependency Injection][di] ou le blog de
Mark Seemann pour en savoir plus sur ces patterns.

## Conclusion

C'est terminé, on a enfin bouclé ce très grand tour qui nous montre
concrètement à quoi peut ressembler en pratique notre injection de dépendances.

On a vu le pattern classique "injection par paramètre de constructeur", le
pattern moins discuté "injection par paramètre de méthode", on a même observé
une entité métier qui est responsable d'un comportement.

On a également vu "quand" est faite l'injection, et une version naïve de
"comment" est faite l'injection, avec cette notion de *Composition Root*.

Rien n'est particulièrement compliqué, mais je trouve intéressant de
récapituler comment tout ça peut fonctionner ensemble, c'est souvent ce qui
manque aux exemples qui ne montrent qu'une seule partie.

## Liens

- Le livre [Dependency Injection: Principles, practices, and Patterns][di]
- L'[exemple de code](https://github.com/DependencyInjection-2nd-edition/codesamples/tree/master/RightECommerce), en un peu plus détaillé
- Le [blog de Mark Seemann](https://blog.ploeh.dk/)
- Les [nombreux articles sur l'injection de dépendances](https://blog.ploeh.dk/tags/#Dependency%20Injection-ref) dans ce blog

[di]: https://www.manning.com/books/dependency-injection-principles-practices-patterns
