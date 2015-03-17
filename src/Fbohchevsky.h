/*
 * Fackley.h
 *
 *  Created on: Mar 17, 2015
 *      Author: eisti
 */

#ifndef SRC_FBOHCHEVSKY_H_
#define SRC_FBOHCHEVSKY_H_
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <vector>
#include <math.h>
#include<iostream>
class Fbohchevsky {
public:
	Fbohchevsky();
	virtual ~Fbohchevsky();
	double f(std::vector<double> params);

	std::vector<double> getMin();
	std::vector<double> getMax();
};

#endif /* SRC_FBOHCHEVSKY_H_ */
