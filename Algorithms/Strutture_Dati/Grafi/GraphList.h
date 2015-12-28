//Implementa il grafo come lista di liste
#ifndef GRAPHL_H
#define GRAPHL_H
#include "Graph.h"
#include "../Lista/ListaConc.h"

class GraphList: public Graph
{
    ListaConc<int>* G; //Array delle liste concatenate contenenti i nodi adiacenti ad ogni nodo
    int n_Edges; //numero archi
    int n_Nodes; //numero nodi
public:
    GraphList(int n); //costruttore con numero di nodi
    ~GraphList();
    
    int getNNodes()const {return n_Nodes;};
    int getNEdges()const {return n_Edges;};
    ListaConc<int>* getLista()const {return G;};
    
    void addEdge(int v1, int v2); //aggiunta di un arco, dal nodo di indice v1 al nodo di indice v2
    void printGraph()const; //stampa gli elementi con i suoi adiacenti
    
    void DFS(int s)const ;  //Visita in ampiezza
    void BFS(int s)const;  //Visita in profondità, i è l'indice nel nodo di partenza
    Pila<int>* TS()const;  //Ricerca topologica
    void CFC()const; //Componenti fortemente connese
    GraphList* traspose_Graph()const; //Calcola il grafo trasposto
};


#endif

