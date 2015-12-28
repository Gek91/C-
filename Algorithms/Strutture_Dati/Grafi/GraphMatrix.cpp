#include "GraphMatrix.h"

GraphMatrix::GraphMatrix(int n)
{
    M= new bool[n*n];
    n_Nodes=n;
    n_Edges=0;
    
}

////////////////////////////////////////////////////////////////////////////////////////////

GraphMatrix::~GraphMatrix()
{
    delete [] M;
}

void GraphMatrix::addEdge(int v1, int v2)
{
    try
    {
        if( v1>=n_Nodes || v2>=n_Nodes) //valori errati in v1 o v2
            throw 2;
        
        if(M[ v1 * n_Nodes + v2]==0) //controlla che non vi sia già
        {
            M[ v1 * n_Nodes + v2]=1; // se non c'è la inserisce
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

void GraphMatrix::printGraph()const
{
    for (int i=0; i<n_Nodes; i++)
    {
        for (int j=0; j<n_Nodes; j++)
        {
            cout<<M[i*n_Nodes + j] << " ";
        }
        cout<<"\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

void GraphMatrix::BFS(int s)const
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
        
        for (int i=0; i<n_Nodes; i++)//scorri la lista delle adiacenze di u
        {
            if (M[ u*n_Nodes + i ]==1) //se è un vicino
            {
                if(colorvector[i]==0) //se il vicino è bianco
                {
                    colorvector[i]=1; //colora di grigio
                    cout<< i << " ";
                    Q->Insert(i); //lo inserisce nella coda
                }
            }
        }
        colorvector[u]=2; //colora il nodo u di nero
    }
    cout<<"\n";
}

////////////////////////////////////////////////////////////////////////////////////////////

void DFS_Visit(bool *M, int *colorvector , int u, int n )
{
    colorvector[u]=1;
    cout<< u << " ";
    
    for (int i=0; i<n; i++)//scorri la lista delle adiacenze di u
    {
        if (M[ u*n + i ]==1) //se è un vicino
        {
            if(colorvector[i]==0) //se il vicino è bianco
            {
                DFS_Visit(M,colorvector,i,n);
            }
        }
    }
    colorvector[u]=2; //colora il nodo u di nero
}

void GraphMatrix::DFS(int s)const
{
    int *colorvector=new int[n_Nodes]; //vettore colore dei nodi: 0 bianco, 1 grigio, 2 nero
    for (int i=0; i<n_Nodes; i++)
    {
        colorvector[i]=0;
    }
    colorvector[s]=1; //inserisco il primo elemento nella coda
    DFS_Visit(M,colorvector,s,n_Nodes);
    cout<<"\n";
}

////////////////////////////////////////////////////////////////////////////////////////////

void TS_Visit(bool *M, int *colorvector ,Pila<int>* P,int u, int n)
{
    colorvector[u]=1;
    
    for (int i=0; i<n; i++)//scorri la lista delle adiacenze di u
    {
        if (M[ u*n + i ]==1) //se è un vicino
        {
            if(colorvector[i]==0) //se il vicino è bianco
            {
                TS_Visit(M,colorvector,P,i,n);
            }
        }
    }
    colorvector[u]=2; //colora il nodo u di nero
    P->Push(u);
}

Pila<int>* GraphMatrix::TS()const
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
            TS_Visit(M,colorvector,P, i, n_Nodes);
        }
    }
    return P;
}

////////////////////////////////////////////////////////////////////////////////////////////

void CFC_func_Visit(bool *M, int *colorvector,int u,int n )
{
    colorvector[u]=1;
    cout<<u<<endl;
    for (int i=0; i<n; i++)//scorri la lista delle adiacenze di u
    {
        if (M[ u*n + i ]==1) //se è un vicino
        {
            if(colorvector[i]==0) //se il vicino è bianco
            {
                CFC_func_Visit(M,colorvector,i,n);
            }
        }
    }
    colorvector[u]=2; //colora il nodo u di nero
}

void CFC_func(GraphMatrix* GT,Pila<int>* P)
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
            CFC_func_Visit(GT->getMatrix(),colorvector,v,GT->getNNodes());
        }
    }
}

void GraphMatrix::CFC()const
{
    Pila<int>* P=TS(); //Passo 1
    GraphMatrix* GT=traspose_Graph();
    CFC_func(GT,P);

}

////////////////////////////////////////////////////////////////////////////////////////////

GraphMatrix* GraphMatrix::traspose_Graph()const
{
    GraphMatrix* M2=new GraphMatrix(n_Nodes); //matrice risultante
    
    for (int i=0; i<n_Nodes; i++)
    {
        for (int j=0; j<n_Nodes; j++)
        {
            M2->M[ j*n_Nodes + i ]=M[ i*n_Nodes + j ]; //calcola l'elemento trasposto
        }
    }
    return M2;
}

