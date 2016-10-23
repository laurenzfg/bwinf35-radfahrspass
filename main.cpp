#include <iostream>
#include <limits.h>
#include <time.h>
#include "fahrradfahrer.h"
using namespace std;

int main()
{
    std::string eingabe;
    std::cout<<"Datei : ";
    std::cin>>eingabe;
    Fahrradfahrer JohnDoe(eingabe);
    double t0=clock();
    JohnDoe.ablaufen();
    double t1=clock();
    std::cout<<"Laufzeit: "<<(t1-t0)/CLOCKS_PER_SEC<<"s\n";
    JohnDoe.fahren();
    return 0;
}
