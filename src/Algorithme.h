/*
 * Algorithme.h
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#ifndef ALGORITHME_H_
#define ALGORITHME_H_
#define DEBUG std::cout<<__FILE__<<"["<<__LINE__<<"]: "<<__func__<<std::endl;
#include "Objectif.h"

class Algorithme {
protected:
	/*Objectif fonctionObjectif;*/
public:
	Algorithme();
	/*Algorithme(Objectif);*/
	virtual ~Algorithme();
	//virtual int solve()const;

};

#endif /* ALGORITHME_H_ */
