//Classe che implementa una coda utilizzando una lista concatenata
#ifndef CODA_H
#define CODA_H

#include "../Lista/ListaConc.h"
template <class T>
class Coda: public ListaConc<T>
{
    ListElem<T>* tail; //puntatore all'ultimo elemento della coda
public:
    Coda(){ ListaConc<T>(); tail=0; };
    ~Coda(){ ~ListaConc<T>(); tail=0; };
    int getCodaDim()const { return ListaConc<T>::getDim(); }; //ritorna la dimensione della pila
    
    void Insert(T e); //inserisce un elemento in fondo alla coda
    void Remove(); //elimina il primo elemento della coda
    T firstValue()const {return ListaConc<T>::getHead()->getElem(); }; //ritorna il valore del primo elemento della coda
    
    bool codaVuota(){ return ListaConc<T>::listaVuota();}; //ritorna se la coda è vuota o meno
    void printCoda() const { ListaConc<T>::printList();};
    
};

/////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTAZIONI

template <class T>
void Coda<T>::Insert(T e)
{
    if(ListaConc<T>::getHead()==0) //se la lista è vuota
    {
        ListaConc<T>::setHead(new ListElem<T>(e));
        ListaConc<T>::incDim();
        tail=ListaConc<T>::getHead();
    }
    else //se non lo è
    {
        tail->setNxt(new ListElem<T>(e)); //aggiungi in fondo alla lista l'elemento
        tail=tail->getNxt();
        ListaConc<T>::incDim();
    }
    
}

template <class T>
void Coda<T>::Remove()
{
    try
    {
        if(ListaConc<T>::listaVuota())
            throw 1;
        ListElem<T>* delElem=ListaConc<T>::getHead();
        ListaConc<T>::setHead(delElem->getNxt());
        delete delElem;
        ListaConc<T>::dimDim(); //aggiorna il valore di dimensione
    }
    catch (int t)
    {
        if(t==1)
            throw "Pila già vuota, non possibile eseguire il Pop";
    }
}

#endif