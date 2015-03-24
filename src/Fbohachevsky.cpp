/*
 * Fackley.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: eisti
 */

#include "Fbohachevsky.h"

Fbohachevsky::Fbohachevsky() {
	// TODO Auto-generated constructor stub

}

Fbohachevsky::~Fbohachevsky() {
	// TODO Auto-generated destructor stub
}

double Fbohachevsky::f(const std::vector<double> params) const{
	double x1 { params[0] };
	double x2 { params[1] };

	return ((x1*x1+2*(x2*x2))-(0.3*cos(3*M_PI*x1))-(0.4*cos(4*M_PI*x2))+0.7);
}

std::vector<double> Fbohachevsky::getMin() {
	std::vector<double> vect{};
	vect.push_back(0.0);
	vect.push_back(0.0);
	vect[0]=-100.00;
	vect[1]=-100.00;

	return vect;

}

std::vector<double> Fbohachevsky::getMax() {
	std::vector<double> vect{};
		vect.push_back(0.0);
		vect.push_back(0.0);
		vect[0]=100.00;
		vect[1]=100.00;

		return vect;
}
