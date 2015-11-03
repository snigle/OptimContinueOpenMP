Introduction
============

Ceci est une version .md du rapport. Ce fichier ne contient uniquement les informations relatives à l'API. Vous trouverez le détail de nos recherche dans le fichier pdf.


API
===

Fonction Objectif
-----------------

Pour la création d’une nouvelle fonction Objectif, il faut créer une
classe qui contient, les méthodes getMin(), getMax(),et la formule de la
fonction Objectif.

        double f(const std::vector<double> params) const;
      

-   params les paramètres de la fonction

-   retourne l’image des paramètre par la fonction objectif

<!-- -->

        std::vector<double> getMin()const;
      

        std::vector<double> getMax()const;
      

Ces deux méthodes permettent respectivement de fournir les bornes min et
les bornes max de la fonction objectif correspondante.

Au vu de notre implémentation on peut créer des fonctions objectifs avec
autant de dimensions que l’on souhaite.

Constructeur Abeille
--------------------

    Abeille(F _obj, unsigned _nbFleurs, unsigned _iterationMaxParFleur,
        unsigned _maxIteration);

-   \_obj Objet contenant une fonction objectif f(vector\<double\> v),
    getMin() et getMax() pour donner les bornes de cette fonction

-   \_nbFleurs le nombre de fleur souhaité pour l’exécution de
    l’algorithme

-   \_iterationMaxParFleur le nombre de fois qu’une abeille observatrice
    passe sur une fleur avant de la laisser tomber

-   \_maxIteration le nombre d’itération total de l’algorithme

Constructeur Essaim
-------------------

       Essaim(F _obj, unsigned _nbParticules, unsigned _cArret);
      

-   \_obj Objet contenant une fonction objectif f(vector\<double\> v),
    getMin() et getMax() pour donner les bornes de cette fonction

-   \_nbParticules le nombre de particule souhaité pour l’exécution de
    l’algorithme

-   \_cArret la condition d’arrêt, c’est à dire le nombre maximum
    d’itération.

Solve
-----

-   solve : permet de lancer l’algorithme en parallélisant

-   solve(unsigned n) : permet de lancer l’algorithme en utilisant n
    threads.

-   solveMpi(const MpiBind &mpi) : parallélise en utilisant MPI, le
    résultat sera mis à jour dans l’objet du thread 0

<!-- -->

    Fschwefel<3> f;
    Abeille<Fschwefel<3>> e(f, 100, 1000, 10000);
    e.solveMpi(mpi); //Execution MPI
    if (mpi.getRank() == 0) {
    cout << "MPI :" << e << endl; //Resultat sur le thread 0
    }
    e.solve(3); //Execution parallele
    e.solve(1); //Execution non parallele

GetResultat
-----------

Permet de récupérer la position minimum de la fonction après l’exécution
de solve.

    std::vector<double> Abeille<F>::getResultat() const;

Flux de sortie \<\<
-------------------

Vous pouvez afficher le résultat sous la forme $F(x)=y$ en utilisant le
flux de sortie sur l’objet après avoir appliqué solve.

    Fschwefel<3> f;
    Abeille<Fschwefel<3>> e(f, 100, 1000, 10000);
    e.solve();
    cout << e << endl;

Exemple
-------

    Fbohachevsky f { };
    Abeille<Fbohachevsky> abeille(f,500,100,10000);
    abeille.testGenererFleur();

    Fbohachevsky f { };
    Essaim<Fbohachevsky> e(f,100,10000);
    e.testGenererFleur();

Exécution des tests
-------------------

Pour exécuter les test en utilisant openmp, il y a deux options possible
:

-   -a : exécute les tests sur les abeilles

-   -e : exécute les tests sur les essaims

<!-- -->

    $./Debug/projetgsi
        $./Debug/projetgsi -a
        $./Debug/projetgsi -e

Pour désactiver le multithreading, il faut mettre la variable
d’environnement OMP\_GET\_NUM\_THREADS à 1.\
Pour tester MPI :

        $mpirun -np 4 ./Debug/projetgsi

Tests expérimentaux
===================

Pour tester les différentes solutions de notre librairie, nous avons
utilisé différentes fonctions en 1,2 et 3 dimensions.

Les fonctions que nous avons testés ont beaucoup de variations et donc
beaucoup de minimums locaux, par exemple les deux fonctions suivantes.

<span>2</span>

![Fonction de Ackley](ackley.png)

![Fonction de Schwefel](schwefel.png)

![Fonction de Bohachevsky](boha.png)

Nous avons noté des différences entre les performances des 2
algorithmes, nous avons récapitulé ces différences dans le tableau que vous pouvez voir dans le fichier pdf.


La différence de précision entre les deux algorithmes est flagrante,
même pour une fonction assez simple comme la fonction carrée, on observe
une différence de 3 chiffres après la virgule.

Cette différence se maintient sur les 3 autres fonctions.

Néanmoins, même si il est difficile de comparer les temps d’exécution
car il dépend des différents paramètres de l’algorithme comme le nombre
d’itérations par exemple, on observe que l’algorithme des abeilles est à
peu près 2 fois plus rapide. Finalement, si l’on veut privilégier la
vitesse d’exécution, on peut utiliser l’algorithme des abeilles qui
donne quand même une bonne idée de la solution exacte.

Si l’on veut privilégier la précision, il faudra utiliser l’heuristique
des essaims qui renverra des résultats plus proches de la solution
exacte.

Conclusion 
==========

L’étude des comportements animaliers nous permet d’en déduire des
algorithmes pouvant être utilisés dans le cadre d’optimisation difficile
de fonctions dites objectifs. Après implémentation avec parallélisation
on peut en tirer plusieurs conclusions, l’algorithme des essaims
particulaires est plus optimal en terme de précision que l’algorithme
des Abeilles bien que ce dernier soit plus rapide. De la manière dont on
a implémenté la parallélisation, côté mpi ce n’est pas plus rapide mais
le résultat est un peu plus précis et côté openmp on observe une
exécution plus rapide remarquable.
