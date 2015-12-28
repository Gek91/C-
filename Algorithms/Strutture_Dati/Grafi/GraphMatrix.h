#ifndef GRAPHM_H
#define GRAPHM_H
#include "Graph.h"

class GraphMatrix: public Graph
{
    bool *M; //matrice booleana
    int n_Edges; //numero archi
    int n_Nodes; //numero nodi
public:
    GraphMatrix(int n); //costruttore con numero di nodi
    ~GraphMatrix();     //distruttore
    
    int getNNodes()const {return n_Nodes;};
    int getNEdges()const {return n_Edges;};
    bool* getMatrix()const {return M;};
    
    void addEdge(int v1, int v2);   //aggiunta di un arco, dal nodo di indice v1 al nodo di indice v2
    void printGraph()const; //funzione per la stampa ordinata del grafo
    
    void DFS(int s)const;  //Visita in ampiezza
    void BFS(int s)const;  //Visita in profondità
    Pila<int>* TS()const;  //Ricerca topologica
    void CFC()const; //Componenti fortemente connese
    GraphMatrix* traspose_Graph()const; //Calcola il grafo trasposto

};

#endif