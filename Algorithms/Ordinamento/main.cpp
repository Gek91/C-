#include <iostream>
#include "ord.h"


int main()
{
    int A[10]={5,3,2,1,4,5,1,2,3,1};
    //heapsort(A,10);
    //insertionSort(A,10);
    //quicksort(A,0,9);
    //mergesort(A,0,9);
    countingsort(A,10,7);
    for (int i=0; i<10; i++)
    {
        std::cout<<A[i]<<std::endl;
    }

    return 0;
}