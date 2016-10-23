#ifndef FAHRRADFAHRER_H
#define FAHRRADFAHRER_H
#include <iostream>
#include <fstream>
#include <string>

class Fahrradfahrer
{
public:
    Fahrradfahrer(std::string Datei);
    void ablaufen();
    void fahren();
private:
    FILE * Strecke;
    void exep();
    int beschleunigen;
};

#endif // FAHRRADFAHRER_H
