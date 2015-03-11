/*
 * Fcarre.h
 *
 *  Created on: Mar 11, 2015
 *      Author: eisti
 */

#ifndef SRC_FCARRE_H_
#define SRC_FCARRE_H_

#include <vector>

class F_carre {
public:
	F_carre();
	virtual ~F_carre();

	double f(std::vector<double> parametres);
};

#endif /* SRC_FCARRE_H_ */
