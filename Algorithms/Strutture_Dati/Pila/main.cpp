#include "Pila.h"

#include <iostream>
using namespace std;

int main()
{
    try
    {
        Pila<int>* p=new Pila<int>();
        p->Push(10);
        p->Push(11);
        p->Push(12);
        p->printPila();
        cout<<p->Top()<<endl;
        cout<<p->getPilaDim()<<endl;
        p->Pop();
        cout<<p->Top()<<endl;
        cout<<p->getPilaDim()<<endl;

    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    return 0;
}