/*
 * Essaim.h
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#ifndef ESSAIM_H_
#define ESSAIM_H_
#include "mpi-bind.h"
#include <omp.h>
#include "Fcarre.h"
#include "../cute/cute_base.h"
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <random>

template<typename F>

class Essaim {
private:

	F obj;

	unsigned nbParticules;
	unsigned cArret;

	unsigned dimension;

	std::unique_ptr<std::vector<std::vector<double>>>pparticules;
	//Cout minimal par particules
	std::unique_ptr<std::vector<double>> pc;
	//Position du cout minimal
	std::unique_ptr<std::vector<std::vector<double>>> pxp;
	//Cout minimal du voisinage d'une particule
	std::unique_ptr<std::vector<double>> pcv;
	//Position du cout minimal du voisinage
	std::unique_ptr<std::vector<std::vector<double>>> pxv;
	//Vitesse des particules
	std::unique_ptr<std::vector<std::vector<double>>> pvitesse;

	std::vector<double> posResultat;

	//Préparation des rands uniform
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution;
	std::uniform_real_distribution<double> distributionC1;
	std::vector<std::uniform_real_distribution<double>> distributionParticule;

public:

    Essaim(F _obj, unsigned _nbParticules,
            unsigned _cArret);
    virtual ~Essaim();

	void solve(unsigned nbThread);
	void solve();
	void solveMpi(const MpiBind &mpi);
	void initVectors();
	void majVoisins(unsigned i);
	void afficherParticules();
	std::vector<double> getResultat();

    void testMajVoisins();
    void testInit();

	template<typename U>
	friend std::ostream& operator<<(std::ostream& out, const Essaim<U>& e);

};

template<typename F>
std::ostream& operator<<(std::ostream& out, const Essaim<F>& e);

template<typename F>
Essaim<F>::Essaim(F _obj, unsigned _nbParticules,

	unsigned _cArret) :
		obj(_obj), nbParticules(_nbParticules),
		cArret(_cArret),
		dimension(_obj.getMax().size()),
		pparticules( new std::vector<std::vector<double>>(_nbParticules) ),
		pc( new std::vector<double>(_nbParticules) ),
		pxp( new std::vector<std::vector<double>>(_nbParticules) ),
		pcv( new std::vector<double>(_nbParticules) ),
		pxv( new std::vector<std::vector<double>>(_nbParticules) ),
		pvitesse( new std::vector<std::vector<double>>(_nbParticules) ),
		posResultat( std::vector<double>(_obj.getMax().size()) ),
		generator( std::time(nullptr) ),
		distribution(0, 1), distributionC1(0.8,1.2),
		distributionParticule( _obj.getMax().size() ) {

			const std::vector<double> min = obj.getMin();
			const std::vector<double> max = obj.getMax();
			for (unsigned j = 0; j < dimension; ++j) {
				distributionParticule[j] = std::uniform_real_distribution<double>( min[j], max[j] );
			}
			initVectors();

}

template<typename F>
Essaim<F>::~Essaim() {

}

template<typename F>
std::vector<double> Essaim<F>::getResultat() {
    return posResultat;
}


/* initVectors(): Initialise les attributs de la classe Essaim*/
template<typename F>
void Essaim<F>::initVectors() {

    std::vector<double> min = obj.getMin();
    std::vector<double> max = obj.getMax();
    std::vector<std::vector<double>>&particules = *pparticules;
    std::vector<std::vector<double>>&xp = *pxp;
    std::vector<std::vector<double>>&vitesse = *pvitesse;
    std::vector<double>& c = *pc;
    std::vector<std::vector<double>>&xv = *pxv;
    std::vector<double>& cv = *pcv;

    if (min.size() != max.size()) {
        std::cerr
                << "Les min et le max de la fonction objectif ne renvoie pas un vecteur de même taille"
                << std::endl;
    }

    for (unsigned i = 0; i < nbParticules; ++i) {
        for (unsigned j = 0; j < min.size(); ++j) {
            double tmp = distributionParticule[j](generator);
            particules[i].push_back(tmp);
            xp[i].push_back(tmp);
            tmp = distribution(generator);
            vitesse[i].push_back(tmp);
        }
        c[i] = obj.f(particules[i]);
    }

    for (unsigned i = 0; i < nbParticules; ++i) {
        xv[i] = particules[(i + 1) % nbParticules];
        cv[i] = c[(i + 1) % nbParticules];
        majVoisins(i);
    }
}

/* solve(unsigned nbThread): determine le minimum de la fonction objectif,
 * en utilisant un certain nombre de Thread "nbThread" pour la parallelisation avec omp,
 * le resultat sera stocke dans l'attribut "posResultat" */
template<typename F>
void Essaim<F>::solve(unsigned nbThread) {

	omp_set_num_threads(nbThread);
	double R;
	double Fi;
	std::vector<double> min = obj.getMin();
	std::vector<double> max = obj.getMax();
	std::vector<std::vector<double>>&particules = *pparticules;
	std::vector<std::vector<double>>&xp = *pxp;
	std::vector<std::vector<double>>&vitesse = *pvitesse;
	std::vector<double>& c = *pc;
	std::vector<std::vector<double>>&xv = *pxv;
	std::vector<double>& cv = *pcv;

	double valResultat { c[0] };
	posResultat = particules[0];

	unsigned compteur = 0;

	do {

#pragma omp parallel
        {
            double valResultatLocal{c[0]};
            std::vector<double> posResultatLocal = particules[0];
#pragma omp for
			for (unsigned i = 0; i < nbParticules; ++i) {
				Fi = obj.f(particules[i]);
				if (Fi < c[i]) {
					c[i] = Fi;
					xp[i] = particules[i];
					if (valResultatLocal > c[i]) {        //Local
						valResultatLocal = c[i];
						posResultatLocal = xp[i];
					}
				}
				majVoisins(i);
			}

#pragma omp critical
            {
                if (valResultatLocal < valResultat) {
                    valResultat = valResultatLocal;
                    posResultat = posResultatLocal;
                }
            }

#pragma omp for
			for (unsigned i = 0; i < nbParticules; ++i) {

				R = distribution(generator);

				for (unsigned j = 0; j < dimension; ++j) {

					double c1 = distributionC1(generator);
					vitesse[i][j] = c1 * (vitesse[i][j])
							+ R * ( xp[i][j] - particules[i][j] )
							+ (1 - R) * ( xv[i][j] - particules[i][j] );
					double nouvellePosition = particules[i][j] + vitesse[i][j];
					if (nouvellePosition > min[j]
							&& nouvellePosition < max[j]) {
						particules[i][j] = nouvellePosition;
					} else {
						vitesse[i][j] = 0;
					}
				}
			}
		}
		compteur++;
	} while (compteur < cArret);
}

/* solve(): determine le minimum de la fonction objectif en utilisant les parametres de base*/
template<typename F>
void Essaim<F>::solve() {
    solve(omp_get_max_threads());
}

/* solveMpi(const MpiBind &mpi): determine le minimum de la fonction objectif,
 * en utilisant la parallelisation MPI*/
template<typename F>
void Essaim<F>::solveMpi(const MpiBind &mpi) {
    this->solve(1);
    std::vector<double> localRes = posResultat;
    //    std::cout << "Local :" << *this << std::endl;
    if (mpi.getRank() == 0) {

        for (unsigned i = 1; i < mpi.getSize(); ++i) {
            mpi.recv(localRes, i);
            if (obj.f(localRes) < obj.f(posResultat)) {
                posResultat = localRes;
            }
        }
    } else {

        mpi.send(localRes, 0);
    }
}

/* majVoisins(unsigned i): met à jour les deux voisins (vu qu'on a choisi la topologie en anneau)
 * de la particule i
 * c'est à dire la mise à jour des attributs "cv" et "xv" */
template<typename F>
void Essaim<F>::majVoisins(unsigned i) {

	std::vector<double> min = obj.getMin();
	std::vector<double> max = obj.getMax();
	std::vector<std::vector<double>>&particules = *pparticules;
	std::vector<std::vector<double>>&xp = *pxp;
	std::vector<std::vector<double>>&vitesse = *pvitesse;
	std::vector<double>& c = *pc;
	std::vector<std::vector<double>>&xv = *pxv;
	std::vector<double>& cv = *pcv;

	// Topologie anneau
	unsigned v1 { i - 1 };
	unsigned v2 { i + 1 };

	if (i == 0) v1 = nbParticules - 1;
	if (v2 == nbParticules) v2 = 0;

	double f_v1 = obj.f(particules[v1]);
	double f_v2 = obj.f(particules[v2]);

	if ( f_v1 < cv[i]) {
		cv[i] = f_v1;
		xv[i] = particules[v1];
	}
	if ( f_v2 < cv[i]) {
		cv[i] = f_v2;
		xv[i] = particules[v2];
	}

}

/* afficherParticules(): permet d'afficher toutes les particules,
 * positions et valeurs avec leurs voisinages*/
template<typename F>
void Essaim<F>::afficherParticules() {
	std::vector<double> min = obj.getMin();
	std::vector<double> max = obj.getMax();
	std::vector<std::vector<double>>&particules = *pparticules;
	std::vector<std::vector<double>>&xp = *pxp;
	std::vector<std::vector<double>>&vitesse = *pvitesse;
	std::vector<double>& c = *pc;
	std::vector<std::vector<double>>&xv = *pxv;
	std::vector<double>& cv = *pcv;
	std::cout << "p: | ";
	for (unsigned i = 0; i < nbParticules; ++i) {
		for (unsigned j = 0; j < dimension; ++j) {
			std::cout << particules[i][j] << " , ";
		}
		std::cout << "|";
	}
	std::cout << std::endl;

	std::cout << "xp: | ";
	for (unsigned i = 0; i < nbParticules; ++i) {

		for (unsigned j = 0; j < dimension; ++j) {
			std::cout << xp[i][j] << " , ";
		}
		std::cout << "|";

	}
	std::cout << std::endl;

	std::cout << "c: | ";
	for (unsigned i = 0; i < nbParticules; ++i) {

		std::cout << c[i] << " | ";

	}
	std::cout << std::endl;

	std::cout << "xv: | ";
	for (unsigned i = 0; i < nbParticules; ++i) {

		for (unsigned j = 0; j < dimension; ++j) {
			std::cout << xv[i][j] << " , ";
		}
		std::cout << "|";
	}
	std::cout << std::endl;

	std::cout << "v: | ";
	for (unsigned i = 0; i < nbParticules; ++i) {

		for (unsigned j = 0; j < dimension; ++j) {
			std::cout << vitesse[i][j] << " , ";
		}
		std::cout << "|";
	}
	std::cout << std::endl << "----------------------------------" << std::endl;
}

/* testMajVoisins(): permet de tester la méthode majVoisins(unsigned i) */
template<typename FonctionObjetctif>
void Essaim<FonctionObjetctif>::testMajVoisins() {
    std::vector<double> min = obj.getMin();
    std::vector<double> max = obj.getMax();
    std::vector<std::vector<double>>&particules = *pparticules;
    std::vector<std::vector<double>>&xp = *pxp;
    std::vector<std::vector<double>>&vitesse = *pvitesse;
    std::vector<double>& c = *pc;
    std::vector<std::vector<double>>&xv = *pxv;
    std::vector<double>& cv = *pcv;

    majVoisins(0);

    ASSERT(cv[0] <= c[nbParticules - 1]);
    ASSERT(cv[0] <= c[1]);
    for (unsigned i = 1; i < nbParticules - 1; ++i) {
        majVoisins(i);
        ASSERT(cv[i] <= c[i - 1]);
        ASSERT(cv[i] <= c[i + 1]);
    }
    majVoisins(nbParticules - 1);
    ASSERT(cv[nbParticules - 1] <= c[0]);
    ASSERT(cv[nbParticules - 1] <= c[nbParticules - 1 - 1]);
}

/* testInit(): permet de tester la méthode d'initialisation initVectors()*/
template<typename FonctionObjetctif>
void Essaim<FonctionObjetctif>::testInit() {
    std::vector<double> min = obj.getMin();
    std::vector<double> max = obj.getMax();
    std::vector<std::vector<double>>&particules = *pparticules;
    std::vector<std::vector<double>>&xp = *pxp;
    std::vector<std::vector<double>>&vitesse = *pvitesse;
    std::vector<double>& c = *pc;
    std::vector<std::vector<double>>&xv = *pxv;
    std::vector<double>& cv = *pcv;

    ASSERT(vitesse.size() == nbParticules);
    ASSERT(particules.size() == nbParticules);
    for (unsigned i = 0; i < nbParticules; ++i) {
        ASSERT(vitesse[i].size() == dimension);
        for (unsigned j = 0; j < dimension; ++j) {
            ASSERT(particules[i][j] < max[j] && particules[i][j] >= min[j]);
            ASSERT(xp[i][j] == particules[i][j]);
        }
    }
}

/* Redéfini l'opérateur << pour la classe Essaim */
template<typename F>
std::ostream& operator<<(std::ostream& out, const Essaim<F>& e) {
    out << "F(";
    for (unsigned i = 0; i < e.dimension; ++i) {
        out << e.posResultat[i] << ",";
    }
    out << ") = " << e.obj.f(e.posResultat) << std::endl;
    return out;
}

#endif /* ESSAIM_H_ */
