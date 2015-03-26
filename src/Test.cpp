#include "../cute/cute.h"
#include "../cute/ide_listener.h"
#include "../cute/xml_listener.h"
#include "../cute/cute_runner.h"
#include "Fcarre.h"
#include "Essaim.h"
#include <iostream>
#include "Abeille.h"
#include"Fbohachevsky.h"
#include"Fackley.h"
#include "Abeille.h"

using namespace std;

void testAbeill()
{
	F_carre f { };
	Abeille<F_carre> abeille(f,10,10000);
	abeille.testInitFleurs();
}
void EssaimMajVoisin(){
    Fackley f;
	Essaim<Fackley> e(f, 0.02, 0.02, 100,10);
        e.testMajVoisins();
}

void EssaimInitVectors(){
    Fbohachevsky f;
	Essaim<Fbohachevsky> e(f, 0,02, 100, 10);
	e.testMajVoisins();
}

void fCarre(){
	F_carre f;
	vector<double> x(1);
	x[0]=2;
	ASSERT_EQUAL(4,f.f(x));
        
        Essaim<F_carre> e(f,0,0,1000,1000);
        e.solve();
        std::vector<double> res = e.getResultat();
}

void init() {
	ASSERTM("start writing tests",true);
}

//Test sur la classe Algorithme.

void algo(){
    F_carre f;
    Abeille<F_carre> a(f,10,10000);
    ASSERTM("start writing tests",true);

}

void solveEssaim(){
	Fackley f;
	Essaim<Fackley> e(f, 0.02, 0.02, 1000,10000);

	e.initVectors();
	e.afficherParticules();

	e.solve();
	cout<<e<<endl;


}

void runAllTests(int argc, char const *argv[]){
	cute::suite s{};

//	s.push_back(CUTE(init));
//	s.push_back(CUTE(fCarre));
//	s.push_back(CUTE(solveEssaim));
//
//        s.push_back(CUTE(EssaimInitVectors));
//        s.push_back(CUTE(EssaimMajVoisin));
//
//	s.push_back(CUTE(solveEssaim));
//	s.push_back(CUTE(algo));

	s.push_back(CUTE(testAbeill));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
	//initEssaim();
    return 0;
}



