#include "ListaConc.h"



int main()
{
    try
    {
        ListaConc<int>* f=new ListaConc<int>();
        cout<<"listavuota:"<<f->listaVuota()<<endl;
        f->addElem(2);
        f->addElem(1);
        f->addElem(2);
        f->printList();
        cout<<"Dim:"<<f->getDim()<<endl;
        ListElem<int>* e=f->getHead()->getNxt()->getNxt();
        delete(f);
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    return 0;
}