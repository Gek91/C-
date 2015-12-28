#include "funzioni.h"


int main()
{
 graph G;
G=creagrafo();
addNode(G,"1");
addNode(G,"2");
addNode(G,"3");
addNode(G,"4");
addNode(G,"5");
addNode(G,"6");
addNode(G,"7");
addNode(G,"8");
addEdge(G,"7","8",2,5);
addEdge(G,"5","7",2,5);
addEdge(G,"6","7",10,5);
addEdge(G,"3","7",40,5);
addEdge(G,"2","5",11,5);
addEdge(G,"4","6",14,5);
addEdge(G,"1","2",3,5);
addEdge(G,"1","3",10,5);
addEdge(G,"1","4",1,5);
listAirport(G,"1");
listDestinations(G,"1");
findMinPath(G,"1","8","distanza");
findMinPath(G,"1","8","costo");
exit(0);
}
