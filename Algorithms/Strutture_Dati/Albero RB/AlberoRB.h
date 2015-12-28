//classe che rappresenta un albero binario. elementi salvati seguendo la proprietà dell'albero di ricerca binario: dato un nodo x, il suo sottoalbero sinistro contiene tutti i valori <x e il sottoalbero desto contiene tutti gli elementi x<

#ifndef ALBERORB_H
#define ALBERORB_H

#include "AlberoRBElem.h"

using namespace std;

template <class T>
class AlberoRB
{
    AlberoRBElem<T>* root;
    void setroot(AlberoRBElem<T>* e){root=e;}; //imposta il valore di root
public:
    AlberoRB(){root=0;};
    
    AlberoRBElem<T>* getroot()const {return root;}; //ritorna il puntatore alla radice
    
    AlberoRBElem<T>* ricercaVal(T k) const; //ricerca di un valore k all'interno dell'albero implementando la three search. ritorna null se non esiste
    AlberoRBElem<T>* maxVal() const; //restituisce il valore minimo nell'albero
    AlberoRBElem<T>* minVal() const; //restituisce il valore massimo nell'albero
    void stampaAlberoRB()const; //stampa la lista degli elementi dell'albero implementando la visita in ordine simmetrico
    AlberoRBElem<T>* successoreVal(T k) const; //torna il successore del valore se esso esiste nell'albero. Ritorna errore se l'elmento non esiste, null se non ha successori
    AlberoRBElem<T>* predecessoreVal(T k) const; //torna il predecessore del valore se esso esisten nell'albero. Ritorna errore se l'elemento non esiste, null se non ha successori
    void insertElem(AlberoRBElem<T>* e); //inserisce un nuovo elemento. L'elemento non deve avere figli
    void deleteElem(T e); //elimina l'elemento con il valore passato se è presente nell'albero
    
    void left_Rotate(AlberoRBElem<T>* x); // operazioni di rotazione, necessarie per mantenere la struttura di RB albero in caso di inserimenti e delezioni O(1)
    void right_Rotate(AlberoRBElem<T>* x);
    
    
    
};

////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTAZIONI

template <class T>
void inorderThreeWalk(const AlberoRBElem<T>* x) //visita in ordine simmetrico
{
    if(x!=0)
    {
        inorderThreeWalk(x->getleft()); //stampa prima tutti gli elementi del sottoalbero sinistro
        cout<<*(x->getvalue())<<endl; //stampa l'elementp
        inorderThreeWalk(x->getright()); //stampa tutti gli elementi dell'albero destro
    }
}

template <class T>
void AlberoRB<T>::stampaAlberoRB() const
{
    inorderThreeWalk(root); //richiama la funzione inorderThreeWalk sulla radice
}

template <class T>
AlberoRBElem<T>* threeSearch( AlberoRBElem<T>* x,T k)
{
    T* val=x->getvalue();
    if(x==0 || k==*val) //se si è trovato l'elemento o non esiste
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
AlberoRBElem<T>* AlberoRB<T>::ricercaVal(T k) const
{
    return threeSearch(root,k); //richiama la funzione threeSearch sulla radice
}

template <class T>
AlberoRBElem<T>* threeMinimum( AlberoRBElem<T>* x) //calcola il minimo nel sottoalmebro con radice in x
{
    while (x->getleft()!=0)
    {
        x=x->getleft();
    }
    return x;
}

template<class T>
AlberoRBElem<T>* AlberoRB<T>::minVal() const //restitusice il nodo che non ha figli sinistri
{
    if(root!=0)
    {
        return threeMinimum(root); //richiama three minimum sulla radice
    }
    return 0;
}

template<class T>
AlberoRBElem<T>* threeMaximum(  AlberoRBElem<T>* x) //calcola il massimo nel sottoalbero con radice in x
{
    while (x->getright()!=0)
    {
        x=x->getright();
    }
    return x;
}

template<class T>
AlberoRBElem<T>* AlberoRB<T>::maxVal() const //restituisce il nodo che non ha figli destri
{
    if(root!=0)
    {
        return threeMaximum(root); //richiama threemaximum sulla radice
    }
    return 0;
}

template<class T>
AlberoRBElem<T>* threeSuccessor(AlberoRBElem<T>* x)
{
    if(x->getright()!=0) //se ha un sottoalbero destro, il successore sarà il minimo elemento in esso
        return threeMinimum(x->getright());
    AlberoRBElem<T>* y=x->getp();
    while(y!=0 && x==y->getright()) //altrimenti cerca il primo nodo tra gli avi che non sia il figlio destro di suo padre. Il padre sarà il successore
    {
        x=y;
        y=y->getp();
    }
    return y;
}

template<class T>
AlberoRBElem<T>* AlberoRB<T>::successoreVal(T k) const
{
    try
    {
        AlberoRBElem<T>* x=ricercaVal(k);
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

template<class T>
AlberoRBElem<T>* threePredecessor(AlberoRBElem<T>* x)
{
    if(x->getleft()!=0) //se ha un sottoalbero sinistro, il predecessore sarà il massimo elemento in esso
        return threeMaximum(x->getright());
    AlberoRBElem<T>* y=x->getp();
    while(y!=0 && x==y->getleft()) //altrimenti cerca il primo nodo tra gli avi che non sia il figlio sinistro di suo padre. Il padre sarà il successore
    {
        x=y;
        y=y->getp();
    }
    return y;
}

template<class T>
AlberoRBElem<T>* AlberoRB<T>::predecessoreVal(T k) const
{
    try
    {
        AlberoRBElem<T>* x=ricercaVal(k);
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

template <class T>
void AlberoRB<T>::left_Rotate(AlberoRBElem<T>* x)
{
    try
    {
        if(x->getright()==0)
            throw 1;
        
        AlberoRBElem<T>* y=x->getright(); //y <- x.right
        x->setright(y->getleft()); //x.right <- y.left
        
        if(y->getleft()!=0)
            y->getleft()->setp(x);  //y.left.p <- x
        
        y->setp(x->getp()); //y.p <- x.p
        if(x->getp()==0)    //se x era root
            setroot(y); //root <- y
        else if(x==x->getp()->getleft()) //altrimenti se x=x.p.left
            x->getp()->setleft(y); //x.p.left <- y
        else //altrimenti
            x->getp()->setright(y); //x.p.right <- y
        
        y->setleft(x); //y.left <- x
        x->setp(y);  //x.p <- y
    }
    catch (int e)
    {
        if(e==1)
            throw "Figlio destro null";
    }
}

template <class T>
void AlberoRB<T>::right_Rotate(AlberoRBElem<T>* x)
{
    try
    {
        if(x->getleft()==0)
            throw 1;
        
        AlberoRBElem<T>* y=x->getleft(); //y <- x.left
        x->setleft(y->getright()); //x.left <- y.right
        
        if(y->getright()!=0)
            y->getright()->setp(x);  //y.right.p <- x
        
        y->setp(x->getp()); //y.p <- x.p
        if(x->getp()==0)    //se x era root
            setroot(y); //root <- y
        else if(x==x->getp()->getright()) //altrimenti se x=x.p.right
            x->getp()->setright(y); //x.p.right <- y
        else //altrimenti
            x->getp()->setleft(y); //x.p.left <- y
        
        y->setright(x); //y.right <- x
        x->setp(y);  //x.p <- y
    }
    catch (int e)
    {
        if(e==1)
            throw "Figlio sinistro null";
    }
}

template<class T>
void AlberoRB<T>::insertElem(AlberoRBElem<T>* e)
{
    try
    {
        //Three insert normale
        if(e->getleft()!=0 || e->getright()!=0 ) //condizione di errore
            throw 1;
        AlberoRBElem<T>* x=root;
        AlberoRBElem<T>* y=0;
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
        //FINE Three insert
        //Parte aggiunta per gli alberi RB
        e->setcolor(1);
        while(e!=root && e->getp()->getcolor()!=1) //ricerca le violazioni alle proprietà dell'albero RB
        {
            if(e->getp()==e->getp()->getp()->getleft()) //padre di e è figlio sinistro
            {
                y=e->getp()->getp()->getright(); //zio di e
                if(y->getcolor()==1) //caso 1, zio rosso
                {
                    e->getp()->setcolor(0); //padre e nero
                    y->setcolor(0); //zio e nero
                    e->getp()->getp()->setcolor(1); //nonno e rosso
                    e=e->getp()->getp(); //x= nonno di x
                }
                else //zio nero
                {
                    if(e==e->getp()->getright()) //caso 2 e è figlio destro
                    {
                        e=e->getp();
                        left_Rotate(e); //trasformo il caso 2 nel caso 3
                    } //caso 3
                    e->getp()->setcolor(0); //padre e nero
                    e->getp()->getp()->setcolor(1); //nonno e rosso
                    right_Rotate(e->getp()->getp());
                }
            }
            else//padre di e è figlio destro
            {
                y=e->getp()->getp()->getleft();
                if(y->getcolor()==1) //caso 1
                {
                    e->getp()->setcolor(0);
                    y->setcolor(0);
                    e->getp()->getp()->setcolor(1);
                    e=e->getp()->getp();
                }
                else
                {
                    if(e==e->getp()->getleft()) //caso 2
                    {
                        e=e->getp();
                        right_Rotate(e);
                    } //caso 3
                    e->getp()->setcolor(0);
                    e->getp()->getp()->setcolor(1);
                    left_Rotate(e->getp()->getp());
                }
            }
        }
    }
    catch(int t)
    {
        if(t==1)
            throw "Elemento ha figli o ha valore null";
    }
}

template<class T>
void RB_Delete_Fixup(AlberoRB<T>* A, AlberoRBElem<T>* x) //ha il compito di ristabilire le proprietà dell rb albero dopo la delezione
{
    while(x != A->getroot() && x->getcolor()==0)
    {
        AlberoRBElem<T>* w;

        if(x==x->getp()->getleft()) //controlla se è figlio sinistro
        {
            w=x->getp()->getright(); //fratello di x
            if(w->getcolor()==1) // w è rosso, caso 1
            {
                w->setcolor(0);     //w nero
                x->getp()->setcolor(1); // padre x rosso
                A->left_Rotate(x->getp()); //rotazione a sinistra, nessuna proprietà viene violata
                w=x->getp()->getright(); //caso 1 è diventato uno dei casi 2,3,4
            } //w è nero
            if(w->getleft()->getcolor()==0 && w->getright()->getcolor()==0) //figli di 2 sono neri, caso 2
            {
                w->setcolor(1);     //w è rosso
                x=x->getp();
            }
            else
            {
                if(w->getright()->getcolor()==0) //figlio sinistro w è rosso, figlio destro è nero, caso 3
                {
                    w->getleft()->setcolor(0); //figlio sinistro w nero
                    w->setcolor(1); //w è rosso
                    A->right_Rotate(w); //rotazione a destra senza violare proprietà
                    w=x->getp()->getright();
                }
                w->setcolor(x->getp()->getcolor()); //figlio destro di w è rosso
                x->getp()->setcolor(0); // padre di x è nero
                if(w->getright()!=0)
                    w->getright()->setcolor(0); //figlio destro di w è nero
                A->left_Rotate(x->getp()); //rotazione a sinistra
                x=A->getroot();
            }
        }
        else //è figlio destro
        {
            w=x->getp()->getleft();
            if(w->getcolor()==1)
            {
                w->setcolor(0);     //caso 1
                x->getp()->setcolor(1);
                A->right_Rotate(x->getp());
                w=x->getp()->getleft();
            }
            if(w->getright()->getcolor()==0 && w->getleft()->getcolor()==0)
            {
                w->setcolor(1);     //caso 2
                x=x->getp();
            }
            else
            {
                if(w->getleft()->getcolor()==0)
                {
                    w->getright()->setcolor(0); //caso 3
                    w->setcolor(1);
                    A->left_Rotate(w);
                    w=x->getp()->getleft();
                }
                w->setcolor(x->getp()->getcolor()); //caso 4
                x->getp()->setcolor(0);
                if(w->getleft()!=0)
                    w->getleft()->setcolor(0);
                A->right_Rotate(x->getp());
                x=A->getroot();
            }
        }
    }
    x->setcolor(0);
}

template<class T>
void AlberoRB<T>::deleteElem(T k)
{
    AlberoRBElem<T>* z=ricercaVal(k); //z elemento da eliminare
    if(z!=0)
    {
        AlberoRBElem<T>* y;
        AlberoRBElem<T>* x;
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
        if(x != 0)
            x->setp(y->getp()); //padre di x figlio di y = padre di y
        
        if(y->getp()==0) //se y era la radice -> x diventa radice
            root=x;
        else //altrimenti
        {
            if(y == ( y->getp() )->getleft()) //aggiorno il puntatore dal padre di y ad x in relazione se y fosse figlio destro o sinistro
            {
                ( y->getp() )->setleft(x);
            }
            
            else
            {
                ( y->getp() )->setright(x);
            }
            
        }
        //se il nodo estratto è il successore di z (per il primo if) reinserisco il valore al posto di z che verrà eliminato
        if(y!=z)
            z->setvalue(y->getvalue());
        if(y->getcolor()==0)
            RB_Delete_Fixup(this,x);
        delete (y);
    }
}

#endif
