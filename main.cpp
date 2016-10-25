#include <iostream>
#include <limits.h>
#include <time.h>
#include "fahrradfahrer.h"
using namespace std;

int main()
{
	//Datei mit Strecke einlesen
    std::string eingabe;
    std::cout<<"Datei : ";
    std::cin>>eingabe;

	//Fahrradfahren erstellen und Strecke ablaufen lassen. Dabei die Laufzeit messen.
    Fahrradfahrer JohnDoe(eingabe);
    double t0=clock();
    JohnDoe.ablaufen();
    double t1=clock();
	
	/* Laufzeit ausgeben und Strecke fahren. Anweisungen für gerade Streckenabschnitte
	   werden in prot.txt gespeichert.
	   Das Fahren ist für das Ermitteln des Fahrverhaltens nicht notwendig.*/
    std::cout<<"Laufzeit: "<<(t1-t0)/CLOCKS_PER_SEC<<"s\n";
    JohnDoe.fahren();
    return 0;
}
