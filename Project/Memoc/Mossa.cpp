#include "Mossa.h"

Mossa::Mossa(int n)
{
    indici=(int*) calloc (n,sizeof(int));
}

void Mossa::setIndice(int i, int n)
{
    indici[n]=i;
}
