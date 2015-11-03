##Optimisation difficile pour des problème à variable continue##

Dans le cadre de notre 3ème semestre de cycle ingénieur, il a été proposé
aux élèves du parcours GSI un projet dont le but est de créer une librairie per-
mettant d’effectuer une optimisation difficile pour des problèmes à variable
continue.

Le but de cette librairie est de trouver la solution à des fonctions difficiles
en un temps réduit.
Pour mener à bien ce projet et résoudre ces problèmes, il nous a été
proposé des heuristiques qui sont des méthodes pour trouver des solutions à
des problèmes difficiles.

1.Dépendances
 Pour compiler le programme, g++-4.9 est nécessaire ainsi que la librairie openmpi
 
 
 Pour installer g++ sur ubuntu :
 
 $sudo add-apt-repository ppa:ubuntu-toolchain-r/test
 $sudo apt-get update
 $sudo apt-get install gcc-4.9 g++-4.9
 $sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9

 Pour installer openmpi :
 $sudo apt-get install libopenmpi-dev


2.Compiler
 $make
 
3.Exécuter :
 $./Debug/projetgsi //Tous les tests
 $./Debug/projetgsi -a //Pour les abeilles
 $./Debug/projetgsi -e //Pour Essaims
 $mpirun -np 4 ./Debug/projetgsi

Plus d'informations dans le rapport
