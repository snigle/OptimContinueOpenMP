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

int Essaim::solve() const {

}

