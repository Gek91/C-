#ifndef ELEM_H
#define ELEM_H

//la classe descrive un elmento di una lista composto dal valore e dal puntatore al prossimo elemento

#include <iostream>
using namespace std;

template <class T>
class ListElem
{
    T elem;
    ListElem* nxt;
public:
    ListElem(T x, ListElem* y): elem(x), nxt(y){};   //costruttore con due argomenti in ingresso
    ListElem(T x):elem(x), nxt(0){}; //costruttore con un solo argomento
    ~ListElem(); //distruttore
    ListElem* getNxt(){return nxt;}; // ritorna il prossimo valore della pila
    T getElem(){return elem;};
    void setNxt(ListElem* e){nxt=e;}; //cambia il valore di next
};

template <class T>
ListElem<T>::~ListElem()
{
    elem.~T();
}

///////////////////////////////////////////////////////////////////////////////////////////////
//la classe descrive un elemento di una lista che eredita da ListElem aggiungendo il puntatore all'elemento precedente
template <class T>
class ListElemBi: public ListElem<T>
{
    ListElem<T>* prev;
public:
    ListElemBi(T x, ListElem<T>* y, ListElem<T>* z):ListElem<T>(x,y){prev=z;}; //costruttore a tre argomenti
    ListElemBi(T x): ListElem<T>(x){prev=0;}; //costruttore ad un solo argomento
    ListElem<T>* getPrev(){return prev;}; // ritorna un puntatore all'elemento precedente
    void setPrev(ListElem<T>* e){prev=e;}; //imposta il valore di prev
};


#endif