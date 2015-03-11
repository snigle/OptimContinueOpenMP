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



void Essaim::initVectors() {
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

int Essaim::solve() {
	double c1, c2, r1, r2, rho1, rho2;
	//double somVitesse = 0;
	unsigned compteur = 0;
	c1 = 1.5;
	c2 = 2;
	do {
		for (unsigned i = 0; i < nbParticules; ++i) {
			if (obj.f(particules[i]) > c[i] ) {
				c[i] = obj.f( particules[i] );
				xp[i] = particules[i];
			}
			majVoisins(i);
		}
		for (unsigned i = 0; i < nbParticules; ++i) {
			do{
				r1 = rand()/(double)RAND_MAX;
				r2 = rand()/(double)RAND_MAX;
				rho1 = c1 * r1;
				rho2 = c2 * r2;
			}while( rho1 + rho2 <= 4 );
			vitesse[i] = coefConstriction( rho1, rho2)*(vitesse[i] + rho1*(xp[i] - particules[i]) + rho2*( xv[i] - particules[i]));
			particules[i] = particules[i] + vitesse[i];
			//somVitesse += vitesse[i];
		}
		compteur ++;
	} while (compteur < cArret);
}

double Essaim::coefConstriction(double rho1, double rho2) {
	double rho;
	rho = rho1 + rho2;
	return (1 - (1/(rho)) + (sqrt(fabs( pow(rho, 2) - 4*rho ))/2) )
}

bool Essaim::majVoisins(unsigned i) {
	bool majEffectue { false };

	// Topologie anneau
	int v1 { i - 1 };
	int v2 { i + 1 };
	if (v1 < 0)
		v1 = nbParticules - 1;
	if (v2 == nbParticules)
		v2 = 0;

	if (obj.f(particules[v1]) > cv[i]) {
		cv[i] = obj.f(particules[v1]);
		xp[i] = particules[v1];
		majEffectue = true;
	}
	if (obj.f(particules[v2]) > cv[i]) {
		cv[i] = obj.f(particules[v2]);
		xp[i] = particules[v2];
		majEffectue = true;
	}
	return majEffectue;
}
