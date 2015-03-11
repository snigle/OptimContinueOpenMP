/*
 * Essaim.h
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#ifndef ESSAIM_H_
#define ESSAIM_H_
#include "Algorithme.h"
#include "Fcarre.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

class Essaim: public Algorithme {
private:

	F_carre obj;
	double c1;
	double c2;

	unsigned nbParticules;
	unsigned cArret;

	std::vector<std::vector<double>> particules;
	std::vector<double> c;
	std::vector<std::vector<double>> xp;
	std::vector<double> cv;
	std::vector<std::vector<double>> xv;
	std::vector<std::vector<double>> vitesse;

	std::vector<double> borneMin;
	std::vector<double> borneMax;

public:
	Essaim(F_carre _obj, double _c1, double _c2, unsigned _nbParticules,
			unsigned _cArret);
	virtual ~Essaim();

	int solve();
	void initVectors();

	double coefConstriction(double rho1, double rho2);
	bool majVoisins(unsigned i);
};

#endif /* ESSAIM_H_ */
