#ifndef LISTA_H
#define LISTA_H

#include "ListElem.h"

//classe che rappresenta una lista concatenata
template <class T>
class ListaConc
{
private:
    ListElem<T>* head; //puntatore all'inizio della lista
    int dim;            //dimensione della lista
protected:
    void incDim(){dim++;}//incrementa la dimensione
    void dimDim(){dim--;}//decrementa la dimensione
    void setHead(ListElem<T>* e){head=e;} //imposta il valore di head
public:
    ListaConc(){dim=0; head=0;} //costruttore
    ~ListaConc(); //distruttore
    ListElem<T>* getHead() const {return head;} //ritorna il puntatore alla lista
    int getDim() const {return dim;} //ritorna la dimensione della lista
        
    //funzioni applicabili sulla lista
    bool listaVuota() const;  //ritorna un booleano che indica se la lista è vuota o meno
    void addElem(T e); //aggiunge un elemento al termine della lista con il valore specificato
    void removeElem(T e); //rimuove tutti gli elementi della lista con il valore specificato
    ListElem<T>* searchElem(T e) const; //ritorna il puntatore al primo elemento della lista con il valore cercato
    void printList() const; //stampa gli elementi della lista in ordine
    //ALTRE POSSIBILI AGGIUNTE
};


///////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTAZIONI ListaConc

template <class T>
void delElem(ListElem<T>* elem)
{
    if(elem->getNxt()!=0)
        delElem(elem->getNxt());
    delete(elem);
}

template <class T>
ListaConc<T>::~ListaConc()
{
    delElem(head);
};

template <class T>
bool ListaConc<T>::listaVuota() const
{
    if(getDim()==0)
    {
        return true;
    }
    return false;
}

template <class T>
void ListaConc<T>::addElem(T e)
{
    if(getHead()==0) //se la lista è vuota
    {
        setHead(new ListElem<T>(e));
        incDim();
    }
    else //se non lo è
    {
        ListElem<T>* elem=getHead();
        ListElem<T>* nxt=elem->getNxt();
        while(nxt!=0) //scorrila fino al termine
        {
            elem=nxt;
            nxt=elem->getNxt();
        }
        elem->setNxt(new ListElem<T>(e)); //aggiungi in fondo alla lista l'elemento
        incDim();
    }
}

template <class T>
void ListaConc<T>::removeElem(T e)
{
    ListElem<T>* elem=getHead();
    ListElem<T>* previus=0;
    while(elem!=0) //finché non termini la lista
    {
        if(e==elem->getElem()) // se è l'elemento che si vuol eliminare
        {
            if(previus==0) //se è il primo
            {
                previus=elem;
                elem=elem->getNxt();
                setHead(elem);
                delete previus;
            }
            else
            {
                previus->setNxt(elem->getNxt()); //aggiorno il valore nxt dell'elemento precedente
                delete elem; //elimino il valore
                elem=previus->getNxt(); //continuo dal valore successivo a quello eliminato
            }
        }
        else //passo all'elemento successivo
        {
            previus=elem; // tengo traccia dell'elemento appena esaminato
            elem=elem->getNxt();
        }
    }
}

template <class T>
ListElem<T>* ListaConc<T>::searchElem(T e) const
{
    ListElem<T>* elem=getHead();
    while(elem!=0) //finché non termini la pila
    {
        if(elem->getElem()==e) //se è l'elemento cercato ritorna il puntatore ad esso
            return elem;
        elem=elem->getNxt(); //altrimenti passa al prossimo elemento
    }
    return 0;
}

template <class T>
void ListaConc<T>::printList() const
{
    ListElem<T>* elem=getHead();
    while(elem!=0) //scorre tutta la lista
    {
        std::cout<<elem->getElem()<<std::endl; //stampa il valore dell'elemento della lista
        elem=elem->getNxt(); //prossimo elemento
    }
}


#endif