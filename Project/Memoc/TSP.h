#ifndef TSP_H
#define TSP_H
#include <ctime>
#include <math.h>

#include "Solution.h"
#include "TabuList.h"

//classe che rappresenta un problema, contiene un vettore con i punti e un vettore con  valori degli archi
class TSP{
    int numero_punti; //numero dei punti del problema
    std::vector<Punto> lista; //vettore che contiene la lista di tutti i nodi
    std::vector<double> archi; //vettore che contiene il valore di ogni arco ordinati per distanza dal nodo i ai precedenti a partire dal nodo 1 fino a i-1
public:
    TSP(int n){numero_punti=n;} //crea un TSP definendo il numero di punti al suo interno
    std::vector<double>* getarchi() {return &archi;}; //ritorna un puntatore al vettore degli archi
    std::vector<Punto>* getlista() {return &lista;}; //ritorna un puntatore al vettore dei nodi
    int get_n_punti() const {return numero_punti;} //ritorna il numero di punti nel problema
    
    bool inseriscinodo(Punto p);  //inserisce il nodo con il valore stabilito nella lista, torna true se l'operazione va a buon fine
    
    // Tipologie di design per il posizionamento dei punti nel TSP
    void randomdesign();    //crea il problema posizionando i punti in modo casuale
    void clusterdesign();   //crea il problema generando due cluster in due posizioni casuali
    void lineardesign();    //distribuzioni dei punti su una retta definita dai primi due punti generati casualmente
    void circledesign();    //distribuisce i punti su una circonferenza con centro random e raggio random
    
    //Funzioni per lastampa delle informazioni su file
    void stampanodi(FILE* plot) const; //salva sul file in ingresso i valori relativi ai punti del TSP
    void stampaarchi(FILE* f) const; //salva sul file in ingresso i valori relativi agli archi del TSP
    
    //Funzioni per la risoluzione del TSP
    Solution* resolveTSP(int n_ripartenze, bool opt) const; //Genera una soluzione iniziale attraverso initSolution, a partire da essa esegue delle ricerche di vicinato applicando perturbazioni in modo da calcolare altri minimi locali.
    
    Solution* initSolution() const; //inizializza la soluzione del TSP

    Solution* TabuSearch(int dim, int maxiter ,bool opt) const; //genera la soluzione iniziale attraverso initSolution, a partire da essa esegue una ricerca di vicinato utilizzando la tecnica della tabu search
};

#endif