#ifndef MOSSA_H
#define MOSSA_H

#include <cstdlib>

//contiene l'informazione relativa ad una mossa eseguita, utile alla Tabu Search
class Mossa
{
    int* indici; //puntatore ad un area di memoria che contiene gli indici relativi ad una mossa
public:
    Mossa(int n); //costruttore
    void setIndice(int i, int n); //inserisce il valore i in posizione n in indici
    int* getIndici(){ return indici;}; //ritorna il puntatore ad indici
};



#endif