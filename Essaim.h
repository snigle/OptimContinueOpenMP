/*
 * Essaim.h
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#ifndef ESSAIM_H_
#define ESSAIM_H_
#include "Algorithme.h"

class Essaim:public Algorithme {
protected:
public:
	Essaim();
	Essaim(Objectif);
	virtual ~Essaim();
	int solve()const;
};

#endif /* ESSAIM_H_ */
