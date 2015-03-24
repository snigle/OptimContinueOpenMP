/*
 * Essaim.h
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#ifndef ESSAIM_H_
#define ESSAIM_H_
#include "Fcarre.h"
#include "../cute/cute_base.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>

template <typename F>
class Essaim {
private:

    F obj;
    double c1;
    double c2;

    unsigned nbParticules;
    unsigned cArret;

    unsigned dimension;

    std::vector<std::vector<double>> particules;
    //Cout minimal par particules
    std::vector<double> c;
    //Position du cout minimal
    std::vector<std::vector<double>> xp;
    //Cout minimal du voisinage d'une particule
    std::vector<double> cv;
    //Position du cout minimal du voisinage
    std::vector<std::vector<double>> xv;
    //Vitesse des particules
    std::vector<std::vector<double>> vitesse;

    std::vector<double> resultat;

public:

    /*Essaim(F& f, const double& d, const double& e, const int& i,
            const int& j) {
    }*/

    Essaim(F _obj, double _c1, double _c2, unsigned _nbParticules,
            unsigned _cArret);
    virtual ~Essaim();

    void solve();
    void initVectors();

    double coefConstriction(double rho1, double rho2);
    bool majVoisins(unsigned i);
    unsigned positionMinimumGlobal();

    void afficherParticules();
    void afficherMeilleurVoisin();

    void testMajVoisins();
    void testInit();

    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Essaim<U>& e);
};

template <typename F>
std::ostream& operator<<(std::ostream& out, const Essaim<F>& e);

template <typename F>
Essaim<F>::Essaim(F _obj, double _c1, double _c2, unsigned _nbParticules,
        unsigned _cArret) : obj(_obj),
c1(_c1), c2(_c2), nbParticules(_nbParticules), cArret(
_cArret), dimension(_obj.getMax().size()), particules(
std::vector<std::vector<double>>(_nbParticules)), c(
std::vector<double>(_nbParticules)), xp(
std::vector<std::vector<double>>(_nbParticules)), cv(
std::vector<double>(_nbParticules)), xv(
std::vector<std::vector<double>>(_nbParticules)), vitesse(
std::vector<std::vector<double>>(_nbParticules)),
resultat(std::vector<double>(_obj.getMax().size())) {
}

template <typename F>
Essaim<F>::~Essaim() {

}

template <typename F>

void Essaim<F>::initVectors() {
    std::vector<double> min = obj.getMin();
    std::vector<double> max = obj.getMax();

    if (min.size() != max.size()) {
        std::cerr
                << "Les min et le max de la fonction objectif ne renvoie pas un vecteur de même taille"
                << std::endl;
    }

    //Préparation des rands uniform
    std::default_random_engine generator{};
    std::uniform_real_distribution<double> distribution(0, 1);
    std::vector<std::uniform_real_distribution<double>> distributionParticule(
            dimension);
    for (unsigned j = 0; j < dimension; ++j) {
        distributionParticule[j] = std::uniform_real_distribution<double>(min[j],
                max[j]);
    }

    for (unsigned i = 0; i < nbParticules; ++i) {
        particules[i] = std::vector<double>(min.size());
        vitesse[i] = std::vector<double>(min.size());
        for (unsigned j = 0; j < min.size(); ++j) {
            particules[i][j] = distributionParticule[j](generator);
            vitesse[i][j] = distribution(generator);
        }
        c[i] = obj.f(particules[i]);
        xp[i] = particules[i];

        c[i] = std::numeric_limits<double>::max();
        cv[i] = c[(i + 1) % nbParticules];
    }

    for (unsigned i = 0; i < nbParticules; ++i) {
        xv[i] = particules[(i + 1) % nbParticules];
        cv[i] = c[(i + 1) % nbParticules];
        majVoisins(i);
    }
}

template <typename F>

void Essaim<F>::solve() {
    double c1, c2, r1, r2, rho1, rho2;
    //double somVitesse = 0;

    unsigned compteur = 0;
    c1 = 1.5;
    c2 = 2;
    do {
        for (unsigned i = 0; i < nbParticules; ++i) {
            if (obj.f(particules[i]) < c[i]) {
                c[i] = obj.f(particules[i]);
                xp[i] = particules[i];
            }
            majVoisins(i);
        }
        for (unsigned i = 0; i < nbParticules; ++i) {
            //do{
            r1 = rand() / (double) RAND_MAX;
            r2 = rand() / (double) RAND_MAX;
            rho1 = c1 * r1;
            rho2 = c2 * r2;
            //}while( rho1 + rho2 <= 4 );
            for (unsigned j = 0; j < dimension; ++j) {
                double var = vitesse[i][j];
                double var2 = xp[i][j];
                double var3 = xv[i][j];
                double var4 = particules[i][j];
                vitesse[i][j] = coefConstriction(rho1, rho2)*(vitesse[i][j] + rho1 * (xp[i][j] - particules[i][j]) + rho2 * (xv[i][j] - particules[i][j]));
                particules[i][j] = particules[i][j] + vitesse[i][j];
                //somVitesse += vitesse[i][j];
            }

        }
        compteur++;
        if (compteur % 100 == 0) {
            resultat = xp[positionMinimumGlobal()];
            std::cout << *this << std::endl;
        }
    } while (compteur < cArret);

    resultat = xp[positionMinimumGlobal()];

}

template <typename F>

unsigned Essaim<F>::positionMinimumGlobal() {
    unsigned best_position;
    double best_val;
    best_position = 0;
    best_val = c[0];
    for (unsigned i = 1; i < dimension; ++i) {
        if (best_val >= c[i]) {
            best_position = i;
            best_val = c[i];
        }
    }
    return best_position;
}

template <typename F>

double Essaim<F>::coefConstriction(double rho1, double rho2) {
    double rho;
    rho = rho1 + rho2;
    return (1 - (1 / (rho)) + (sqrt(fabs(pow(rho, 2) - 4 * rho)) / 2));
}

template <typename F>

bool Essaim<F>::majVoisins(unsigned i) {
    bool majEffectue{false};

    // Topologie anneau
    unsigned v1{i - 1};
    unsigned v2{i + 1};
    if (i == 0)
        v1 = nbParticules - 1;
    if (v2 == nbParticules)
        v2 = 0;

    if (obj.f(particules[v1]) < cv[i]) {
        cv[i] = obj.f(particules[v1]);
        xp[i] = particules[v1];
        majEffectue = true;
    }
    if (obj.f(particules[v2]) < cv[i]) {
        cv[i] = obj.f(particules[v2]);
        xp[i] = particules[v2];
        majEffectue = true;
    }
    return majEffectue;
}

template <typename F>

void Essaim<F>::afficherParticules() {
    for (unsigned i = 0; i < nbParticules; ++i) {
        std::cout << "(";
        for (unsigned j = 0; j < dimension; ++j) {
            std::cout << particules[i][j] << ", ";
        }
        std::cout << ")" << std::endl;
    }
}

template <typename F>


void Essaim<F>::afficherMeilleurVoisin() {
}

template <typename FonctionObjetctif>
void Essaim<FonctionObjetctif>::testMajVoisins() {
    majVoisins(0);

    ASSERT(cv[0] < c[nbParticules - 1]);
    ASSERT(cv[0] < c[1]);
    for (unsigned i = 1; i < nbParticules - 1; ++i) {
        majVoisins(i);
        ASSERT(cv[i] < c[i - 1]);
        ASSERT(cv[i] < c[i + 1]);
    }
    majVoisins(nbParticules - 1);
    ASSERT(cv[nbParticules - 1] < c[0]);
    ASSERT(cv[nbParticules - 1] < c[nbParticules - 1 - 1]);



}

template <typename FonctionObjetctif>
void Essaim<FonctionObjetctif>::testInit() {
    std::vector<double> min = obj.getMin();
    std::vector<double> max = obj.getMax();
    for (unsigned i = 0; i < nbParticules; ++i) {
        for (unsigned j = 0; j < dimension; ++j) {
            ASSERT(particules[i][j] < max && particules[i][j] >= min);
            ASSERT(xp[i][j] == particules[i][j]);
        }
    }

}

template <typename F>
std::ostream& operator<<(std::ostream& out, const Essaim<F>& e) {
    out << "F(";
    for (unsigned i = 0; i < e.dimension; ++i) {
        out << e.resultat[i] << ",";
    }
    out << ") = " << e.obj.f(e.resultat) << std::endl;
    return out;
}

#endif /* ESSAIM_H_ */
