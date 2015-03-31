#include "mpi-bind.h"
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
//Test pour voir si la distance à la vraie solution est accpetable en utilisant l'heuristique des abeilles.
void testAbeillF_carre()
{
	F_carre f { };
	Abeille<F_carre> abeille(f,500,100);
	abeille.testInitFleurs();
	abeille.solve();
		cout<<abeille<<endl;
////	double res { abeille.solve()[0] };
//	ASSERT(res-0<0.01);
}
//Test pour voir si la distance à la vraie solution est accpetable en utilisant l'heuristique des abeilles.
void testAbeillFackley()
{
	Fackley f { };
	Abeille<Fackley> abeille(f,500,100);
//	abeille.testInitFleurs();
	abeille.solve();
	cout<<abeille<<endl;
//	std::vector<double> res=abeille.getPosResult;
//	for(unsigned i=0;i<f.getMax().size();++i)
//	{
//		ASSERT(res[i]-0<0.01);
//	}

}
//Test pour voir si la distance à la vraie solution est acceptable en utilisant l'heuristique des abeilles.
void testAbeillFbohachevsky()
{
	Fbohachevsky f { };
	Abeille<Fbohachevsky> abeille(f,500,100);
	abeille.solve();
		cout<<abeille<<endl;
//	abeille.testInitFleurs();
//	std::vector<double> res=abeille.solve();
//	for(unsigned i=0;i<f.getMax().size();++i)
//	{
//		ASSERT(res[i]-0<0.01);
//	}

}


void testAbeilleGenererFleur()
{
	Fbohachevsky f { };
	Abeille<Fbohachevsky> abeille(f,500,100);
	abeille.testGenererFleur();
}

void EssaimMajVoisin()
{
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
        cout<<res[0]<<endl;
}

void init() {
	ASSERTM("start writing tests",true);
}

//Test sur la classe Algorithme.

void algo(){
    F_carre f;
    Abeille<F_carre> a(f,10,30);
    ASSERTM("start writing tests",true);

}

void solveEssaim(){
	Fackley f;
	Essaim<Fackley> e(f, 0.02, 0.02, 1000,1000);
	e.initVectors();
	//e.afficherParticules();

	e.solve();
	cout<<e<<endl;


}

void runAllTests(int argc, char *argv[]){
	cute::suite s{};

	s.push_back(CUTE(init));
	s.push_back(CUTE(fCarre));
	s.push_back(CUTE(solveEssaim));

        s.push_back(CUTE(EssaimInitVectors));
        s.push_back(CUTE(EssaimMajVoisin));

	s.push_back(CUTE(solveEssaim));
	s.push_back(CUTE(algo));

	s.push_back(CUTE(testAbeillF_carre));
	s.push_back(CUTE(testAbeillFackley));
	s.push_back(CUTE(testAbeilleGenererFleur));
	s.push_back(CUTE(testAbeillFbohachevsky));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char** argv){

    try {
    	MpiBind mpi(argc,argv);
    	if(mpi.getRank()==0){
    	runAllTests(argc,argv);
    	}

    	F_carre f;
    	Abeille<F_carre> e(f,100,1000);
        e.solveMpi(mpi);
        if(mpi.getRank()==0){
        cout<<"MPI :"<<e<<endl;
        }
       }
       catch (const char *ex) {
          std::cerr<<ex<<std::endl;
          return 1;
       }
	//initEssaim();
    return 0;
}



