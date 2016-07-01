#include <cmath>
#include <iostream>
using namespace std;
// classe che rappresenta un heap, in questo caso è utilizzato un array puntato da A e un intero che contiene la dimensione dell'array
template <class T>
class Heap
{
    T* A;    //puntatore all'array che realizza l'heap
    int n;      //dimensione array
public:
    Heap(T array[],int size);        //costruttore con specificata la grandezza dell'heap
    ~Heap(){free(A); }; //distruttore
    int getsize() const {return n;};
    void setsize(int size) { n = size; };
    T elem(int i) const {return A[i];};
    int parent(int i) const ;   //ritorna l'indice del padre del nodo
    int left(int i) const;  //ritorna il figlio sinistro del nodo
    int right(int i) const;    //ritorna il figlio destro del nodo
    void scambia(int i, int j); //scambia due elementi di posto
    void heapify(int i);  //la procedura mantiene le caratteristiche chiave dell'heap per un determinato i specificato-> Parent(i)>=A[i]
    void buildHeap(); // produce un heap a partire da un array non ordinato
    void printHeap(); //stampa gli elementi di heap
    
    
    //extract-max //operazioni di coda di priorità
    //insert
    
};

//////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTAZIONI

template <class T>
Heap<T>::Heap(T array[],int size)
{
    try
    {
        if(size<=0)
            throw 1;
        if(array==NULL)
            throw 2;
        n=size;
        A=array;
    }
    
    catch (int t) {
        if(t==1)
            throw "Dimensione heap errata";
        if(t==2)
            throw "Array vuoto";
    }
}

template <class T>
int Heap<T>::parent(int i) const
{
    try
    {
        if(i<0 || i>n-1)
            throw 1;
        return floor(i/2);
    }
    catch (int t)
    {
        if(t==1)
        throw "Indice errato";
    }
    return 0;
}

template <class T>
int Heap<T>::left(int i) const
{
    try
    {
        if(i<0 || i>n-1)
            throw 1;
        return 2*i+1;
    }
    catch (int t)
    {
        if(t==1)
        throw "Indice errato";
    }
    return 0;
}

template <class T>
int Heap<T>::right(int i) const
{
    try
    {
        if(i<0 || i>n-1)
            throw 1;
        return (2*i)+2;
    }
    catch (int t)
    {
        if(t==1)
        throw "Indice errato";
    }
    return 0;
}

template <class T>
void Heap<T>::scambia(int i, int j)
{
    T k=A[i];
    A[i]=A[j];
    A[j]=k;
}

template <class T>
void Heap<T>::heapify(int i) //inverte il valore di i con uno il valore più grande tra i suoi due figli se hanno valore più alto di lui
{
    try
    {
        if(i<0 || i>n-1)
            throw 1;
        int l=left(i);
        int r=right(i);
        T largest;
        if((l<getsize()) && (A[l]>A[i])) //prende quello con valore più grande tra i e l
            largest=l;
        else
            largest=i;
        if((r<getsize()) && (A[r]>A[largest])) //prende quello con valore più grande tra i l e r
            largest=r;
        if(largest!=i)
        {
            scambia(i,largest); //scambia di posizione i con quello con il valore più grande trovato
            heapify(largest);   //riesegue il metodo dall'indice del valore più grande trovato che ora conterra il valore che era in i
        }
    }
    catch (int t)
    {
        if(t==1)
            throw "Indice errato";
    }
}

template <class T>
void Heap<T>::buildHeap() //esegue heapify a partire da metà heap fino all'inizio, ciò permette di costruire un heap
{
    for(int i=floor(getsize()/2);i >= 0; i--)
    {
        heapify(i);
    }
}

template <class T>
void Heap<T>::printHeap()
{
    for (int i=0; i<n; i++)
    {
        cout<<"Elemento "<<i<<":"<<A[i]<<endl;
    }
}

