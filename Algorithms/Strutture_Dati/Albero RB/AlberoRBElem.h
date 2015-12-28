//classe che rappresenta un elemento di un albero binario, ha puntatore al padre e ai due figli
#ifndef ALBERORBELEM_H
#define ALBERORBELEM_H

#include <iostream>


template <class T>
class AlberoRBElem
{
    T* value;
    AlberoRBElem* p; //padre
    AlberoRBElem* left; //figlio sinistro
    AlberoRBElem* right; //figlio destro
    bool color; //colore 1=rosso 0=nero
    
public:
    
    AlberoRBElem(T* v){value=v; p=0; left=0; right=0;};
    ~AlberoRBElem();
    
    void setleft(AlberoRBElem* e){left=e;};  //imposta valore di left
    void setright(AlberoRBElem* e){right=e;}; //imposta valore di right
    void setp(AlberoRBElem* e){p=e;}; //imposta il valore di padre
    void setvalue(T* v){value=v;}; //imposta il valore di value
    void setcolor(bool c){color=c;}; //imposta il colore
    
    T* getvalue()const {return value;}; //ritorna il valore nel nodo
    AlberoRBElem* getp()const {return p;}; //ritorna un puntatore al padre del nodo
    AlberoRBElem* getleft() const {return left;}; //ritorna il figlio sinistro del nodo
    AlberoRBElem* getright() const {return right;}; // ritorna il figlio destro del nodo
    bool getcolor()const {return color;}; //ritorna il colore del nodo

};

//////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTAZIONI
template <class T>
AlberoRBElem<T>::~AlberoRBElem()
{
    //delete(value);
}

#endif
