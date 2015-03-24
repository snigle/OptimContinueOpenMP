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
	std::unique_ptr<std::vector<double>> pFleurs;
	std::unique_ptr<std::vector<double>> pFitnesses;
	std::unique_ptr<std::vector<int>> pIterations;
	std::vector<double>& fleurs;
	std::vector<double>& fitnesses;
	std::vector<int>& iterations;
	F obj;
	unsigned nbFleurs;
	double fitness()const;
	unsigned dimension;
	void initVectors();

public :
	Abeille(F _obj,unsigned _nbFleurs,unsigned dim);

	void solve();
};

template<typename F>
inline double Abeille<F>::fitness() const {
}

template<typename F>
inline void Abeille<F>::initVectors() {

	for(unsigned i=0;i<nbFleurs;++i){
		iterations.push_back(0);
		std::vector<double> min = obj.getMin();
		std::vector<double> max = obj.getMax();

		if (min.size() != max.size()) {
			throw "Les min et le max de la fonction objectif ne renvoie pas un vecteur de même taille";
		}
		//Préparation des randoms uniformes.
		std::default_random_engine generator { };
		std::uniform_real_distribution<double> distribution(0, 1);
		std::vector<std::uniform_real_distribution<double>> distributionParticule(dimension);

	}
}

template<typename F>
Abeille<F>::Abeille(F _obj, unsigned _nbFleurs,unsigned _dim):pFleurs(new std::vector<double>{}),
pFitnesses(new std::vector<double> { }), obj(_obj), dimension { _dim }, nbFleurs {_nbFleurs },
pIterations(new std::vector<int> {}) {
	fleurs=*pFleurs;
	fitnesses=*pFitnesses;
	iterations=*pIterations;



}


template<typename F>
inline void Abeille<F>::solve() {
}

#endif /* ABEILLE_H_ */
