#ifndef PUNTO_H
#define PUNTO_H

#include <iostream>

// Classe che rappresenta un punto con coordinate intere
class Punto{
    int x; //coordinata x
    int y; //coordinata y
public:
    Punto(int a, int b): x(a), y(b){}; //costruttore a due parametri
    Punto(const Punto& copia): x(copia.getx()), y(copia.gety()){}; //costruttore di copia
    int getx() const{return x;}; //ritorna il valore di x
    int gety() const{return y;}; //ritorna il valore di y
    
    //Operatori == e !=
    bool operator==(const Punto &p)
    {
        if(x==p.getx())
            if(y==p.gety())
                return true;
        return false;
    }
    
    bool operator!=(Punto p)
    {
        if(x==p.getx())
            if(y==p.gety())
                return false;
        return true;
    }
    friend std::ostream& operator<< (std::ostream &os, const Punto &p);
    
    bool operator<(Punto p)
    {
        if(x<p.getx())
            return true;
        else
        {
            if(x==p.getx())
            {
                if(y<p.gety())
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
    }

};

#endif
