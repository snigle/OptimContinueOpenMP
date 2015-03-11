/*
 * Essaim.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: eisti
 */

#include "Essaim.h"
using namespace std;


Essaim::Essaim(F_carre _obj, double _c1, double _c2, unsigned _nbParticules,
		unsigned _cArret, vector<double> min, vector<double> max) :
		obj(_obj), c1 { _c1 }, c2 { _c2 }, nbParticules { _nbParticules }, cArret {
				_cArret }, particules(vector<vector<double>>(_nbParticules)), c(
				vector<double>(_nbParticules)), xp(
				vector<vector<double>>(_nbParticules)), cv(
				vector<double>(_nbParticules)), xv(
				vector<vector<double>>(_nbParticules)), v(
				vector<double>(_nbParticules)),
				borneMin(min), borneMax(max){



}

int Essaim::solve(){
	do {
		for (unsigned i = 0; i < nbParticules; ++i) {
			if (obj.f(particules[i])) > c[i] ) {
				c[i] = obj.f( particules[i] );
				xp[i] = particules[i];
			}
			majVoisins(i);
		}
		for (unsigned i = 0; i < nbParticules; ++i) {
			v[i] = (v[i] );
		}
	} while (cArret);
}

bool Essaim::majVoisins(unsigned i) {
	bool majEffectue = false;
	// Topologie anneau
	int v1 = i-1;
	int v2 = i+1;
	if( v1 < 0 ) v1 = nbParticules-1;
	if( v2 == nbParticules ) v2 = 0;

	if (obj.f(particules[v1]) > cv[i] ) {
		cv[i] = obj.f( particules[v1] );
		xp[i] = particules[v1];
		majEffectue = true;
	}
	if (obj.f(particules[v2]) > cv[i] ) {
		cv[i] = obj.f( particules[v2] );
		xp[i] = particules[v2];
		majEffectue = true;
	}
	return majEffectue;
}
