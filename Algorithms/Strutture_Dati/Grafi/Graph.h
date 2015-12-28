//definisco la classe astratta Graph che conterrà i metodi che i grafi dovranno implementare. I grafi sono orientati
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "../Coda/Coda.h"
#include "../Pila/Pila.h"


using namespace std;

class Graph
{
public:    
    virtual void addEdge(int v1, int v2)=0; //aggiunta di un arco, dal nodo di indice v1 al nodo di indice v2
    virtual void printGraph()const =0; //funzione per la stampa ordinata del grafo

    
    virtual void DFS(int s)const =0;  //Visita in ampiezza
    virtual void BFS(int s)const =0;  //Visita in profondità
    virtual Pila<int>* TS()const =0;  //Ricerca topologica
    virtual void CFC()const =0; //Componenti fortemente connese
    //virtual void CTR()const =0; //Chiusura transitiva
    //virtual Graph* traspose_Graph()const =0; //calcola il grafo trasposto
    
    
};

#endif