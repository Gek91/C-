#include "TabuList.h"

void TabuList::addElem(Mossa m)
{
    if(Tlist.size()>=dimensione) //se si è raggiunta la dimensione della lista elimino l'ultimo elemento
    {
        Tlist.pop_back();
    }
    std::vector<Mossa>::iterator it; //inserisco l'elemento in testa alla lista
    it = Tlist.begin();
    it = Tlist.insert ( it , m );
}

TabuList::~TabuList()
{
    for (int i=0; i<Tlist.size(); i++) //scorre tutta la lista
    {
        free(Tlist.at(i).getIndici()); //libera lo spazio relativo ad ogni mossa
    }
}