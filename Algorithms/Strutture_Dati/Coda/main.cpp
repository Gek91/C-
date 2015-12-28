#include "Coda.h"

#include <iostream>
using namespace std;

int main()
{
    try
    {
        Coda<int>* p=new Coda<int>();
        //cout<<p->getCodaDim()<<endl;
        p->Insert(10);
        p->Insert(1);
        p->Remove();
        p->printCoda();
        cout<<p->getCodaDim()<<endl;
        cout<<p->firstValue()<<endl;
        

    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    return 0;
}