#ifndef PILA_H
#define PILA_H

#include "../Lista/ListaConc.h"
template <class T>
class Pila: public ListaConc<T>
{
    
public:
    int getPilaDim()const { return ListaConc<T>::getDim(); }; //ritorna la dimensione della pila
    
    void Push(T e); //inserisce un elemento in testa
    void Pop(); //elimina l'elemento in testa
    T Top()const;  //ritorna il valore dell'elemento in cima alla pila
    T Next_To_Top() const;
    bool pilaVuota()const { return ListaConc<T>::listaVuota();}; //ritorna se la pila è vuota o meno
    void printPila() const { ListaConc<T>::printList();};
};

/////////////////////////////////////////////////////////////////////////////
//IMPLEMENTAZIONI

template <class T>
void Pila<T>::Push(T e)
{
    ListElem<T>* newElem=new ListElem<T>(e,ListaConc<T>::getHead());
    ListaConc<T>::setHead(newElem);
    ListaConc<T>::incDim(); //aggiorna il valore di dimensione
}

template <class T>
void Pila<T>::Pop()
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

template <class T>
T Pila<T>::Top() const
{
    try
    {
        if(pilaVuota())//Se la lista non è vuota
            throw 1;
        return ListaConc<T>::getHead()->getElem();
    }
    catch (int t)
    {
        if(t==1)
            throw "Pila vuota";
    }
};

template <class T>
T Pila<T>::Next_To_Top() const
{
    try
    {
        if(pilaVuota())//Se la lista non è vuota
            throw 1;
        ListElem<T> *elem=ListaConc<T>::getHead()->getNxt();
        if(elem==0) //se ha un secondo elemento
            throw 2;
        return elem->getElem();
    }
    catch (int t)
    {
        if(t==1)
            throw "Pila vuota";
        if(t==2)
            throw "Non ha un secondo elemento";
    }
};

#endif