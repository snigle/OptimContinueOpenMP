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

vector<double> getMin(){
	return vector<double>{-1};
}
vector<double> getMax(){
	return vector<double>{-1};
}
