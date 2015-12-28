#include "GraphList.h"

GraphList::GraphList(int n)
{
    try
    {
        if(n<=0)         //grafo vuoto
            throw 1;
        n_Nodes=n;
        n_Edges=0;
        G=new ListaConc<int> [n];
    }
    catch(int e)
    {
        if(e==1)
            throw "Numero nodi <=0";
        
    }
}

GraphList::~GraphList()
{
    delete [] G;
}

////////////////////////////////////////////////////////////////////////////////////////////

void GraphList::addEdge(int v1, int v2)
{
    try
    {
        if( v1>=n_Nodes || v2>=n_Nodes) //valori errati in v1 o v2
            throw 2;
        
        ListaConc<int>* list=&G[v1];
        if( list->searchElem(v2)==0 ) //controlla che non vi sia già
        {
            list->addElem(v2); // se non c'è la inserisce
        }
        else //altrimenti torna errore
            throw 3;
        n_Edges++;
    }
    catch (int e)
    {
        if(e==2)
            throw "Indici dei nodi errati";
        if(e==3)
            throw "Arco esiste già";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

void GraphList::printGraph()const
{
    for(int i=0; i<n_Nodes;i++) //Per ogni vertice
    {
        cout<<i<<" --> ";
        ListaConc<int>* list=&G[i];
        ListElem<int>* elem=list->getHead();
        while( elem!=0) //stampa la lista delle adiacenze
        {
            cout<<elem->getElem()<<" ";
            elem=elem->getNxt();
        }
        cout<<"\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

void GraphList::BFS(int s)const
{
    int *colorvector=new int[n_Nodes]; //vettore colore dei nodi: 0 bianco, 1 grigio, 2 nero
    Coda<int>* Q=new Coda<int>(); //coda necessaria al bfs
    for (int i=0; i<n_Nodes; i++)
    {
        colorvector[i]=0;
    }

    colorvector[s]=1; //inserisco il primo elemento nella coda
    cout<< s << " ";
    Q->Insert(s);
    
    while (!Q->codaVuota()) //fino a quando la coda non è vuota
    {
        int u=Q->firstValue(); //estrai il primo elemento della coda u
        Q->Remove();
        
        ListaConc<int>* list= &G[u];
        ListElem<int>* elem=list->getHead();
        while(elem!=0) //scorri la lista delle adiacenze di u
        {
            int v=elem->getElem();
            if(colorvector[v]==0) //se il vicino è bianco
            {
                colorvector[v]=1; //colora di grigio
                cout<< v << " ";
                Q->Insert(v); //lo inserisce nella coda
            }
            elem=elem->getNxt();
        }
        colorvector[u]=2; //colora il nodo u di nero
    }
    cout<<"\n";
}

////////////////////////////////////////////////////////////////////////////////////////////

void DFS_Visit(ListaConc<int>* G, int *colorvector , int u )
{
    colorvector[u]=1;
    cout<< u << " ";

    ListaConc<int>* list= &G[u];
    ListElem<int>* elem=list->getHead();
    while(elem!=0) //scorri la lista delle adiacenze di u
    {
        int v=elem->getElem();
        if(colorvector[v]==0) //se il vicino è bianco
        {
            DFS_Visit(G,colorvector,v);
        }
        elem=elem->getNxt();
    }
    colorvector[u]=2; //colora il nodo u di nero
}

void GraphList::DFS(int s)const
{
    int *colorvector=new int[n_Nodes]; //vettore colore dei nodi: 0 bianco, 1 grigio, 2 nero
    for (int i=0; i<n_Nodes; i++)
    {
        colorvector[i]=0;
    }
    colorvector[s]=1; 
    DFS_Visit(G,colorvector,s);
    cout<<"\n";
}

////////////////////////////////////////////////////////////////////////////////////////////

void TS_Visit(ListaConc<int>* G, int *colorvector ,Pila<int>* P, int u )
{
    colorvector[u]=1;
    ListaConc<int>* list= &G[u];
    ListElem<int>* elem=list->getHead();
    while(elem!=0) //scorri la lista delle adiacenze di u
    {
        int v=elem->getElem();
        if(colorvector[v]==0) //se il vicino è bianco
        {
            TS_Visit(G,colorvector,P,v);
        }
        elem=elem->getNxt();
    }
    colorvector[u]=2; //colora il nodo u di nero
    P->Push(u);
}

Pila<int>* GraphList::TS()const
{
    int *colorvector=new int[n_Nodes]; //vettore colore dei nodi: 0 bianco, 1 grigio, 2 nero
    for (int i=0; i<n_Nodes; i++)
    {
        colorvector[i]=0;
    }
    Pila<int>* P=new Pila<int>();
    for (int i=0; i<n_Nodes; i++) //scorre tutti i nodi
    {
        if(colorvector[i]==0)
        {
            TS_Visit(G,colorvector,P, i);
        }
    }
    return P;
}

////////////////////////////////////////////////////////////////////////////////////////////

void CFC_func_Visit(ListaConc<int>* G, int *colorvector,int u )
{
    colorvector[u]=1;
    cout<<u<<endl;
    ListaConc<int>* list= &G[u];
    ListElem<int>* elem=list->getHead();
    while(elem!=0) //scorri la lista delle adiacenze di u
    {
        int v=elem->getElem();
        if(colorvector[v]==0) //se il vicino è bianco
        {
            CFC_func_Visit(G,colorvector,v);
        }
        elem=elem->getNxt();
    }
    colorvector[u]=2; //colora il nodo u di nero
}

void CFC_func(GraphList* GT,Pila<int>* P)
{
    int *colorvector=new int[GT->getNNodes()]; //vettore colore dei nodi: 0 bianco, 1 grigio, 2 nero
    for (int i=0; i<GT->getNNodes(); i++)
    {
        colorvector[i]=0;
    }
    while(!(P->pilaVuota()))
    {
        int v=P->Top();
        P->Pop();
        if(colorvector[v]==0)
        {
            cout<<"Componente\n";
            CFC_func_Visit(GT->getLista(),colorvector,v);
        }
    }
}

void GraphList::CFC()const
{
    Pila<int>* P=TS(); //Passo 1
    GraphList* GT=traspose_Graph();
    CFC_func(GT,P);
    
}

////////////////////////////////////////////////////////////////////////////////////////////

GraphList *GraphList::traspose_Graph()const
{
    GraphList *Trasp=new GraphList(n_Nodes);
    for (int i=0; i<n_Nodes; i++) //Per tutti i nodi nel grafo controlla la lista della adiacenze
    {
        ListaConc<int>* adiac=&G[i];
        ListElem<int>* elem=adiac->getHead();
        while( elem!=0) //Per ogni elemento in ogni lista di adiacenza aggiunge l'elemento a cui appartiene la lista alla loro lista di adiacenza
        {
            Trasp->G[elem->getElem()].addElem(i);
            elem=elem->getNxt();
        }
    }
    return Trasp;
}


