#include "funzionihelp.h"

graph creagrafo() // Funzione che inizializza il grafo ponendo il numero dei nodi =0 e creando la sentinella alla lista dei nodi. restituisce un puntatore al grafo
{
    graph G;    //Grafo che verrà ritornato dalla funzione
    G=(graph) malloc(sizeof(struct graph_struct)); //alloco lo spazio necessario al grafo e lo faccio puntare dalla variabile grafo
    G->numberOfNodes=0; //inizializzo il numero dei nodi a 0
    G->id=0; // inizializzo il contatore degli id
    G->listOfAirport=malloc(sizeof(struct node_struct));//creo la sentinella della lista dei nodi
    (G->listOfAirport)->nodeid=G->id++; //id sentinella lo pongo a 00
    (G->listOfAirport)->nxt=NULL; //inizializzo in puntantore al prossimo elemento della lista a NULL
    return G;
}
void addNode(graph G,char *name) //funzione che aggiunge un nodo alla lista. Riceve in input la lista e il nome del nodo
{
    airport na; //New Airport, variabile anodo di supporto
    na=(airport) malloc(sizeof(struct node_struct));// alloco lo spazio per un nodo e assegno lo spazio alla variabile di supporto New airport
    na->code=name; //assegno il nome preso in inpunt dalla funzione alla variabile
    na->nodeid=G->id++; //assegno in numero id e lo incremento
    na->visitato=0; //inizializzao il tag visitato a 0
    na->starOut=creaPuntatoreStella(); // assegno alla stella uscente di New Airport l'arco New Route
    na->nxt=((G->listOfAirport)->nxt);// Inserico il nodo nel grafo aggiornando il puntatore al nodo successivo
    (G->listOfAirport)->nxt=na; //inserisco il nodo nel grafo come primo elemento della lista
    G->numberOfNodes++; //aggiorno il numero dei nodi
}
void listAirport(graph G,char *name) //funzione che tramite una visita DFS del grafo preso in input stampa a video tutti i nodi
{
    printf("Lista degli areoporti ottenuta con una DFS a partire da %s\n",name);
    airport a;//variabile di supporto di tipo aeroporto
    a=trova(G,name); // trovo il nodo con nome name
    DFS(G,a); //richiamo la funzione DFS sul grafo e sull'elemento desiderato
    resetVisitato(G); //resetto la variabile visitato per tutti i nodi
}
void deleteNode(graph G,char *name ) //funzione che elimina il nodo con il nome dato in input dal grafo dato in input
{
    airport a,b; //variabili di supporto di tipo aeroporto
    int find=0; //variabile booleana utile per inidicare se il nodo è stato trovato o meno, inizializzata a 0
    a=(G->listOfAirport); // punto con una variabile di supporto la lista dei nodi
    while(!find) //finche non ho trovato il nodo scorro la lista confrontando il nome di ogni nodo con quello preso in input
    {               // quando lo trovo tengo traccia del nodo precedente nell'altra variabile di supporto
        if(!(strcmp((a->nxt)->code,name)))
        {
            find=1;
            b=a;
        }
        a=(a->nxt);
    }
        b->nxt=(a->nxt); //aggiorno i puntatori dell'elemento precedente e successivo a quello da eliminare ed elimino l'elemento desiderato
        free(a);
         G->numberOfNodes--; //aggiorno il valore del numero dei nodi
}
void addEdge( graph G,char *from,char *to,int cost,int distance) //aggiunge un nodo alla stella uscente dei due nodi presi in input dalla funzione con costo e distanza stabilite.
{
    airport a,b; //variabili di supporto di tipo aeroporto
    route nr; //variabile di supporto New Route
    a=trova(G,from); //trovo il nodo con nome from
    nr=(route) malloc(sizeof(struct edge_struct)); //alloco memoria per un arco e la punto con la variabile new route
    nr->cost=cost; //inserisco il valore costo
    nr->distance=distance;// inserisco il valore distanza
    nr->prv=((a->starOut)->prv); //inserisco nella stella uscente del nodo l'arco appena creato
    (a->starOut)->prv=nr;
    b=trova(G,to); //trovo il nodo con nome to
    nr->nodeDst=b; // inserisco il nome del nodo di destinazione nell'arco
    nr=(route) malloc(sizeof(struct edge_struct)); //creo l'arco, lo inizializzo con i valori e lo inserisco nella stella uscente del nodo to
    nr->cost=cost;
    nr->distance=distance;
    nr->prv=((b->starOut)->prv);
    (b->starOut)->prv=nr;
    nr->nodeDst=a;
}
void delEdge(graph G,char *src,char *dst) //funzione che elimina l'arco che collega i due nodi di nome preso in input dalla funzione
{
    helpdeledge(G,src,dst); //richiamo la funzione di delete sul primo nodo
    helpdeledge(G,dst,src); //richiamo la funzione di delete sul secondo nodo
}
void findMinPath(graph G,char *src,char *dst, char *par) //trova il cammino minimo rispetto al costo tra i nodi stampando il cammino e il valore di esso
{
    int find; // variabile ausiliarie intera utilizzata come booleana
    tail C; //variabili tail. C è il puntatore alla coda, le altre due sono ausiliarie
    tree T,Th; //variabili tree. T è il puntatore all'albero, le altre due sono ausiliarie
    airport a;//variabili di supporto di tipo airport
    find=0;
    T=creaAlbero(G);// inizializzo l'albero
    C=creaCoda(G); // inizializzo la coda
    Th=listapadri(G,T,src); //inserisco nell'albero gli elementi organizzati come una lista di padri ponendo come radice l'elemento src;
    a=Th->elem; //inserisco l'elemento radice nella coda
    inCoda(C,a);
    while(((C->bck)->elem)->nodeid!=0) //finche la coda non è vuota
    {
        Th=minFuoricoda(T,C); //trova l'elemento minimo della coda lo legge lo elimina dalla coda e restituisce il puntatore nell'albero a quell'elemento
        if(!(strcmp(par,"costo"))) //se il cammino minimo è sul costo
        adiacenticosto(Th,T,C); //prende la stella uscente dell'elemento e confronta i valori degli archi con quelli attribuiti ai nodi dell'albero se tali valori sono minori modifica l'albero. se i nodi adiacenti non son presenti nella coda li inserisce
        else
        if(!(strcmp(par,"distanza")))// se il cammino minimo è sulla distanza
        adiacentidistanza(Th,T,C);
    }
    Th=T;
    find=0;
    while(!find) //cerca dst nell'albero
    {
        Th=Th->nxt;
        if(!(strcmp((Th->elem)->code,dst)))
        {
            find=1;
        }
    }
    printf("\nIl percorso di %s min tra %s al nodo %s e':%d\n",par,src,dst,Th->val);
    printf("Il cammino tra i due nodi e':\n");
    stampaCammino(Th); //stampa il cammino minimo dall'albero di copertura
    free(C);
}
void listDestinations(graph G,char *name) // funzione che effettua una visita bsf del grafo e stampando partendo dal nodo name i nodi in base alla distanza di hop da esso
{
    int i=0;//variabile intera contatore. utilizzata per indicare la distanza degli hop
    printf("Destinazioni raggiungibili da %s in ordine di distanza unitaria",name);
    printf("\n");
    tail T,W; //variabili tail che identificano le due code usate
    airport a; //variabili di supporto di tipo aeroporto
    T=creaCoda(G); //inizializzo la coda T
    W=creaCoda(G); //inizializzo la coda W
    a=trova(G,name); //trovo l'elemento nel grafo con nome name
    inCoda(T,a); //inserisco nella coda T l'elemento da cui partira la visita
    while((((T->bck)->elem)->nodeid!=0)||(((W->bck)->elem)->nodeid!=0)) //finche entrambe le code non sono vuote
    {
        printf("Hop %d\n",i);
        if((T->bck)->elem->nodeid==0) //se T è vuota passero alla funzione come prima coda W altrimenti viceversa. La prima coda passata sarà la coda da cui verranno estratti i nodi e la seconda sarà quella dove verranno inseriti i figli
            helpBFS(W,T,G);
        else
            helpBFS(T,W,G);
        i++; //aggiorno il contatore degli hop
    }
    free(T);// dealloco la memoria puntata da T
    free(W);//dealloco la memoria puntata da W
    resetVisitato(G); //resetto la variabile visitato di ogni elemento del grafo
}
