//classe che rappresenta un albero binario. elementi salvati seguendo la proprietà dell'albero di ricerca binario: dato un nodo x, il suo sottoalbero sinistro contiene tutti i valori <x e il sottoalbero desto contiene tutti gli elementi x<
#ifndef ALBEROBIN_H
#define ALBEROBIN_H

#include "AlberoBinElem.h"


template <class T>
class AlberoBin
{
    AlberoBinElem<T>* root;
    void setroot(AlberoBinElem<T>* e){root=e;}; //imposta il valore di root
public:
    AlberoBin(){root=0;};
    ~AlberoBin(){delete(root);}; //distruttore
    AlberoBinElem<T>* ricercaVal(T k) const; //ricerca di un valore k all'interno dell'albero implementando la three search. ritorna null se non esiste
    AlberoBinElem<T>* maxVal() const; //restituisce il valore minimo nell'albero
    AlberoBinElem<T>* minVal() const; //restituisce il valore massimo nell'albero
    void stampaAlberoBin()const; //stampa la lista degli elementi dell'albero implementando la visita in ordine simmetrico
    AlberoBinElem<T>* successoreVal(T k) const; //torna il successore del valore se esso esiste nell'albero. Ritorna errore se l'elmento non esiste, null se non ha successori
    AlberoBinElem<T>* predecessoreVal(T k) const; //torna il predecessore del valore se esso esisten nell'albero. Ritorna errore se l'elemento non esiste, null se non ha successori
    void insertElem(AlberoBinElem<T>* e); //inserisce un nuovo elemento. L'elemento non deve avere figli
    void deleteElem(T e); //elimina l'elemento con il valore passato se è presente nell'albero
    
    
    
    
};

////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTAZIONI
template <class T>
void inorderThreeWalk(const AlberoBinElem<T>* x) //visita in ordine simmetrico
{
    if(x!=0)
    {
        inorderThreeWalk(x->getleft()); //stampa prima tutti gli elementi del sottoalbero sinistro
        cout<<*(x->getvalue())<<endl; //stampa l'elemento
        inorderThreeWalk(x->getright()); //stampa tutti gli elementi dell'albero destro
    }
}

template <class T>
void AlberoBin<T>::stampaAlberoBin() const
{
    inorderThreeWalk(root); //richiama la funzione inorderThreeWalk sulla radice
}

////////// Search

template <class T>
AlberoBinElem<T>* threeSearch( AlberoBinElem<T>* x,T k)
{
    T* val=x->getvalue();
    if(x==0 || k==val) //se si è trovato l'elemento o non esiste
        return x;
    if (k<*val)
    {
        return threeSearch(x->getleft(),k); //se k<valore nodo attuale continua la ricerca nel sottoalbero sinistro
    }
    else
    {
        return threeSearch(x->getright(),k); //se k>valore nodo attuale continua la ricerca nel sottoalbero destro
    }
}

template<class T>
AlberoBinElem<T>* AlberoBin<T>::ricercaVal(T k) const
{
    return threeSearch(root,k); //richiama la funzione threeSearch sulla radice
}

////////// Min

template <class T>
AlberoBinElem<T>* threeMinimum( AlberoBinElem<T>* x) //calcola il minimo nel sottoalmebro con radice in x
{
    AlberoBinElem<T>* y=x;
    while (y->getleft()!=0)
    {
        y=y->getleft();
    }
    return y;
}

template<class T>
AlberoBinElem<T>* AlberoBin<T>::minVal() const //restitusice il nodo che non ha figli sinistri
{
    if(root!=0)
    {
        return threeMinimum(root); //richiama three minimum sulla radice
    }
    return 0;
}

/////////// Max

template<class T>
AlberoBinElem<T>* threeMaximum(  AlberoBinElem<T>* x) //calcola il massimo nel sottoalbero con radice in x
{
    AlberoBinElem<T>* y=x;
    while (y->getright()!=0)
    {
        y=y->getright();
    }
    return y;
}

template<class T>
AlberoBinElem<T>* AlberoBin<T>::maxVal() const //restituisce il nodo che non ha figli destri
{
    if(root!=0)
    {
        return threeMaximum(root); //richiama threemaximum sulla radice
    }
    return 0;
}

/////////// Successor

template<class T>
AlberoBinElem<T>* threeSuccessor(AlberoBinElem<T>* x)
{
    if(x->getright()!=0) //se ha un sottoalbero destro, il successore sarà il minimo elemento in esso
        return threeMinimum(x->getright());
    AlberoBinElem<T>* y=x->getp();
    while(y!=0 && x==y->getright()) //altrimenti cerca il primo nodo tra gli avi che non sia il figlio destro di suo padre. Il padre sarà il successore
    {
        x=y;
        y=y->getp();
    }
    return y;
}

template<class T>
AlberoBinElem<T>* AlberoBin<T>::successoreVal(T k) const
{
    try
    {
        AlberoBinElem<T>* x=ricercaVal(k);
        if(x==0)
            throw 1;
        return threeSuccessor(x); //se k esiste nell'albero ricerco il successore
    }
    catch (int t)
    {
        if(t==1)
            throw "Elemento non presente nell'albero";
    }
    return 0;
}

////////// Predecessor

template<class T>
AlberoBinElem<T>* threePredecessor(AlberoBinElem<T>* x)
{
    if(x->getleft()!=0) //se ha un sottoalbero sinistro, il predecessore sarà il massimo elemento in esso
        return threeMaximum(x->getleft());
    AlberoBinElem<T>* y=x->getp();
    while(y!=0 && x==y->getleft()) //altrimenti cerca il primo nodo tra gli avi che non sia il figlio sinistro di suo padre. Il padre sarà il successore
    {
        x=y;
        y=y->getp();
    }
    return y;
}

template<class T>
AlberoBinElem<T>* AlberoBin<T>::predecessoreVal(T k) const
{
    try
    {
        AlberoBinElem<T>* x=ricercaVal(k);
        if(x==0)
            throw 1;
        return threePredecessor(x); //se k esiste nell'albero ricerco il predecessore
    }
    catch (int t)
    {
        if(t==1)
            throw "Elemento non presente nell'albero";
    }
    return 0;
}

///////// Insert

template<class T>
void AlberoBin<T>::insertElem(AlberoBinElem<T>* e)
{
    try
    {
        if(e->getleft()!=0 || e->getright()!=0 || e->getvalue()==0) //condizione di errore
            throw 1;
        AlberoBinElem<T>* x=root;
        AlberoBinElem<T>* y=0;
        while(x!=0) //scorre l'albero fino a trovare un nodo con un figlio vuoto
        {
            y=x;
            if(*(e->getvalue()) < *(x->getvalue())) //se il valore è < x continuo nel sottoalbero sinistro
                x=x->getleft();
            else
                x=x->getright(); //altrimenti continuo nel sottoalbero destro
        }
        e->setp(y); //una volta trovata la posizione inserisco i valori nei puntatori padre
        if(y==0)
        {
            root=e;
        }
        else
        {
            if(*(e->getvalue()) < *(y->getvalue())) //e nei puntatori di figlio in relazione al valore
                y->setleft(e);
            else
                y->setright(e);
        }
    }
    catch(int t)
    {
        if(t==1)
            throw "Elemento ha figli o ha valore null";
    }
}

//////// Delete

template<class T>
void AlberoBin<T>::deleteElem(T k)
{
    AlberoBinElem<T>* z=ricercaVal(k); //z elemento da eliminare
    if(z!=0)
    {
        AlberoBinElem<T>* y;
        AlberoBinElem<T>* x;
        //z ha almeno un figlio y= successore di z altrimenti y=z
        if(z->getright()==0 && z->getleft()==0)
            y=z;
        else
            y=threeSuccessor(z);
         //se y ha figli, assegno il figlio di y ad x altrimenti assegno null
        if (y->getleft()!=0)
            x=y->getleft();
        else
            x=y->getright();
        //estrae il nodo y dall'albero modificando i puntatori
        if(x!=0)
            x->setp(y->getp()); //padre di x figlio di y = padre di y
        if(y->getp()==0) //se y era la radice -> x diventa radice
        {
            root=x;
        }
        else //altrimenti
        {
            if( y == ( y->getp() )->getleft() ) //aggiorno il puntatore dal padre di y ad x in relazione se y fosse figlio destro o sinistro
                ( y->getp() )->setleft(x);
            else
                ( y->getp() )->setright(x);
        }
        //se il nodo estratto è il successore di z (per il primo if) reinserisco il valore al posto di z che verrà eliminato
        if(y!=z)
        {
            z->setvalue(y->getvalue());
            //
        }
        y->setp(0);
        y->setleft(0);
        y->setright(0);
        delete (y);
    }
}

#endif
