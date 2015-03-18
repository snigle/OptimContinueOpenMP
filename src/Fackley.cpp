/*
 * Fackley.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: eisti
 */

#include "Fackley.h"

using namespace std;

double Fackley::f(const std::vector<double> params) const{
	double x1 { params[0] };
	double x2 { params[1] };

	return ( -20.0*exp(
					-0.2*sqrt(((x1*x1)/2.0)+
					((x2*x2)/2.0))) -
				exp(
						(cos(2.0*M_PI*x1)/2.0)+
						(cos(2.0*M_PI*x2)/2.0)
						)
				+ 20.0
				+ exp(1) );
}

std::vector<double> Fackley::getMin() {
	std::vector<double> vect{};
	vect.push_back(0.0);
	vect.push_back(0.0);
	vect[0]=-40.00;
	vect[1]=-40.00;

	return vect;

}

std::vector<double> Fackley::getMax() {
	std::vector<double> vect{};
		vect.push_back(0.0);
		vect.push_back(0.0);
		vect[0]=40.00;
		vect[1]=40.00;

		return vect;
}

