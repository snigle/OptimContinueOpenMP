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
		obj(_obj), c1(_c1), c2(_c2), nbParticules(_nbParticules), cArret(
				_cArret), dimension(_obj.getMax().size()), particules(
				vector<vector<double>>(_nbParticules)), c(
				vector<double>(_nbParticules)), xp(
				vector<vector<double>>(_nbParticules)), cv(
				vector<double>(_nbParticules)), xv(
				vector<vector<double>>(_nbParticules)), vitesse(
				vector<vector<double>>(_nbParticules)) {
}
Essaim::~Essaim() {

}

void Essaim::initVectors() {
	vector<double> min = obj.getMin();
	vector<double> max = obj.getMax();

	if (min.size() != max.size()) {
		cerr
				<< "Les min et le max de la fonction objectif ne renvoie pas un vecteur de même taille"
				<< endl;
	}

	//Préparation des rands uniform
	default_random_engine generator { };
	std::uniform_real_distribution<double> distribution(0, 1);
	vector<std::uniform_real_distribution<double>> distributionParticule(
			dimension);
	for (unsigned j = 0; j < dimension; ++j) {
		distributionParticule[j] = uniform_real_distribution<double>(min[j],
				max[j]);
	}

	for (unsigned i = 0; i < nbParticules; ++i) {
		particules[i] = vector<double>(min.size());
		vitesse[i] = vector<double>(min.size());
		for (unsigned j = 0; j < min.size(); ++j) {
			particules[i][j] = distributionParticule[j](generator);
			vitesse[i][j] = distribution(generator);
		}
		c[i] = obj.f(particules[i]);
		xp[i] = particules[i];
		c[i] = numeric_limits<double>::max();
	}
	for (unsigned i = 0; i < nbParticules; ++i) {
		majVoisins(i);
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
			if (obj.f(particules[i]) < c[i]) {
				c[i] = obj.f(particules[i]);
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
	return 1;
}

double Essaim::coefConstriction(double rho1, double rho2) {
	double rho;
	rho = rho1 + rho2;
	return (1 - (1/(rho)) + (sqrt(fabs( pow(rho, 2) - 4*rho ))/2) );
}

bool Essaim::majVoisins(unsigned i) {
	bool majEffectue { false };

	// Topologie anneau
	unsigned v1 { i - 1 };
	unsigned v2 { i + 1 };
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

void Essaim::afficherParticules() {
	for (unsigned i = 0; i < nbParticules; ++i) {
		cout << "(";
		for (unsigned j = 0; j < dimension; ++j) {
			cout << particules[i][j] << ", ";
		}
		cout << ")" << endl;
	}
}

void Essaim::afficherMeilleurVoisin() {
}
