#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>
#include <limits>
#include "Punto.h"
 //classe che rappresenta una possibile soluzione del TSP come una sequenza dei nodi che lo compongono.

class Solution
{
    std::vector<int> S; //vettore contenente l'ordine dei nodi nella soluzione
    double Val; //valore della soluzione
    
public:
    Solution(); //costruttore con in ingresso la lunghezza della soluzione    
    
    std::vector<int>* getSolution() {return &S;}; //ritorna un puntatore alla soluzione
    double getValSol() const {return Val;}; //ritorna il valore della soluzione
    void setValSol(double v) {Val=v;}; //aggiorna il valore della soluzione
    
    void insertElem(int p, const std::vector<double> &a); //inserisce nella soluzione un elemento seguendo le modalità della Farthest Inserition
    
    void stampasoluzione(FILE* f)  const; //stampa nel file la soluzione del problema
    
    void ricalcolaVal(const std::vector<double> &a); //esegue il ricalcolo di Val dopo la modifica dei valori in S
};

int indexToEdge(int j, int i); //funzione supplementare che traduce due indici di nodi nell'indice relativo all'arco tra i due



#endif