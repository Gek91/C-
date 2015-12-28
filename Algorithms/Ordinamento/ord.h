#include "../Strutture_Dati/Heap/Heap.h"
#include <cstdlib>
// insertionSort(array da riordinare, numero elementi nell'array);
template <typename T>
void insertionSort(T array[],T n);//ordina gli elementi dell'array simulando l'inserimento degli elementi non in ordine in un array gia ordinato che sarà la parte iniziale dell'array da ordinare. Prende l'elemento in posizione j e sposta tutti gli elementi precedenti a lui e già ordinati tra loro più grandi di lui di un posto finché non trova gli elementi più piccoli, in quel caso si inserirà nel posto lasciato libero dallo spostamento dei più grandi.

// heapsort(array da riordinare, numero elementi nell'array);
template <typename T>
void heapsort(T A[], T n);//costruisce un heap con buildHeap, poi riordina l'heap invertendo l'ultima posizione con la prima dell'array e decrementando la lunghezza dell'array di uno. Ad ogni passo esegue heapify in modo da ottenere il valore più alto tra quelli rimasti in A[1] in modo che dopo venga posizionato in fodo all'array preso in considerazione (decrementato)

template <typename T>
void scambia(T& i, T& j); //scambia i valori di due variabili

template <typename T>
int Partition(T A[], int p, int r);// funzione di supplemento a quicksort, ordina gli elementi in modo da avere tutti quelli più piccoli dell'elemento preso in considerazione prima di lui e tutti quelli più grandi dopo di lui. Ritorna poi la sua posizione

//quicksort(array da riordinare, indice primo elemento array , indice ultimo elemento);
template <typename T>
void quicksort(T A[],int p, int r); // richiama Partition che permette di suddividere l'array in due sottoarray in cui si trovano tutti gli elementi più piccoli in uno e più grandi nell'altro di un elemento di cui si è trovata la posizione. Riesegue poi quicksort su questi due sotto array p,q e q,r con q la posizione dell'elemento trovato

template <typename T>
void merge(T A[], int l, int c, int r);// funzione di supplemente al mergesort, unisce le due parti ordinate ottenute in un unico array ordinato

// mergesort(array da ordinare, indice di inzio, indice di fine)
template <typename T>
void mergesort(T A[], int l, int r); //algoritmo di ordinamento ricorsivo, divide in due metà in maniera ricorsiva l'array per poi ordinarle unendole attraverso la funzione merge

// countingsort(array da riordinare, numero elementi array ,valore maggiorante);
template <typename T>
void countingsort(T A[],int n,int k); // si passa in ingresso oltre all'array e alla sua dimensione un valore maggiorante di quelli contenuti nell'array (<k). Utilizza due vettori supplementari per ordinare l'array, C[i] conterrà il numero di elementi minori di i. in B viene ordinato il vettore, alla fine viene copiato

//void radixsort(int A[])

//void bucketsort()


///////////////////////////////////////////////////////////////////////////////////////////
//Implementazione
template <typename T>
void insertionSort(T A[],T n)
{
    int key;    //utilizzato per salvare l'elemento da ordinare
    for (int j=1;j<n ; j++) //ordina l'array iniziando dai primi elementi
    {
        key=A[j]; //prende l'elemento j
        int i=j-1;
        while(i>=0 && A[i]>key) //esplora la parte gia ordinata >j dell'array
        {
            A[i+1]=A[i]; //sposta gli elementi più grandi in avanti di un posto
            i=i-1;
        }
        A[i+1]=key; //mette al posto giusto l'elemento key dopo gli elementi più piccoli di lui
    }
}

///////////

template <typename T>
void heapsort(T A[], T n)
{
    Heap<T> H(A,n); // utilizza un oggetto Heap per gestire il tutto
    H.buildHeap(); //costruisce lo heap-> array ha proprietà heap
    int sizeheap=H.getsize();
    for(int i=H.getsize()-1; i>0; i--) //ripete l'esecuzione dell'algoritmo
    {
        H.scambia(0,i); //ordina il valore più grande che si troverà all'inizio dello heap
        H.setsize(H.getsize()-1); //poiché l'ultimo elemento è in ordine viene tolto dai passi successivi
        H.heapify(0);  //viene nuovamente formato uno heap-> valore più grande in testa
    }
    H.setsize(sizeheap);
}

//////////

template <typename T>
void scambia(T& i, T& j)
{
    T k=i;
    i=j;
    j=k;
}

template <typename T>
int Partition(T A[], int p, int r)
{
    T x=A[p];
    int i=p-1;
    int j=r+1;
    while(1)
    {
        while(A[--j]>x); // cerca il primo elemento più piccolo di x dal fondo
        while(A[++i]<x); // cerca il primo elemento più grande di x dall'inizio
        if(i<j)
        {
            scambia(A[i],A[j]); //scambia i due valori trovati, in modo da avere tutti gli elementi più grandi di x dopo di lui e quelli più piccoli prima di lui
        }
        else
        {
            return j; //posizione di x
        }
        
    }
}

template <typename T>
void quicksort(T A[],int p, int r)
{
    if (p<r)
    {
        int q=Partition(A,p,r); //trova la posizione dell'elemento A[p] che divide A in più grandi e più piccoli di lui
        quicksort(A,p,q); //esegue la stessa procedura sui due sotto array trovati
        quicksort(A,q+1,r);
    }
}

///////////////

template <typename T>
void merge(T A[], int l, int c, int r) //l indice sinistro, c indice centrale, r indice destro
{
    T* B=(T*) malloc(sizeof(T)*(r-l)); //vettore di appoggio
    int i=l;
    int j=c+1;
    int k=0;
    while((i<=c) && (j<=r)) //fusione delle due metà
    {
        if(A[i]<=A[j])
        {
            B[k]=A[i];
            i++;
        }
        else
        {
            B[k]=A[j];
            j++;
        }
        k++;;
    }
    while (i<=c) //se i minore di center significa che alcuni elementi della prima metà no sono stati inseriti nel vettore
    { //vengono aggiunti in coda
        B[k]=A[i];
        i++;
        k++;
    }
    while(j<=r)// se j minore di r significa che alcuni elementi della seconda metà non sono stati inseriti  nel vettore
    {
        B[k]=A[j];
        j++;
        k++;
    }
    for (k=l; k<=r; k++) //copio il vettore di appoggio B nel vettore A
    {
        A[k]=B[k-l];
    }
    free(B);
}

template <typename  T>
void mergesort(T A[], int l, int r) //l indice sinistro, r indice destro
{
    if (l<r)
    {
        int c=(l+r)/2; //centro del vettore
        mergesort(A,l,c); //chiama ricorsivamente sulla prima parte del vettore
        mergesort(A,c+1,r); //chiama ricorsivamente sulla seconda parte
        merge(A,l,c,r); //funzione di fusione delle metà ordinate
    }
}

//////////

template <typename T>
void countingsort(T A[],int n,int k) //k valore maggiorante degli elementi dell'array
{
    T* B=(T*) malloc (sizeof(T)*n);
    T* C=(T*) malloc (sizeof(T)*k);
    for(int i=0; i<k; i++)
    {
        C[i]=0;
    }
    for(int j=0; j<n; j++)
    {
        C[A[j]]=C[A[j]]+1;   //C contiene il numero di elementi con valore A[j]
    }
    for(int i=1; i<k; i++)
    {
        C[i]=C[i]+C[i-1]; //C contiene gli elementi minori o uguali ad i
    }
    for (int j=n-1; j>=0; j--)
    {
        B[C[A[j]]-1]=A[j];  //realizza il vettore risultato
        C[A[j]]=C[A[j]]-1;
    }
    for (int i=0; i<n; i++) //copia in A i valori di B
    {
        A[i]=B[i];
    }
    free(B);
    free(C);
}

