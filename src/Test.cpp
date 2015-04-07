#include "mpi-bind.h"
#include "../cute/cute.h"
#include "../cute/ide_listener.h"
#include "../cute/xml_listener.h"
#include "../cute/cute_runner.h"
#include "Fcarre.h"
#include "Essaim.h"
#include <iostream>
#include "Abeille.h"
#include"Fbohachevsky.h"
#include"Fackley.h"
#include "Abeille.h"
#include "Fschwefel.h"
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;
//////////////////////////////////Tests pour l'heuristique des abeilles//////////////////

void testAbeilleGenererFleur() {
	ASSERTM(
			"Vérifie que la fleur est bien dans les limites de l'espace de recherche",
			true);
	Fbohachevsky f { };
	Abeille<Fbohachevsky> abeille(f, 500, 100, 10000);
	abeille.testGenererFleur();
}

void testAbeillF_carre() {
	ASSERTM(
			"Test de résolution de la fonciton fcarré avec l'heuristique des abeilles",
			true);
	F_carre f { };
	Abeille<F_carre> abeille(f, 500, 100, 10000);
	abeille.testInitFleurs();
	abeille.solve();

	cout << abeille << endl;
	//On regarde si la solution trouvée est bien inférieure à un seuil.
	ASSERT(std::abs(abeille.getResultat()[0]) < 0.01);
}

void testAbeillFackley() {
	ASSERTM(
			"Test de résolution de la fonction de ackley avec l'heuristique des abeilles (2 dimensions)",
			true);
	Fackley f { };
	Abeille<Fackley> abeille(f, 500, 100, 10000);
	abeille.solve();
	cout << abeille << endl;

	std::vector<double> resultats = abeille.getResultat();
	//On regarde pour chaque dimension si la différence entre le résultat et le résultat attendu  est inférieur à un seuil.
	for (unsigned i = 0; i < resultats.size(); ++i) {
		ASSERT(abs(resultats[i]) < 0.1);
	}

}

void testAbeillFbohachevsky() {
	ASSERTM(
			"Test de résolution de la fonction de bohachevsky avec l'heuristique des abeilles (2 dimensions)",
			true);
	Fbohachevsky f { };
	Abeille<Fbohachevsky> abeille(f, 500, 100, 10000);
	abeille.solve();
	cout << abeille << endl;

	std::vector<double> resultats = abeille.getResultat();
	//On regarde pour chaque dimension si la différence entre le résultat et le résultat attendu est inférieur à un seuil.
	for (unsigned i = 0; i < resultats.size(); ++i) {
		ASSERT(std::abs(resultats[i]) < 0.1);
	}
}

void testAbeilleFschwefel() {
	ASSERTM(
			"Test de résolution de la fonction de schewefel avec l'heuristique des abeilles (3 dimensions)",
			true);
	Fschwefel<3> f;
	Abeille<Fschwefel<3>> abeille(f, 500, 1000, 10000);
	abeille.solve();
	cout << abeille << endl;

	std::vector<double> resultats = abeille.getResultat();
	//On regarde pour chaque dimension si la différence entre le résultat et le résultat attendu est inférieur à un seuil.
	for (unsigned i = 0; i < resultats.size(); ++i) {
		ASSERT(std::abs(420.9687 - resultats[i]) < 5);
	}

}

//////////////////////////////////Tests pour l'heuristique des abeilles//////////////////


void EssaimMajVoisin() {
	ASSERTM("tests pour la mise à jour des voisins", true);
	Fackley f;
	Essaim<Fackley> e(f, 100, 10);
	e.testMajVoisins();
}

void EssaimInitVectors() {
	ASSERTM("tests pour l'initialisation des vecteurs", true);
	Fbohachevsky f;
	Essaim<Fbohachevsky> e(f, 100, 10);
	e.testMajVoisins();
}

void testEssaimFcarre() {
	F_carre f;
	Essaim<F_carre> e(f, 1000, 1000);
	e.solve();
	cout << e << endl;

	std::vector<double> resultats = e.getResultat();
	//On regarde pour chaque dimension si le résultat est inférieur à un seuil.
	for (unsigned i = 0; i < resultats.size(); ++i) {
		ASSERT(abs(resultats[i] < 0.0001));
	}

}

void testEssaimAckley() {
	Fackley f;
	Essaim<Fackley> e(f, 1000, 1000);
	e.solve();
	cout << e << endl;

	std::vector<double> resultats = e.getResultat();
	//On regarde pour chaque dimension si le résultat est inférieur à un seuil.
	for (unsigned i = 0; i < resultats.size(); ++i) {
		ASSERT(abs(resultats[i] < 0.01));
	}

}

void testEssaimBohachevsky() {
	Fbohachevsky f;
	Essaim<Fbohachevsky> e(f,  1000, 1000);
	e.solve();
	cout << e << endl;

	std::vector<double> resultats = e.getResultat();
	//On regarde pour chaque dimension si le résultat est inférieur à un seuil.
	for (unsigned i = 0; i < resultats.size(); ++i) {
		ASSERT(abs(resultats[i] < 0.01));
	}

}

void testEssaimFschwefel() {
	Fschwefel<3> f;
	Essaim<Fschwefel<3>> essaim(f, 500, 10000);
	essaim.solve();
	std::cout << essaim << std::endl;

	std::vector<double> resultats = essaim.getResultat();
	//On regarde pour chaque dimension si le résultat est inférieur à un seuil.
	for (unsigned i = 0; i < resultats.size(); ++i) {
		ASSERT(abs(420.9687 - resultats[i] < 0.01));
	}
}

void init() {
	ASSERTM("start writing tests", true);
}

void runAllTests(int argc, char *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(init));
	if (argc == 2) {
		//Test avec les abeilles.
		if (strcmp(argv[1], "-a") == 0) {
			s.push_back(CUTE(testAbeilleGenererFleur));
			s.push_back(CUTE(testAbeillF_carre));
			s.push_back(CUTE(testAbeillFackley));
			s.push_back(CUTE(testAbeillFbohachevsky));
			s.push_back(CUTE(testAbeilleFschwefel));
		}
		//Test avec les essaims.
		if (strcmp(argv[1], "-e") == 0) {
			s.push_back(CUTE(EssaimMajVoisin));
			s.push_back(CUTE(EssaimInitVectors));
			s.push_back(CUTE(testEssaimFcarre));
			s.push_back(CUTE(testEssaimAckley));
			s.push_back(CUTE(testEssaimBohachevsky));
			s.push_back(CUTE(testEssaimFschwefel));

		}
	}
	cute::xml_file_opener xmlfile(1, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, 1, argv)(s, "AllTests");
}

int main(int argc, char** argv) {
	try {
		MpiBind mpi(argc, argv);
//		Dans le cas où on n'est pas en parallèle
		if (mpi.getSize() == 1) {
			runAllTests(argc, argv);
		} else {

			//Résolution de la fonction schwefel avec l'heuristique des abeilles et mpi.
			Fschwefel<3> f;
			Abeille<Fschwefel<3>> e(f, 100, 1000, 10000);
			e.solveMpi(mpi);
			if (mpi.getRank() == 0) {
				cout << "MPI :" << e << endl;
			}
			//Résolution de la fonctions schwefel avec l'heuristique des essaims et mpi.
			Fschwefel<3> fs;
			Essaim<Fschwefel<3>> essaim(fs, 500, 10000);
			essaim.solveMpi(mpi);
			if (mpi.getRank() == 0) {
				cout << "MPI :" << essaim << endl;
			}

		}
	} catch (const char *ex) {
		std::cerr << ex << std::endl;
		return 1;

	}

	//initEssaim();
	return 0;
}

