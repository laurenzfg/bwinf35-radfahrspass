#ifndef FAHRRADFAHRER_H
#define FAHRRADFAHRER_H
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

class Fahrradfahrer
{
public:
    Fahrradfahrer(std::string Datei);
		~Fahrradfahrer();
    void ablaufen();
    void fahren();
private:
    FILE * Strecke;
    void exep(); 	   				// Wird bei nicht Befahrbarkeit aufgerufen.
    int Beschleunigungen; 	// Speichert die Anzahl der Beschleunigungen.
};

#endif // FAHRRADFAHRER_H
