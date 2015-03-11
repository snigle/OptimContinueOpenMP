/*
 * Essaim.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#include "Essaim.h"
using namespace std;

Essaim::Essaim(F_carre _obj, double _c1, double _c2, unsigned _nbParticules,
		unsigned _cArret) :
		obj(_obj), c1 { _c1 }, c2 { _c2 }, nbParticules { _nbParticules }, cArret {
				_cArret }, particules(vector<vector<double>>(_nbParticules)), c(
				vector<double>(_nbParticules)), xp(
				vector<vector<double>>(_nbParticules)), cv(
				vector<double>(_nbParticules)), xv(
				vector<vector<double>>(_nbParticules)), vitesse(
				vector<double>(_nbParticules)) {
}

int Essaim::solve() const {

}

void Essaim::initVectors(){
	vector<double> min = obj.getMin();
		vector<double> max = obj.getMax();
		if (min.size() != max.size()) {
			cerr
					<< "Les min et le max de la fonction objectif ne renvoie pas un vecteur de même taille"
					<< endl;
		}

		for (unsigned i = 0; i < nbParticules; ++i) {
			particules[i] = vector<double>(min.size());
			vitesse[i] = vector<double>(min.size());
			for (unsigned j = 0; j < min.size(); ++j) {
				//Génération d'une position de particules
				std::default_random_engine generator { };
				std::uniform_real_distribution<int> distributionParticule(min[j],
						max[j]);
				particules[i][j] = distributionParticule(generator);
				//Génération d'une vitesse entre 0 et 1 suivant une loi uniforme
				std::uniform_real_distribution<int> distributionVitesse(0, 1);
				vitesse[i][j] = distributionVitesse(generator);

			}
			c[i] = obj.f(particules[i]);
			xp[i] = particules[i];

		}
}
