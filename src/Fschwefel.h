/*
 * Fschwefel.h
 *
 *  Created on: Mar 31, 2015
 *      Author: eisti
 */

#ifndef SRC_FSCHWEFEL_H_
#define SRC_FSCHWEFEL_H_
#include<vector>
#include<math.h>
#include <cmath>
#include<iostream>
template <unsigned N>
class Fschwefel {
public:
	Fschwefel();
	virtual ~Fschwefel();

	double f(const std::vector<double> params) const;

	std::vector<double> getMin()const;
	std::vector<double> getMax()const;
};
template <unsigned N>
Fschwefel<N>::Fschwefel() {
	// TODO Auto-generated constructor stub

}
template <unsigned N>
Fschwefel<N>::~Fschwefel() {
	// TODO Auto-generated destructor stub
}
template <unsigned N>
double Fschwefel<N>::f(const std::vector<double> params) const {
	double res {0};
	double somme {0};
	res =418.9829 * N;
	for(unsigned i=0;i<N;++i)
	{
		somme+=params[i]* sin(sqrt(std::abs(params[i])));
	}

	return res-somme;

}
template <unsigned N>
std::vector<double> Fschwefel<N>::getMin() const {
	std::vector<double> min;
	for(unsigned i=0;i<N;++i)
	{
		min.push_back(-500);
	}

	return min;

}
template <unsigned N>
std::vector<double> Fschwefel<N>::getMax() const {
	std::vector<double> max;
	for(unsigned i=0;i<N;++i)
		{
			max.push_back(500);
		}
	return max;
}
#endif /* SRC_FSCHWEFEL_H_ */
