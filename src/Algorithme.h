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
#include "Objectif.h"

template <typename FonctionObjetctif>
class Algorithme {
protected:
	FonctionObjetctif fonctionObj ;
public:
	Algorithme(FonctionObjetctif fonction);
	virtual ~Algorithme();
	virtual int solve()const;

};

template<typename FonctionObjetctif>
Algorithme<FonctionObjetctif>::~Algorithme() {
}

template<typename FonctionObjetctif>
Algorithme<FonctionObjetctif>::Algorithme(FonctionObjetctif fonction):fonctionObj(fonction) {

	if(dynamic_cast<Objectif*>(fonctionObj)==nullptr){
		std::cout<<"La classe générique doit être une implémentation de la classe Objectif"<<std::endl;
	}
}

template<typename FonctionObjetctif>
int Algorithme<FonctionObjetctif>::solve() const {
}

#endif /* ALGORITHME_H_ */
