#ifndef SMATRIX_H
#define SMATRIX_H

#include "Matrix.h"

template <class T>
class SMatrix:public Matrix<T>
{
    int N;
public:
    SMatrix(int n):Matrix<T>(n,n){ N=Matrix<T>::W;}; //costruttore
    int getDim()const { return Matrix<T>::getNcol();}; //ritorna la dimensione della matrice
    
    //Operazioni su matrici quadrate
    int trace() const;//calcola la traccia della matrice quadrata
    //int det() const; //calcola il determinante della matrice
};

////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
int SMatrix<T>::trace() const
{
    int ret=0;
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            if(i==j)
                ret=ret + Matrix<T>::M[i*N+j]; //somma solo in caso di i=j
        }
    }
    return ret;
}



#endif
