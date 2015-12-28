#ifndef TABU_H
#define TABU_H

#include "Mossa.h"
#include <vector>

//classe che rappresenta la tabu list utilizzata nell'algoritmo tabu search

class TabuList
{
    std::vector<Mossa> Tlist; //Lista di mosse
    int dimensione; //dimensione massima della lista
public:
    TabuList(int n){dimensione=n;}; // costruttore
    ~TabuList(); //distruttore
    void addElem(Mossa m); //aggiunge un elemento al termine della Tabu List
    std::vector<Mossa>* getTlist(){return &Tlist;}; //ritorna la lista delle mosse
    
    
};



#endif