#ifndef PERSONA_H
#define PERSONA_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <new>
#include <string>
#include <climits>
#include <time.h>
#include <stdlib.h>
#include "Persona.h"
#include <ctime>
using namespace std;

#define N_DOMANDE 35//Numero di domande possibili nel gioco

// definiscono i valori che possono assumere gli attributi
enum capelli{biondi,castani,rossi,bianchi,neri,calvo};  //valori per capelli
enum occhi{marroni,azzurri,verdi};  //valori per gli occhi
enum dimensioni{grande,normale,piccolo,assente};    //valori per cappello, occhiali, barba, baffi, bocca, orecchie, naso
enum sesso{uomo,donna}; //valori per sesso

class Persona{//definisce i personaggi e i loro attributi
    int nome; //nei test è definito attraverso un numero intero
    dimensioni cappello;
    dimensioni occhiali;
    dimensioni barba;
    dimensioni baffi;
    sesso varsesso;     //si maschio, no femmina
    dimensioni bocca;
    dimensioni orecchie;
    dimensioni naso;
    capelli colorecapelli;
    occhi coloreocchi;
    Persona *next;  //puntatore all'elemento successivo della lista

    
public:
    Persona(int name);  //costruttore a cui si passa il nome
    Persona(Persona *first, Persona* nxt);// costruttore di copia
    int getnome(){return nome;};    //restituisce il nome del personaggio
    dimensioni getcappello(){return cappello;}; //restituisce il valore dell'attributo cappello
    dimensioni getocchiali(){return occhiali;}; //restituisce il valore dell'attributo occhiali
    dimensioni getbarba(){return barba;};   //restituisce il valore dell'attributo barba
    dimensioni getbaffi(){return baffi;};   //restituisce il valore dell'attrbuto baffi
    sesso getsesso(){return varsesso;}; //resituisce il valore dell'attributo sesso
    dimensioni getbocca(){return bocca;};   //restituisce il valore dell'attributo bocca
    dimensioni getorecchie(){return orecchie;}; //restituisceil valore dell'attributo orecchie
    capelli getcapelli(){return colorecapelli;};    //restituisce il valore dell'atributo capelli
    occhi getocchi(){return coloreocchi;};  //restituisce il valore dell'attrivuto occhi
    dimensioni getnaso(){return naso;}; //restituisce il valore dell'attributo naso
    Persona* getnext(){return next;};   //restituisce il prossimo elemento della lista di personaggi
    void setnext(Persona* nxt){next=nxt;}; //imposta il prossimo elemento della lista
};

//Classe Persona
//#include "Persona.h"

Persona::Persona(int name) //costruttore random di personaggi
{
    int distribuzionesesso=rand()%4;  //determina il sesso del personaggio
    if(distribuzionesesso>0) //determina gli altri attributi se maschio
    {
        varsesso=uomo;//maschio
        //barba
        switch (rand()%4) {
            case 0:
                barba=grande;
                break;
            case 1:
                barba=normale;
                break;
            case 2:
                barba=piccolo;
                break;
            case 3:
                barba=assente;
                break;
        }
        //baffi
        switch (rand()%4) {
            case 0:
                baffi=grande;
                break;
            case 1:
                baffi=normale;
                break;
            case 2:
                baffi=piccolo;
                break;
            case 3:
                baffi=assente;
                break;
        }
        //capelli
        switch (rand()%6) {
            case 0:
                colorecapelli=biondi;
                break;
            case 1:
                colorecapelli=castani;
                break;
            case 2:
                colorecapelli=rossi;
                break;
            case 3:
                colorecapelli=bianchi;
                break;
            case 4:
                colorecapelli=neri;
                break;
            case 5:
                colorecapelli=calvo;
                break;
        }
    }
    else //determina gli altri attributi se è femmina
    {
        varsesso=donna;//femmina
        barba=assente;
        baffi=assente;
        switch (rand()%5) {
            case 0:
                colorecapelli=biondi;
                break;
            case 1:
                colorecapelli=castani;
                break;
            case 2:
                colorecapelli=rossi;
                break;
            case 3:
                colorecapelli=bianchi;
                break;
            case 4:
                colorecapelli=neri;
                break;
        }
    }
    nome=name;
    //bocca
    switch (rand()%3) {
        case 0:
            bocca=grande;
            break;
        case 1:
            bocca=normale;
            break;
        case 2:
            bocca=piccolo;
            break;
    }
    //cappello
    switch (rand()%4) {
        case 0:
            cappello=grande;
            break;
        case 1:
            cappello=normale;
            break;
        case 2:
            cappello=piccolo;
            break;
        case 3:
            cappello=assente;
            break;
    }
    //occhiali
    switch (rand()%4) {
        case 0:
            occhiali=grande;
            break;
        case 1:
            occhiali=normale;
            break;
        case 2:
            occhiali=piccolo;
            break;
        case 3:
            occhiali=assente;
            break;
    }
    //naso
    switch (rand()%3) {
        case 0:
            naso=grande;
            break;
        case 1:
            naso=normale;
            break;
        case 2:
            naso=piccolo;
            break;
    }
    //orecchie
    switch (rand()%3) {
        case 0:
            orecchie=grande;
            break;
        case 1:
            orecchie=normale;
            break;
        case 2:
            orecchie=piccolo;
            break;
    }
    //occhi
    switch (rand()%3) {
        case 0:
            coloreocchi=marroni;
            break;
        case 1:
            coloreocchi=azzurri;
            break;
        case 2:
            coloreocchi=verdi;
            break;
    }
    setnext(NULL);
}

Persona::Persona(Persona* first, Persona* nxt) //costruttore copia
{
    nome=first->getnome();
    cappello=first->getcappello();
    occhiali=first->getocchiali();
    barba=first->getbarba();
    baffi=first->getbaffi();
    bocca=first->getbocca();
    varsesso=first->getsesso();
    orecchie=first->getorecchie();
    colorecapelli=first->getcapelli();
    coloreocchi=first->getocchi();
    naso=first->getnaso();
    next=nxt;
}


#endif


