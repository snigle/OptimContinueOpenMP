/*
 * Fcarre.h
 *
 *  Created on: Mar 11, 2015
 *      Author: eisti
 */

#ifndef SRC_FCARRE_H_
#define SRC_FCARRE_H_

#include <vector>
#include "Objectif.h"

class F_carre:public Objectif {
public:
	F_carre();
	virtual ~F_carre();

	double f(std::vector<double> parametres);

	std::vector<double> getMin();
	std::vector<double> getMax();
};

#endif /* SRC_FCARRE_H_ */
