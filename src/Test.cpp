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
#include "Fschwefel.h"
#include <stdio.h>
#include <string.h>

using namespace std;
//////////////////////////////////Tests pour l'heuristique des abeilles//////////////////

void testAbeilleGenererFleur()
{
	ASSERTM("Vérifie que la fleur est bien dans les limites de l'espace de recherche",true);
	Fbohachevsky f { };
	Abeille<Fbohachevsky> abeille(f,500,100);
	abeille.testGenererFleur();
}


void testAbeillF_carre()
{
	ASSERTM("Test de résolution de la fonciton fcarré avec l'heuristique des abeilles",true);
	F_carre f { };
	Abeille<F_carre> abeille(f,500,100);
	abeille.testInitFleurs();
	abeille.solve();
	cout<<abeille<<endl;
}

void testAbeillFackley()
{
	ASSERTM("Test de résolution de la fonction de ackley avec l'heuristique des abeilles (2 dimensions)",true);
	Fackley f { };
	Abeille<Fackley> abeille(f,500,100);
	abeille.solve();
	cout<<abeille<<endl;

}

void testAbeillFbohachevsky()
{
	ASSERTM("Test de résolution de la fonction de bohachevsky avec l'heuristique des abeilles (2 dimensions)",true);
	Fbohachevsky f { };
	Abeille<Fbohachevsky> abeille(f,500,100);
	abeille.solve();
	cout<<abeille<<endl;
}

void testAbeilleFschwefel()
{
	ASSERTM("Test de résolution de la fonction de schewefel avec l'heuristique des abeilles (3 dimensions)",true);
	Fschwefel<3> f ;
	Abeille<Fschwefel<3>> abeille(f,100,1000);
	abeille.solve();
	cout<<abeille<<endl;



}

//////////////////////////////////Tests pour l'heuristique des abeilles//////////////////

void EssaimMajVoisin()
{
	ASSERTM("tests pour la mise à jour des voisins",true);
    Fackley f;
	Essaim<Fackley> e(f, 0.02, 0.02, 100,10);
	e.testMajVoisins();
}

void EssaimInitVectors(){
	ASSERTM("tests pour l'initialisation des vecteurs",true);
    Fbohachevsky f;
	Essaim<Fbohachevsky> e(f, 0,02, 100, 10);
	e.testMajVoisins();
}

void testEssaimFcarre(){
	F_carre f;
	Essaim<F_carre> e(f, 0.02, 0.02, 1000,1000);
	e.solve();
	cout<<e<<endl;


}

void testEssaimAckley(){
	Fackley f;
	Essaim<Fackley> e(f, 0.02, 0.02, 1000,1000);
	e.solve();
	cout<<e<<endl;


}

void testEssaimFschwefel()
{
	Fschwefel<3> f ;
	Essaim<Fschwefel<3>> essaim(f, 0.02, 0.02, 500,10000);
	essaim.solve();
	std::cout<<essaim<<std::endl;
}



void init() {
	ASSERTM("start writing tests",true);
}




void runAllTests(int argc, char *argv[]){
	cute::suite s{};
	s.push_back(CUTE(init));
	if(argc==2)
	{
		//Test avec les abeilles.
		if(strcmp(argv[1],"-a")==0)
		{
			cout<<"zfz";
			s.push_back(CUTE(testAbeilleGenererFleur));
			s.push_back(CUTE(testAbeillF_carre));
			s.push_back(testAbeillFackley);
			s.push_back(CUTE(testAbeillFbohachevsky));
			s.push_back(CUTE(testAbeilleFschwefel));
		}
		//Test avec les essaims.
		if(strcmp(argv[1],"-e")==0)
		{
			s.push_back(CUTE(EssaimMajVoisin));
			s.push_back(CUTE(EssaimInitVectors));
			s.push_back(CUTE(testEssaimFcarre));
			s.push_back(CUTE(testEssaimAckley));
			s.push_back(CUTE(testEssaimFschwefel));

		}
	}

	//TODO ajouter les tests en parallèle, OPENMP, MPI
//	s.push_back(CUTE(init));
//	s.push_back(CUTE(fCarre));
//	s.push_back(CUTE(solveEssaim));
//
//        s.push_back(CUTE(EssaimInitVectors));
//        s.push_back(CUTE(EssaimMajVoisin));
//
//	s.push_back(CUTE(solveEssaim));
//	s.push_back(CUTE(algo));

//	s.push_back(CUTE(testAbeillF_carre));
//	s.push_back(CUTE(testAbeillFackley));
//	s.push_back(CUTE(testAbeilleGenererFleur));
//	s.push_back(CUTE(testAbeilleFschwefel));
//	s.push_back(CUTE(testEssaimFschwefel));
//	s.push_back(CUTE(testAbeillFbohachevsky));

	cute::xml_file_opener xmlfile(1,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,1,argv)(s, "AllTests");
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



