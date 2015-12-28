//#include "AlberoRB.h"
#include "AlberoRB.h"


using namespace std;

int main()
{
    try
    {
        AlberoRB<int>* A=new AlberoRB<int>();
        AlberoRBElem<int>* e=new AlberoRBElem<int>(1);
        A->insertElem(e);
        e=new AlberoRBElem<int>(10);
        A->insertElem(e);
        e=new AlberoRBElem<int>(12);
        A->insertElem(e);
        e=new AlberoRBElem<int>(14);
        A->insertElem(e);
        e=new AlberoRBElem<int>(7);
        A->insertElem(e);
        e=new AlberoRBElem<int>(9);
        A->insertElem(e);
        e=new AlberoRBElem<int>(5);
        A->insertElem(e);
        A->stampaAlberoRB();
        A->deleteElem(1);
        A->stampaAlberoRB();
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    return 0;
}