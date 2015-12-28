#include "AlberoBin.h"

#include <iostream>
using namespace std;

int main()
{
    try
    {
        AlberoBin<int>* A=new AlberoBin<int>();

        //RIFARE, modificato, ora riceve un puntatore
        /*AlberoBinElem<int>* e=new AlberoBinElem<int>(2);
        A->insertElem(e);
        e=new AlberoBinElem<int>(19);
        A->insertElem(e);
        e=new AlberoBinElem<int>(13);
        A->insertElem(e);
        e=new AlberoBinElem<int>(17);
        A->insertElem(e);
        e=new AlberoBinElem<int>(15);
        A->insertElem(e);
        e=new AlberoBinElem<int>(12);
        A->insertElem(e);
        e=new AlberoBinElem<int>(9);
        A->insertElem(e);
        e=new AlberoBinElem<int>(18);
        A->insertElem(e);
        e=new AlberoBinElem<int>(5);
        A->insertElem(e);*/
        
        A->stampaAlberoBin();
        
        cout<<"-"<<endl;
        cout<<"Max:"<<A->maxVal()->getvalue()<<endl;
        cout<<"Min:"<<A->minVal()->getvalue()<<endl;
        cout<<"Succ 12:"<<A->successoreVal(12)->getvalue()<<endl;
        cout<<"Pred 12:"<<A->predecessoreVal(12)->getvalue()<<endl;
        cout<<A->ricercaVal(12)->getvalue()<<endl;
        cout<<"-"<<endl;

        A->deleteElem(12);
        A->deleteElem(9);

        A->stampaAlberoBin();
        delete(A);

    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    return 0;
}