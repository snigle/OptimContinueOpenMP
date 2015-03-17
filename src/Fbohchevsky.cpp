/*
 * Fackley.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: eisti
 */

#include "Fbohchevsky.h"

Fbohchevsky::Fbohchevsky() {
	// TODO Auto-generated constructor stub

}

Fbohchevsky::~Fbohchevsky() {
	// TODO Auto-generated destructor stub
}

double Fbohchevsky::f(std::vector<double> params){
	double x1 { params[0] };
	double x2 { params[1] };

	return ((x1+2*(x2*x2))-(0.3*cos(3*M_PI*x1))-(0.4*cos(4*M_PI*x2))+0.7);
}

std::vector<double> Fbohchevsky::getMin() {
	std::vector<double> vect{};
	vect.push_back(0.0);
	vect.push_back(0.0);
	vect[0]=-100.00;
	vect[1]=-100.00;

	return vect;

}

std::vector<double> Fbohchevsky::getMax() {
	std::vector<double> vect{};
		vect.push_back(0.0);
		vect.push_back(0.0);
		vect[0]=100.00;
		vect[1]=100.00;

		return vect;
}
