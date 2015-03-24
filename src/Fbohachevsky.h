/*
 * Fackley.h
 *
 *  Created on: Mar 17, 2015
 *      Author: eisti
 */

#ifndef SRC_FBOHACHEVSKY_H_
#define SRC_FBOHACHEVSKY_H_
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <vector>
#include <math.h>
#include<iostream>
class Fbohachevsky {
public:
	Fbohachevsky();
	virtual ~Fbohachevsky();
	double f(const std::vector<double> params) const;

	std::vector<double> getMin();
	std::vector<double> getMax();
};

#endif /* SRC_FBOHACHEVSKY_H_ */
