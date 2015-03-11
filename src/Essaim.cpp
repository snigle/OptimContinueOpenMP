/*
 * Essaim.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#include "Essaim.h"


Essaim::Essaim() {
	// TODO Auto-generated constructor stub

}

Essaim::Essaim(Objectif fonction):Algorithme(fonction)
{

}
Essaim::~Essaim() {
	// TODO Auto-generated destructor stub
}

int Essaim::solve()const{
	do {
		for (unsigned i = 0; i < nbParticules; ++i) {
			if (obj.f(particules(i)) > c ) {
				c = obj.f( particules(i) );
				xp = particules(i);
			}

		}
	} while (cArret);
}

bool Essaim::majVoisins(unsigned i) const {
	bool majEffectue = false;
	// Topologie anneau
	int v1 = i-1;
	int v2 = i+1;
	if( v1 < 0 ) v1 = nbParticules-1;
	if( v2 == nbParticules ) v2 = 0;

	if (obj.f(particules(v1)) > cv[i] ) {
		cv[i] = obj.f( particules(v1) );
		xp[i] = particules(v1);
		majEffectue = true;
	}
	if (obj.f(particules(v2)) > cv[i] ) {
		cv[i] = obj.f( particules(v2) );
		xp[i] = particules(v2);
		majEffectue = true;
	}
	return majEffectue;
}
