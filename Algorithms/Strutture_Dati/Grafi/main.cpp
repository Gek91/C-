#include "GraphMatrix.h"
#include "GraphList.h"

int main()
{
    try
    {
        GraphList* G=new GraphList(8);
        G->addEdge(0,1);
        G->addEdge(0,4);
        G->addEdge(1,0);
        G->addEdge(1,5);
        G->addEdge(2,1);
        G->addEdge(2,6);
        G->addEdge(2,7);
        G->addEdge(3,2);
        G->addEdge(4,4);
        G->addEdge(5,4);
        G->addEdge(5,6);
        G->addEdge(6,5);
        G->addEdge(7,6);
        G->addEdge(7,3);

        G->printGraph();
        G->CFC();
        //G=G->traspose_Graph();
        //G->printGraph();
        //G->BFS(0);
        //G->DFS(0);
        //G->TS()->printPila();

        cout<<"\n\n";
        GraphMatrix* G1=new GraphMatrix(10);
         G1->addEdge(0,1);
         G1->addEdge(0,4);
         G1->addEdge(1,0);
         G1->addEdge(1,5);
         G1->addEdge(2,1);
         G1->addEdge(2,6);
         G1->addEdge(2,7);
         G1->addEdge(3,2);
         G1->addEdge(4,4);
         G1->addEdge(5,4);
         G1->addEdge(5,6);
         G1->addEdge(6,5);
         G1->addEdge(7,6);
         G1->addEdge(7,3);
        G1->printGraph();
        cout<<"\n\n";
        //G1->BFS(0);
        //G1->DFS(0);
        //G1->TS()->printPila();
        //G1=G1->traspose_Graph();
        //G1->printGraph();
        G->CFC();


    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    return 0;
}