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
class Essaim:public Algorithme {
private:
	std::vector<std::vector<double>> particules;
	std::vector<double> c;
	std::vector<std::vector<double>> xp;
	std::vector<double> cv;
	std::vector<std::vector<double>> xv;
	std::vector<std::vector<double>> v;

	double c1;
	double c2;
	Objectif obj;
	unsigned nbParticules;
	unsigned cArret;

public:
	Essaim(Objectif obj, double c1, double c2, unsigned nbParticules, unsigned cArret);
	virtual ~Essaim();
	int solve()const;
	bool majVoisins(unsigned i)const;
};

#endif /* ESSAIM_H_ */
