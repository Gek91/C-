#ifndef EVENTO_H
#define EVENTO_H

// Classe che rappresenta un Evento per l'algoritmo Any_segment_intersec

#include "Segmento.h"

class Evento{
    Segmento* s; //segmento a cui l'evento si riferisce
    bool e;         //T=i   F=f
public:
    Evento(Segmento* seg, bool ev):e(ev) {s=seg;}; //costruttore a due parametri, segmento e indicazione se si tratta dell'inzio o della fine
    Segmento* gets() const {return s;}; //ritorna il segmento relativo all'evento
    //Punto getPunto(); //ritorna il punto del segmento a cui si riferisce
    bool gete() const{return e;}; //ritorna il valore relativo a se si tratta di un evento di inizio o fine segmento
    
    bool operator<=(const Evento &ev)
    {
        int x1;
        int x2;
        if(e) //x1
        {
            x1=s->geti().getx();
        }
        else
        {
            x1=s->getf().getx();
        }
        
        if(ev.gete()) //x2
        {
            x2=ev.gets()->geti().getx();
        }
        else
        {
            x2=ev.gets()->getf().getx();
        }
        
        if(x1<x2) //confronta la coordinata x
            return true; //Se ha x minore è minore dell'altro evento
        else
        {
            if(x1==x2) //se sono uguali controllo se gli eventi si riferiscono ad estremi destri o sinistri
            {
                if(e != ev.gete()) //se sono due estremi diversi
                {
                    if(e) //il più piccolo è sinistro
                        return true;
                    else
                        return false;
                }
                else //se hanno estremi uguali ordino per y
                {
                    int y1;
                    int y2;
                    if(e) //basta controllare uno dei due, sono uguali
                    {
                        y1=s->geti().gety(); //y1
                        y2=ev.gets()->geti().gety(); //y2
                    }
                    else
                    {
                        y1=s->getf().gety(); //y1
                        y2=ev.gets()->getf().gety(); //y2
                    }
                    
                    if(y1<=y2) //confronta la coordinata y
                        return true;
                    else
                        return false;
                }
            }
            else //se non sono uguali è minore l'altra
                return false;
        }
    
    }
};

#endif