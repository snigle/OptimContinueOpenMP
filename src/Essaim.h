/*
 * Essaim.h
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#ifndef ESSAIM_H_
#define ESSAIM_H_
//#include "Algorithme.h"
#include "Fcarre.h"
#include <vector>
#include <iostream>
#include <random>
class Essaim {//: public Algorithme {
private:

	F_carre obj;
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


public:
	/*Essaim(F_carre& f, const double& d, const double& e, const int& i,
			const int& j) {
	}*/

	Essaim(F_carre _obj, double _c1, double _c2, unsigned _nbParticules,
			unsigned _cArret);
	virtual ~Essaim();

	int solve();
	void initVectors();

	bool majVoisins(unsigned i);

	void afficherParticules();
	void afficherMeilleurVoisin();
};

#endif /* ESSAIM_H_ */
