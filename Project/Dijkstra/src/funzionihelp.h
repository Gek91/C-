#include "strutture.h"
void inCoda(tail T,airport b) //Funzione che prende in input una coda(tail) e un aeroporto e inserisce nella coda l'aeroporto
{
    tail nT; //variabile tail ausiliaria
    nT=(tail) malloc(sizeof(struct coda));// alloco lo spazio per un elemento di tipo tail
    nT->elem=b; //inserisco l'elemento aeroporto preso in input dalla funzione nell'elemento
    nT->bck=T->bck; //inserisco l'elemento nella coda
    nT->nxt=T;
    (T->bck)->nxt=nT;
    T->bck=nT;
}
airport trova(graph G, char* name) // funzione che prende in input un grafo e il nome di un aeroporto e restituisce il puntatore all'elemento del grafo con quel nome
{
    airport a; //variabile aeroporto ausiliaria
    int find=0; //variabile booleana inizializzata a 0. utile per conoscere se un elemento è stato trovato
    a=(G->listOfAirport); //punto la lista dei nodi con una variabile aeroporto
    while(!find) //finche non trovo il nodo di nome desiderato scorro la lista
    {
        a=(a->nxt);
        if(!(strcmp(a->code,name)))
        {
            find=1;
        }
    }
    return a;
}
route creaPuntatoreStella() //funzione che crea la stella uscente di ogni nodo. restituisce un puntatore alla lista che comprende la stella uscente
{
    route nr;
    nr=(route) malloc(sizeof(struct edge_struct)); //alloco lo spazio per un arco e lo assegno alla variabile di supporto New Route
    nr->cost=0; //inizializzo il costo a 0
    nr->distance=0;//inizializzo la distanza a 0
    nr->prv=NULL; //pongo uguale a NULL il puntatore all'arco successivo
    return nr;
}
void resetVisitato(graph G)// funzione che riporta il tag visitato di tutti i nodi a 0;
{
    airport a; //variabile di supporto di tipo aeroporto

    a=(G->listOfAirport)->nxt; //estraggo dalla lista il primo elemento e lo faccio puntare dalla variabile di supporto a
    do
    {
        a->visitato=0;  //riporto a 0 la variabile visitato per tutti i nodi
        a=a->nxt;
    }while(a!=NULL);
}
void DFS(graph G, airport a) //esegue ricorsivamente la visita DFS di tutti i nodi di un grafo preso in input partendo dal nodo preso in input
{
    airport b; //variabile di supporto di tipo aeroporto
    route r; //variabile di supporto di tipo arco
    printf("Node ID:%d\nNode Code:%s \n\n",a->nodeid,a->code); //stampo il nodo ricevuto in input alla funzione
    a->visitato=1; //marco come visitato il nodo
    r=(a->starOut); //punto la stella uscente con la variabile di supporto arco
    while(r->prv!=NULL) //richiamo la funzione DFS per ogni adiacente del nodo non ancora visitato passando ogni adiacente come nodo di input alla funzione DFS
    {
        r=r->prv;
        b=r->nodeDst;
       if(b->visitato!=1)
        DFS(G,b);
    }
}
void helpdeledge(graph G,char *src,char *dst)// funzione di supporto a delEdge, prende in input gli stessi input di deledge
{
    int find; //variabile booleana
    airport a,b; //variabili di supporto di tipo aeroporto
    route r,h; //variabili di supporto di tipo arco
    a=trova(G,src); //trova il nodo con nome src
    r=a->starOut; //punto con la prima variabile arco la stella uscente del nodo trovato
    find=0; //pongo find=0
     while(!find) //fiche non trovo il valore con nome dst tengo traccia del nodo precedente e scorro la lista
    {
        h=r;
        r=(r->prv);
        b=(r->nodeDst);
        if(!(strcmp(b->code,dst)))
        {
            find=1;
        }
    }
    h->prv=r->prv;// aggiunsto il puntatore all'elemento successivo dell'elemento precedente a quello da eliminare ed elimino l'elemento desiderato
    free(r);

}
void stampaCammino(tree T) //funzione che stampa il cammino trovato scorrendo l'albero di copertura minimo creato dalla funzione findminpath
{
    if(T->father!=NULL)// se il padre è diverso da NULL
    {
        stampaCammino(T->father); //richiama la funzione sul padre
    }
        printf("Node ID:%d\nNode Code:%s\n\n",(T->elem)->nodeid,(T->elem)->code);// stampa l'elemento
}
tail creaCoda(graph G) //funzione che crea una coda ritorna un puntatore ad essa
{
    tail C; //variabile tail puntaore alla coda
    C=(tail) malloc(sizeof(struct coda)); //alloco lo spazio necessario ad un elemento tail e lo faccio puntare da C
    C->elem=G->listOfAirport; //inizializzo la sentinella
    C->nxt=C; //rendo la coda circolare
    C->bck=C;
    return C;
}
tree creaAlbero(graph G) // funzione che crea un albero e ritorna un puntatore ad esso
{
    tree T; //variabile puntatore all'albero
    T=(tree) malloc(sizeof(struct tree_struct));// alloco spazio necessario ad un elemento tree e lo faccio putnare da T
    T->elem=G->listOfAirport; // inizializzo la sentinella
    T->nxt=NULL;
    T->father=NULL;
    return T;
}
tree listapadri(graph G, tree T, char *src) //funzione che inizializza l'albero come lista di padri e ritorna la radice
{
    airport a; //variabile airport di supporto
    tree Tr,Th; //variabili tree di supporto
    a=G->listOfAirport;
    while(a->nxt!=NULL) //scorro tutto il grafo
    {
        a=a->nxt;
        Tr=(tree) malloc(sizeof(struct tree_struct)); //ogni elemento del grafo lo inserisco in un nuovo elemento dell'albero
        Tr->elem=a;
        Tr->nxt=T->nxt;
        T->nxt=Tr;
        if(!(strcmp(a->code,src))) //se l'elemento appena inserito è src lo rendo radice dell'albero
        {
            Tr->val=0;
            Th=Tr;
        }
        else
        Tr->val=INT_MAX; //se il nodo non è radice rendo la distanza da essa INT_MAX
    }
    return Th; //ritorno un puntatore alla radice
}
tree minFuoricoda(tree T,tail C) //funzione che prende il valore minimo della coda lo estrae e ritorna il puntatore all'elemento corrispondente dell'albero
{
    tree Tr,Th; //variabili ausiliarie di tipo tree
    tail Cr,Ch; //variabili ausiliarie di tipo tail
    int find;
    int min=INT_MAX; //variabile intera usata per memorizzare il valore dell'elemento minimo
    Tr=T;
        while(Tr->nxt!=NULL) //scorro l'albero
        {
            Tr=Tr->nxt;
            if((Tr->val)<min) //se il valore del nodo è minore di min
            {
                find=0;
                Cr=C;
                while(((Cr->nxt)->elem->nodeid!=0)&&(!find)) //scorro la coda finche o trovo l'elemento in essa o la termino
                {
                    Cr=Cr->nxt;
                    if((Tr->elem)->nodeid==(Cr->elem)->nodeid) //se l'elemento è presente nella coda
                    {
                        find=1;
                        min=Tr->val; //tengo traccia dell'elemento minimo
                        Th=Tr;
                        Ch=Cr;
                    }
                }
            }
        }
        Cr=Ch->nxt; //elimino dalla coda l'elemento minimo
        Cr->bck=Ch->bck;
        (Ch->bck)->nxt=Cr;
        return Th; //ritorno il puntatore all'elemento dell'albero corrispondente all'elemento minimo
}
void adiacenticosto(tree Th,tree T,tail C) //funzione che esegue le maggiori elaborazioni dell algoritmo di Dijkstra per i valori del costo
{
    airport b,a; //variabili ausiliarie airport
    int find; //variabile intera utilizzata come booleana
    route r; //variabile ausiliaria route utilizzata per scorrere la stella uscente
    tree Tr; // variabile ausiliaria tree
    tail Cr; //variabile ausiliaria tail
    a=Th->elem; //estraggo l'elemento dal nodo Th
    r=a->starOut;
    while(r->prv!=NULL) //visito tutta la stella uscente, per ogni elemento
        {
            r=r->prv;
            Tr=T;
            find=0;
            while(!find) //scorro l'albero finche non trovo l'elemento nodeDst
            {
                Tr=Tr->nxt;
                b=r->nodeDst;
                if((Tr->elem)->nodeid==b->nodeid)
                find=1;
            }
            if(((Th->val)+(r->cost))<Tr->val) //se il valore del nodo dell'albero da dove parte l'arco piu il valore dell'arco è minore del valore del nodo dell'albero destinatario dell'arco
            {
                Tr->val=Th->val+r->cost; //aggiorno il valore
                Tr->father=Th; // rendo il nodo dell'albero destinatario figlio del nodo da cui parto l'arco
                Cr=C;
                find=0;
                while(((Cr->nxt)->elem->nodeid!=0)&&(!find)) //scorro la coda controllando se il nodo appena aggiornato è presente in essa se non lo è lo inserisco
                {
                    Cr=Cr->nxt;
                    if((Cr->elem)->nodeid==(Tr->elem)->nodeid)
                    find=1;
                }
                if(!find)
                {
                    inCoda(C,Tr->elem);
                }
            }
        }
}
void adiacentidistanza(tree Th,tree T,tail C)  //funzione che esegue le maggiori elaborazioni dell algoritmo di Dijkstra per i valori della distanza
{
    airport b,a;
    int find;
    route r;
    tree Tr;
    tail Cr;
    a=Th->elem;
    r=a->starOut;
    while(r->prv!=NULL)
        {
            r=r->prv;
            Tr=T;
            find=0;
            while(!find)
            {
                Tr=Tr->nxt;
                b=r->nodeDst;
                if((Tr->elem)->nodeid==b->nodeid)
                find=1;
            }
            if(((Th->val)+(r->distance))<Tr->val)
            {
                Tr->val=Th->val+r->distance;
                Tr->father=Th;
                Cr=C;
                find=0;
                while(((Cr->nxt)->elem)->nodeid!=0)
                {
                    Cr=Cr->nxt;
                    if((Cr->elem)->nodeid==(Tr->elem)->nodeid)
                    find=1;
                }
                if(!find)
                {
                    inCoda(C,Tr->elem);
                }
            }
        }
}
void fuoriCoda(tail T) // funzione che estre un elmeneto dalla coda aggiornando i puntatori degli elementi adiacenti
{
        T->nxt=(T->nxt)->nxt;
        free((T->nxt)->bck);
        (T->nxt)->bck=T;
}
int findCoda(tail W,airport b,int find) //funzione che controlla se un elemento è presente nella coda data in input
 {
    tail nT;
    nT=W->nxt;
    while((nT->elem)->nodeid!=0)
    {
        if(b->nodeid==(nT->elem)->nodeid)
        find=1;
        nT=nT->nxt;
    }
    return find;
 }
void helpBFS(tail T, tail W,graph G)// funzione di supporto di listfodestination. data la coda non vuota estrae ogni elemento da essa inserendo i figli nella coda vuota. la funzione prende in input due code e il grafo
{
    int find,hid;
    airport a,b;
    route r;
    while(((T->bck)->elem)->nodeid!=0) //finche la coda T non è vuota
    {
    a=(G->listOfAirport);
        find=0;
        hid=((T->nxt)->elem)->nodeid; //metto il valore di nodeid nella variabile di supporto di tipo intero
        while(!find) //finche non trovo l'elemento con id=hid scorro la lista nodi del grafo
        {
            if((a->nxt)->nodeid==hid)
            {
                find=1;
            }
            a=(a->nxt);
        }
        a->visitato=1; //marco l'elemento come visitato e lo stampo
        printf("Node ID:%d\nNode Code:%s \n\n",a->nodeid,a->code);
        r=a->starOut; //nella variabile di supporto arco inserisco la stella uscente dell'elemento
        while(r->prv!=NULL) //scorro tutta la stella uscente controllando che ogni elemento sia o gia visitato o nelle code
        {
            find=0;
            r=r->prv;
            b=r->nodeDst;
            find=findCoda(T,b,find);
            find=findCoda(W,b,find);
             if((!b->visitato)&&(!find)) //se l'elemento non è ne visitato ne nelle code
            {
                inCoda(W,b);//inserisco l'elemento nella coda W
            }
        } //l'elemento che ho gia visistato viene estratto dalla coda
        fuoriCoda(T);
    }
}
