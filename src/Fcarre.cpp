/*
 * Fcarre.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: eisti
 */

#include "Fcarre.h"

F_carre::F_carre() {
	// TODO Auto-generated constructor stub

}

F_carre::~F_carre() {
	// TODO Auto-generated destructor stub
}

double F_carre::f(std::vector<double> parametres) {
	return parametres[0] * parametres[0];

}
