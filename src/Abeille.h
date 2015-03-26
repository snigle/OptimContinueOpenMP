/*
 * Abeille.h
 *
 *  Created on: Mar 24, 2015
 *      Author: eisti
 */

#ifndef ABEILLE_H_
#define ABEILLE_H_
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <random>

template <typename F>
class Abeille {
private:

    std::unique_ptr<std::vector<std::vector<double>>> pFleurs;
    std::unique_ptr<std::vector<double>> pFitnesses;
    std::unique_ptr<std::vector<int>> pIterations;
    F obj;
    unsigned nbFleurs;
    double fitness(std::vector<double>)const;
    unsigned dimension;
    void initVectors();
    void majFitnesses();
    std::vector<double> getVoisin(unsigned i);
public:
    Abeille(F _obj, unsigned _nbFleurs, unsigned dim);

    void solve();
};

template <typename F>
void Abeille<F>::majFitnesses() {
    for (unsigned i = 0; i < nbFleurs; ++i) {

    }
}

template<typename F>
double Abeille<F>::fitness(std::vector<double> fleur) const {
	double valFleur = obj.f(fleur);

	if(valFleur >= 0) return (1/(valFleur+1));
	else return (1+fabs(valFleur));

}

template<typename F>
std::vector<double> Abeille<F>::getVoisin(unsigned i) {
	std::vector<std::vector<double>> &fleurs = *pFleurs;

	unsigned aleaDimension;

	std::vector<double> fleur = genererFleur();
	std::vector<double> voisine = fleurs[i];
	aleaDimension = (unsigned) (rand()/(double)RAND_MAX)*dimension;

	voisine[aleaDimension] = voisine[aleaDimension]
					 + ((rand()/(double)RAND_MAX)*2-1)
					 * ( voisine[aleaDimension] - fleur[aleaDimension] );


    return 0.0;
}

template<typename F>
void Abeille<F>::initVectors() {
    std::vector<double>& fitnesses = *pFitnesses;
    std::vector<std::vector<double>>&fleurs = *pFleurs;
    std::vector<int>& iterations = *pIterations;


    std::vector<double> min = obj.getMin();
    std::vector<double> max = obj.getMax();

    if (min.size() != max.size()) {
        throw "Les min et le max de la fonction objectif ne renvoie pas un vecteur de même taille";
    }
    //Préparation des randoms uniformes.
    std::default_random_engine generator{};
    std::uniform_real_distribution<double> distribution(0, 1);
    std::vector<std::uniform_real_distribution<double>> distributionParticule(dimension);


    //Initialisation des fleurs et du nombre d'itérations par abeille.
    for (unsigned i = 0; i < nbFleurs; ++i) {
        fitnesses.push_back(0);
        iterations.push_back(0);

    }
    for (unsigned i = 0; i < dimension; ++i) {
        distributionParticule[i] = std::uniform_real_distribution<double>(min[i], max[i]);
    }
    //Initialisation des fleurs.
    for (unsigned i = 0; i < nbFleurs; ++i) {
        for (unsigned j = 0; j < min.size(); ++j) {
            double tmp = distributionParticule[j](generator);
            fleurs[i].push_back(tmp);
        }
    }

}

template<typename F>
Abeille<F>::Abeille(F _obj, unsigned _nbFleurs, unsigned _dim) : pFleurs(new std::vector<std::vector<double>>
{
})
,
pFitnesses(new std::vector<double>{}), obj(_obj), dimension {
    _dim
}, nbFleurs{_nbFleurs}
,
pIterations(new std::vector<int>{}) {
    initVectors();
    //	fleurs=*pFleurs;
    //	fitnesses=*pFitnesses;
    //	iterations=*pIterations;
}

template<typename F>
void Abeille<F>::solve() {
}

#endif /* ABEILLE_H_ */
