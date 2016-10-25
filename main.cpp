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

    JohnDoe.ablaufen();

    JohnDoe.fahren();

    return 0;
}
