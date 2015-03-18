/*
 * Algorithme.h
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#ifndef ALGORITHME_H_
#define ALGORITHME_H_
#define DEBUG std::cout<<__FILE__<<"["<<__LINE__<<"]: "<<__func__<<std::endl;
#include<iostream>

class Algorithme {
protected:

public:
	virtual ~Algorithme();
	virtual int solve()=0;

};



#endif /* ALGORITHME_H_ */
