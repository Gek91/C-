#ifndef SEGMENTO_H
#define SEGMENTO_H

// Classe che rappresenta un segmento

#include "Punto.h"

class Segmento{
    Punto i; //punto di inizio
    Punto f; //punto di fine
public:
    Segmento(int xa, int ya, int xb, int yb): i(xa,ya), f(xb,yb){}; //costruttore con 4 parametri, le coordinate degli estremi
    Segmento(Punto a, Punto b): i(a), f(b){}; //costruttore con due parametri, i due punti estremi
    Segmento(const Segmento& copia): i(copia.geti()), f(copia.getf()){}; //costruttore di copia
    Punto geti() const{return i;}; //ritorna l'estremo iniziale
    Punto getf() const{return f;}; //ritorna l'estremo finale
    void seti(Punto p) {i=p;}; //ridefinisce il valore di i
    void setf(Punto p) {f=p;}; //ridefinisce il valore di f
    
    bool operator<(const Segmento &s) //Operatore <
    {
        if(i<s.geti())
            return true;
        else
        {
            if(i==s.geti())
            {
                if(f<s.getf())
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
    }
    
    bool operator==(const Segmento &s) //Operatore <
    {
        if(i==s.geti())
            if(f==s.getf())
                return true;
        return false;
    }

};



#endif
