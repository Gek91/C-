//classe che rappresenta un elemento di un albero binario, ha puntatore al padre e ai due figli

#ifndef ALBEROBINELEM_H
#define ALBEROBINELEM_H

#include <iostream>

using namespace std;



template <class T>
class AlberoBinElem
{
    T* value;
    AlberoBinElem* p; //padre
    AlberoBinElem* left; //figlio sinistro
    AlberoBinElem* right; //figlio destro
public:
    AlberoBinElem(T* v){value=v; p=0; left=0; right=0;};
    AlberoBinElem(T* v, AlberoBinElem* padre){value=v; p=padre; left=0; right=0;};
    ~AlberoBinElem(); //distruttore
    void setleft(AlberoBinElem* e){left=e;};  //imposta valore di left
    void setright(AlberoBinElem* e){right=e;}; //imposta valore di right
    void setp(AlberoBinElem* e){p=e;}; //imposta il valore di padre
    void setvalue(T* v){value=v;}; //imposta il valore di value
    T* getvalue()const {return value;}; //ritorna il valore nel nodo
    AlberoBinElem* getp()const {return p;}; //ritorna un puntatore al padre del nodo
    AlberoBinElem* getleft() const {return left;} //ritorna il figlio sinistro del nodo
    AlberoBinElem* getright() const {return right;}; // ritorna il figlio destro del nodo
    
};

template <class T>
AlberoBinElem<T>::~AlberoBinElem()
{
    value.~T();
}

#endif