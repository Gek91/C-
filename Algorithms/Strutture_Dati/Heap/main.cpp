#include "Heap.h"

int main()
{
    try
    {
        int A[10]={4,1,3,2,16,9,10,14,8,7};
        Heap<int>* h=new Heap<int>(A,10);
        h->buildHeap();
        h->printHeap();
    }
    catch (const char* msg)
    {
        cerr<<msg<<endl;
    }
    catch(...)
    {
        cerr<<"Eccezzione non gestita"<<endl;
    }
    
    return 0;
}