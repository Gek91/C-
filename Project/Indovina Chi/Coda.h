#ifndef _Lista_h
#define _Lista_h
#include "Domanda.h"

class Coda{ //Elemento della coda
    Persona* elemento; //puntatore ad un oggetto persona(solitamente una lista di persone)
    Coda* nxt;  //puntatore al prossimo elemento della lista
    int array[N_DOMANDE];   //array necessario all'algoritmo
    int domanda;    //tiene traccia della domanda che ha generato quella parte dell'albero
    int numerocicli;    //tiene tracci del numero dei cicli rimanenti
    
public:
    Coda(Persona* elem,Coda* next,int* arr,int domanda, int numero); //costruttore
    void setelemento(Persona* elem){elemento=elem;} //imposta il valore di elemento
    void setnext(Coda* next){nxt=next;} //imposta il valore del puntatore nxt
    void setarray(int* arr){memcpy(array,arr,N_DOMANDE*sizeof(int));}   //imposta il valore dell'array
    void setdomanda(int dom){domanda=dom;} //imposta il valore della domanda
    void setnumerocicli(int ncicli){numerocicli=ncicli;}    //imposta il valore di numerocicli
    
    Persona* getelemento(){return elemento;}    //ritorna l'elemento nella Coda
    Coda* getnxt(){return nxt;} //ritorna il prossimo elemento della Coda
    int* getarray(){return array;} //ritorno il valore dell'array salvato
    int getdomanda(){return domanda;}   //ritorna il valore di domanda
    int getnumerocicli(){return numerocicli;}   //ritorna il valore di numerocicli
};

Coda::Coda(Persona* elem,Coda* next,int *arr,int domanda,int numero) //costruttore
{
    setarray(arr);
    setelemento(elem);
    setnext(next);
    setdomanda(domanda);
    setnumerocicli(numero);
}

#endif