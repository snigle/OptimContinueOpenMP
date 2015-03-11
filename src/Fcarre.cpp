/*
 * Fcarre.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: eisti
 */

#include "Fcarre.h"

using namespace std;
F_carre::F_carre() {
	// TODO Auto-generated constructor stub

}

F_carre::~F_carre() {
	// TODO Auto-generated destructor stub
}

double F_carre::f(std::vector<double> parametres) {
	return parametres[0] * parametres[0];

}

vector<double> F_carre::getMin(){
	vector<double> x(1);
	x[0] = -1;
	return x;
}
vector<double> F_carre::getMax(){
	vector<double> x(1);
		x[0] = 1;
		return x;
}
