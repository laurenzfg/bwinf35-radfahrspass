#include "fahrradfahrer.h"

Fahrradfahrer::Fahrradfahrer(std::string Datei)
{
    Strecke=fopen(Datei.c_str(),"r");
    if(Strecke==NULL)
    {
        std::cout<<"Streckendatei "<<Datei<<" ließ sich nicht öffnen"<<std::endl;
    }
}

void Fahrradfahrer::ablaufen()
{
    register char Streckenabschnitt;
    register int gelesen;
    register int geschwindigkeit_schnell=0;
    register int geschwindigkeit_langsam=0;
    beschleunigen=0;

    gelesen=fread(&Streckenabschnitt,1,1,Strecke);
    while(gelesen==1)
    {
        if(Streckenabschnitt=='/')
        {
            geschwindigkeit_schnell--;
            geschwindigkeit_langsam--;
        }
        else if(Streckenabschnitt=='_')
        {
            geschwindigkeit_schnell++;
            geschwindigkeit_langsam--;
        }
        else if(Streckenabschnitt=='\\')
        {
            geschwindigkeit_schnell++;
            geschwindigkeit_langsam++;
        }

        if(geschwindigkeit_schnell<0) this->exep();

        if(geschwindigkeit_langsam<0)
        {
            if(geschwindigkeit_langsam<geschwindigkeit_schnell)
            {
                geschwindigkeit_langsam+=2;
                beschleunigen++;
            }
            else
            {
                this->exep();
            }
        }

        gelesen=fread(&Streckenabschnitt,1,1,Strecke);
    }
    fseek(Strecke,0,SEEK_SET);
    if(geschwindigkeit_langsam==0)
    {
        std::cout<<"Die Strecke lässt sich befahren. Man muss am Anfang "<<beschleunigen<<" mal beschleunigen."<<std::endl;
    }
    else
    {
        this->exep();
    }
}

void Fahrradfahrer::fahren()
{
    char Streckenabschnitt;
    int gelesen;
    int habe_beschleunigt=0;
    int geschwindigkeit=0;

    gelesen=fread(&Streckenabschnitt,1,1,Strecke);
    while(gelesen==1)
    {
        if(Streckenabschnitt=='_')
        {
            if(habe_beschleunigt<beschleunigen)
            {
                geschwindigkeit++;
                habe_beschleunigt++;
            }
            else
            {
                geschwindigkeit--;
            }
        }
        else if(Streckenabschnitt=='\\')
        {
            geschwindigkeit++;
        }
        else if(Streckenabschnitt=='/')
        {
            geschwindigkeit--;
        }
        gelesen=fread(&Streckenabschnitt,1,1,Strecke);

    }
    std::cout<<"Endgeschwindigkeit : "<<geschwindigkeit<<std::endl;
}

void Fahrradfahrer::exep()
{
    std::cout<<"Die Strecke lässt sich nicht befahren."<<std::endl;
    exit(-1);
}
