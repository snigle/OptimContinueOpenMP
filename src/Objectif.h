/*
 * Objectif.h
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#ifndef OBJECTIF_H_
#define OBJECTIF_H_
#include <vector>
#include<string>
class Objectif{
public:
	//virtual ~Objectif();
	virtual void fonctionObjectif(std::vector<std::string> parametres)=0;

};

#endif /* OBJECTIF_H_ */
