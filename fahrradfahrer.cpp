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
    char Streckenabschnitt;			
    int gelesen;					
    int geschwindigkeit_maximal=0;	
    int geschwindigkeit_minimal=0;	
    Beschleunigungen=0; 
				
		// Solange noch Streckenabschnitt eingelesen werden
    while((gelesen=fread(&Streckenabschnitt,1,1,Strecke))==1) 
    {
				// Geschwindikeiten werden entsprechend des eingelesenen Streckenteils angepasst
        if(Streckenabschnitt=='/')
        {
            geschwindigkeit_maximal--;
            geschwindigkeit_minimal--;
        }
        else if(Streckenabschnitt=='_')
        {
            geschwindigkeit_maximal++;
            geschwindigkeit_minimal--;
        }
        else if(Streckenabschnitt=='\\')
        {
            geschwindigkeit_maximal++;
            geschwindigkeit_minimal++;
        }
		
				// Wenn die schnelle Geschwindikeit nicht mehr ausreicht zum Befahren der Strecke, breche ab.
        if(geschwindigkeit_maximal<0) this->exep();

				//Wenn die langsame Geschwindidkeit nicht mehr ausreicht erhöhe die Geschwindidkeit um 2. (Wandle einmal bremsen in einmal Beschleunigungen um)
        if(geschwindigkeit_minimal<0)
        {
            geschwindigkeit_minimal+=2;
            Beschleunigungen++;
        }
    }
	
		// Wenn die Endgeschwindigkeit null ist, lässt sich die Strecke befahren.
    if(geschwindigkeit_minimal==0)
    {
        std::cout<<"Die Strecke lässt sich befahren. Man muss am Anfang "<<Beschleunigungen<<" mal Beschleunigungen."<<std::endl;
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
    int Geschwindigkeit=0;
		std::ofstream of("prot.txt");
	
		// Strecke befahren, für jeden geraden Streckenabschnitt + oder - ausgeben
    while((gelesen=fread(&Streckenabschnitt,1,1,Strecke))==1)
    {
        if(Streckenabschnitt=='_')
        {
            if(habe_beschleunigt<Beschleunigungen)
            {
                Geschwindigkeit++;
                habe_beschleunigt++;
								of<<"+";
            }
            else
            {
                Geschwindigkeit--;
								of<<"-";
            }
        }
        else if(Streckenabschnitt=='\\')
        {
            Geschwindigkeit++;
        }
        else if(Streckenabschnitt=='/')
        {
            Geschwindigkeit--;
        }
    }
		of.close();
    std::cout<<"Endgeschwindigkeit : "<<Geschwindigkeit<<std::endl;
}

void Fahrradfahrer::exep()
{
    std::cout<<"Die Strecke lässt sich nicht befahren."<<std::endl;
    exit(-1);
}
