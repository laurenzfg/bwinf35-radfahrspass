#include "fahrradfahrer.h"

Fahrradfahrer::Fahrradfahrer(std::string Datei)
{
	// Datei mit Strecke öffnen
    Strecke=fopen(Datei.c_str(),"r");
    if(Strecke==NULL)
    {
        std::cout<<"Streckendatei "<<Datei<<" ließ sich nicht öffnen"<<std::endl;
    }
}

Fahrradfahrer::~Fahrradfahrer()
{
	fclose(Strecke); 
}

void Fahrradfahrer::ablaufen()
{
    register char Streckenabschnitt;		// momentanter Streckenabschnitt
    register int gelesen;					// Anzahl der tatsächlich gelesenen Bytes
    register int geschwindigkeit_schnell=0;	// Geschwindigkeit schnell: Auf jedem geraden Streckenabschnitt wird beschleunigt.
    register int geschwindigkeit_langsam=0;	// Geschwindigkeit langsam: Solange wie möglich wird gebremst.
    beschleunigen=0;

	
    while((gelesen=fread(&Streckenabschnitt,1,1,Strecke))==1) // Solange noch Streckenabschnitt eingelesen werden
    {
		// Geschwindikeiten werden entsprechend des eingelesenen Streckenteils angepasst
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
		
		// Wenn die schnelle Geschwindikeit nicht mehr ausreicht zum befahren der Strecke, breche ab.
        if(geschwindigkeit_schnell<0) this->exep();

		//Wenn die langsame Geschwindidkeit nicht mehr ausreicht erhöhe die Geschwindidkeit um 2. (Wandle einmal bremsen in einmal beschleunigen um)
        if(geschwindigkeit_langsam<0)
        {
            geschwindigkeit_langsam+=2;
            beschleunigen++;
        }
    }
	
	// Wenn die Endgeschwindigkeit null ist, lässt sich die Strecke befahren.
    if(geschwindigkeit_langsam==0)
    {
        std::cout<<"Die Strecke lässt sich befahren. Man muss am Anfang "<<beschleunigen<<" mal beschleunigen."<<std::endl;
    }
    else
    {
        this->exep();
    }
	fseek(Strecke,0,SEEK_SET);
}

void Fahrradfahrer::fahren()
{
    char Streckenabschnitt;
    int gelesen;
    int habe_beschleunigt=0;
    int geschwindigkeit=0;
	std::ofstream of("prot.txt");
	
	// Strecke befahren, für jeden geraden Streckenabschnitt + oder - ausgeben
    while((gelesen=fread(&Streckenabschnitt,1,1,Strecke))==1)
    {
        if(Streckenabschnitt=='_')
        {
            if(habe_beschleunigt<beschleunigen)
            {
                geschwindigkeit++;
                habe_beschleunigt++;
				of<<"+";
            }
            else
            {
                geschwindigkeit--;
				of<<"-";
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
    }
	of.close();
    std::cout<<"Endgeschwindigkeit : "<<geschwindigkeit<<std::endl;
}

void Fahrradfahrer::exep()
{
    std::cout<<"Die Strecke lässt sich nicht befahren."<<std::endl;
    exit(-1);
}
