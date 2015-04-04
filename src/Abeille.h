/*
 * Abeille.h
 *
 *  Created on: Mar 24, 2015
 *      Author: eisti
 */

#ifndef ABEILLE_H_
#define ABEILLE_H_
#include "mpi-bind.h"
#include <omp.h>
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <random>
#include "../cute/cute_base.h"

template <typename F>
class Abeille {
private:

    std::unique_ptr<std::vector<std::vector<double>>> pFleurs;
    std::unique_ptr<std::vector<double>> pFitnesses;
    std::unique_ptr<std::vector<unsigned>> pIterations;
    F obj;
    unsigned maxIterations;
    unsigned nbFleurs;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution/*(0, 1)*/;
    std::vector<std::uniform_real_distribution<double>> distributionParticule/*(dimension)*/;

    unsigned dimension;
    std::uniform_int_distribution<unsigned> distributionDimension;
    std::uniform_real_distribution<double>distributionVoisin;

    std::vector<double> posResultat;



    double fitness(std::vector<double>)const;
    void initVectors();
    void majFitnesses();
    std::vector<double> getVoisin(unsigned i);
    std::vector<double> genererFleur();
public:
    Abeille(F _obj, unsigned _nbFleurs, unsigned _max);

    void solve();
    void solve(unsigned nbThread);
    void solveMpi(const MpiBind &mpi);
    void testInitFleurs()const;
    void testGenererFleur();
    std::vector<double> getResultat()const;
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Abeille<U>& e);
};

template<typename U>
std::ostream& operator<<(std::ostream& out, const Abeille<U>& e);

template<typename F>
Abeille<F>::Abeille(F _obj, unsigned _nbFleurs, unsigned _max) :
pFleurs(new std::vector<std::vector<double> >(_nbFleurs))
, pFitnesses(new std::vector<double>(_nbFleurs))
, pIterations(new std::vector<unsigned>(_nbFleurs))
, obj(_obj)
, maxIterations(_max)
, nbFleurs(_nbFleurs)
, generator(std::time(nullptr))
, distribution(0, _nbFleurs - 1)
, distributionParticule(_obj.getMax().size())
, dimension(_obj.getMax().size())
, distributionDimension(0, dimension - 1)
, distributionVoisin(-1, 1) {

    for (unsigned i = 0; i < dimension; ++i) {
        distributionParticule[i] = std::uniform_real_distribution<double>(obj.getMin()[i], obj.getMax()[i]);
    }

    initVectors();
    //	fleurs=*pFleurs;
    //	fitnesses=*pFitnesses;
    //	iterations=*pIterations;
}

template <typename F>
std::vector<double> Abeille<F>::genererFleur() {
    std::vector<double> fleur(dimension);

    for (unsigned j = 0; j < dimension; ++j) {
        double tmp = distributionParticule[j](generator);
        fleur[j] = tmp;
    }
    return fleur;
}

template <typename F>
void Abeille<F>::majFitnesses() {
    std::vector<std::vector<double>>&fleurs = *pFleurs;
    std::vector<double>& fitnesses = *pFitnesses;
    std::vector<unsigned> iterations = *pIterations;

#pragma omp parallel for
    for (unsigned i = 0; i < nbFleurs; ++i) {
        if (iterations[i] > maxIterations) {
            iterations[i] = 0;
            fleurs[i] = genererFleur();

        }
    }
#pragma omp parallel for
    for (unsigned i = 0; i < nbFleurs; ++i) {
        if (iterations[i] > maxIterations) {
            iterations[i] = 0;
            fleurs[i] = genererFleur();

        }
        std::vector<double> voisin = getVoisin(i);
        fitnesses[i] = fitness(voisin);
    }
}

template<typename F>
double Abeille<F>::fitness(std::vector<double> fleur) const {
    double valFleur = obj.f(fleur);

    if (valFleur >= 0) return (1 / (valFleur + 1));
    else return (1 + fabs(valFleur));

}

template<typename F>
std::vector<double> Abeille<F>::getVoisin(unsigned i) {
    std::vector<std::vector<double>> &fleurs = *pFleurs;

    unsigned aleaDimension{};

    std::vector<double> voisine = fleurs[i];
    aleaDimension = distributionDimension(generator);
    unsigned positionAleatoire = distribution(generator);
    voisine[aleaDimension] = voisine[aleaDimension]
            + distributionVoisin(generator)
            * (voisine[aleaDimension] - fleurs[positionAleatoire][aleaDimension]);

    return voisine;
}

template<typename F>
void Abeille<F>::initVectors() {
    std::vector<std::vector<double>>&fleurs = *pFleurs;

    std::vector<double> min = obj.getMin();
    std::vector<double> max = obj.getMax();

    if (min.size() != max.size()) {
        throw "Les min et le max de la fonction objectif ne renvoie pas un vecteur de même taille";
    }
    //Initialisation des fleurs.

    for (unsigned i = 0; i < nbFleurs; ++i) {
        fleurs[i] = genererFleur();
    }
}

template<typename F>
void Abeille<F>::solve(unsigned nbThread) {
    omp_set_num_threads(nbThread);
    std::vector<double>& fitnesses = *pFitnesses;
    std::vector<std::vector<double>>&fleurs = *pFleurs;
    std::vector<unsigned>& iterations = *pIterations;

    posResultat = fleurs[0];

    for (long unsigned i = 0; i < 10000; ++i) {
        majFitnesses();
#pragma omp parallel for
        for (unsigned scout = 0; scout < nbFleurs; ++scout) {
            unsigned position = distribution(generator);
            if (position % omp_get_num_threads() == omp_get_thread_num()) {
                std::vector<double>& fleur = fleurs[position];
                std::vector<double> voisin = genererFleur();
                iterations[position]++;
                if (fitnesses[position] < fitness(voisin)) {
                    fleur = voisin;
                    iterations[position] = 0;
                    if (fitness(posResultat) < fitness(voisin)) {
                        posResultat = voisin;
                    }
                }
            }
        }
    }

}

template <typename F>
void Abeille<F>::solve() {
    solve(omp_get_max_threads());
}

template <typename F>
void Abeille<F>::solveMpi(const MpiBind &mpi) {
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

template<typename F>
void Abeille<F>::testInitFleurs() const {
    ASSERTM("Test sur l'initialisation des fleurs", true);
    std::vector<double> min = obj.getMin();
    std::vector<double> max = obj.getMax();
    std::vector<std::vector<double>>&fleurs = *pFleurs;
    //Tests pour les itérations.
    std::vector<unsigned>& iterations = *pIterations;
    ASSERT(fleurs.size() == nbFleurs);

    for (unsigned i = 0; i < nbFleurs; ++i) {
        ASSERT(iterations[i] == 0);
        for (unsigned j = 0; j < dimension; ++j) {
            ASSERT(fleurs[i][j] < max[j] && fleurs[i][j] > min[j]);
        }


    }
}

template<typename F>
void Abeille<F>::testGenererFleur() {
    std::vector<double> min = obj.getMin();
    std::vector<double> max = obj.getMax();
    auto fleur = genererFleur();
    for (unsigned i = 0; i < dimension; ++i) {
        ASSERT(fleur[i] < max[i] && fleur[i] > min[i]);
    }


}

template <typename F>
std::ostream& operator<<(std::ostream& out, const Abeille<F>& e) {
    out << "F(";
    for (unsigned i = 0; i < e.dimension; ++i) {
        out << e.posResultat[i] << ",";
    }
    out << ") = " << e.obj.f(e.posResultat) << std::endl;
    return out;
}

template<typename F>
std::vector<double> Abeille<F>::getResultat() const {

	return posResultat;
}

//TODO finir tous les tests.

#endif /* ABEILLE_H_ */
