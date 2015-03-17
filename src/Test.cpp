#include "../cute/cute.h"
#include "../cute/ide_listener.h"
#include "../cute/xml_listener.h"
#include "../cute/cute_runner.h"
#include "Fcarre.h"
#include "Essaim.h"
#include <iostream>
using namespace std;

void fCarre(){
	F_carre f;
	vector<double> x(1);
	x[0]=2;
	ASSERT_EQUAL(4,f.f(x));
}

void initEssaim(){
	F_carre f;
	Essaim<F_carre> e(f, 0.02, 0.02, 5,1);
	e.initVectors();
	e.afficherParticules();


}

void init() {
	ASSERTM("start writing tests",true);
}

//Test sur la classe Algorithme.

void algo(){

}

void solveEssaim(){
	F_carre f;
	Essaim<F_carre> e(f, 0.02, 0.02, 100,1000);
	e.initVectors();
	e.afficherParticules();

	e.solve();
	cout<<e<<endl;


}

void runAllTests(int argc, char const *argv[]){
	cute::suite s{};

	s.push_back(CUTE(init));
	s.push_back(CUTE(fCarre));
	s.push_back(CUTE(solveEssaim));

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
	//initEssaim();
    return 0;
}



