/*
 * Fackley.h
 *
 *  Created on: Mar 18, 2015
 *      Author: eisti
 */

#ifndef SRC_FACKLEY_H_
#define SRC_FACKLEY_H_

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <vector>
#include <cmath>
#include<iostream>

class Fackley {
public:
	double f(const std::vector<double> params) const;

	std::vector<double> getMin()const;
	std::vector<double> getMax()const;
};

#endif /* SRC_FACKLEY_H_ */
