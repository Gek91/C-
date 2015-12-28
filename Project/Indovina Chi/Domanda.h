#ifndef _Domanda_h
#define _Domanda_h
#include "Persona.h"

class Domanda{ //definisce le domande nel gioco attribuiendo le funzioni da eseguire
    string testo;   //testo della domanda
    Persona* (*funz)(Persona* first, bool value); //puntatore a funzione richiamata dalla domanda
    
public:
    Domanda();
    Domanda(string testo,Persona* (*funzione)(Persona* first, bool value)); //costruttore
    
    string gettesto(){return testo;}; // ritorno il valore del testo della domanda
    Persona* execfunz(Persona* first, bool value) //ritorna l'effetto della funzione assegnata all'oggetto
    {
        return funz(first,value);
    }
    
    void settesto(string t){testo=t;}   //definisce il campo testo nell'oggetto
    void setfunz(Persona* (*funzione)(Persona* first, bool value)){funz=funzione;}//definisce il campo funz nell'oggetto
};


Domanda::Domanda() //costruttore default
{
    settesto("");
}
Domanda::Domanda(string testo,Persona* (*funzione)(Persona* first, bool value))//costruttore
{
    settesto(testo);
    setfunz(funzione);
}

#endif
