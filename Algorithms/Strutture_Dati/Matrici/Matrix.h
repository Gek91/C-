#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Matrix
{
protected:
    T* M; //puntatore all'array che contiene la matrice
    int W; //numero colonne
    int L; //numero righe
public:
    Matrix(int l, int w); //costruttore che riceve in ingresso la dimensione della matrice
    ~Matrix() { delete[] M;}; //distruttore
    Matrix(const Matrix<T>& mat ); //costruttore di copia
    
    //funzioni di get
    int getNcol()const { return W;}; //ritorna il numero di colonne
    int getNrow()const { return L;}; //ritorna il numero di righe
    T* getMatrix()const { return M;}; //ritorna il puntatore al vettore che contiene gli elementi della matrice
    
    void printMatrix() const; //stampa il contenuto della matrice

    //Inserimento elementi
    void setElem(int posr, int posc , T elm); //inserisce un elemento nella posizione specificata da posr (0...L-1) e posc(0...W-1)
    void setRow(int row , vector<T>& elem); //inserisce i valori di una riga nella riga specificata da row(0...W-1)
    void setCol(int col , vector<T>& elem); //inserisce i valori di una colonna nella colonna specificata da col(0...L-1)
    
    //Operazioni su matrici
    Matrix* sumMatrix(const Matrix<T>* M2)const; //somma la matrice per un altra passata come parametro, ritorna la nuova matrice somma
    Matrix* scalarMul(const T& scalar)const ; //moltiplica ogni elemento della matrice per uno scalare, ritorna la matrice risultante
    Matrix* transp()const ; //calcola la matrice trasposta, ritorna la matrice risultante
    Matrix* multMatrix(const Matrix<T>* M2) const;
    
    //Operazioni su righe e colonne
    Matrix* rowSwitch(int r1, int r2) const; //inverte la posizione di due righe, ritorna la matrice risultante
    Matrix* colSwitch(int c1, int c2) const;
    Matrix* multRow(int r, const T& scalar)const;//moltiplica una colonna per un valore scalare, ritorna la matrice risultante
    Matrix* multCol(int c, const T& scalar)const;
   
    Matrix* submatrix(int r,int c) const; // crea una sottomatrice eliminando la riga r e/o la colonna c. Se utilizzo valori r=L o c=W non elimina niente, e non verifica errore. Ritorna la matrice risultante
};
/////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
Matrix<T>::Matrix(int l, int w)
{
    try
    {
        if(w<=0 || l<=0)
            throw 1;
        W=w;
        L=l;
        M=new T[W*L];
    }
    catch (int t)
    {
        if(t==1)
            throw "Indice riga o colonna errato";
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& mat )
{
    W=mat.getNcol();
    L=mat.getNrow(); //copia i valori di grandezza della matrice
    T* vect=mat.getMatrix();
    M=new T[W*L]; //inizializza il vettore
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<W; j++)
        {
           M[ i*W + j ]=vect[ i*W + j ]; //copia i valori all'interno del vettore
        }
    }
}

template <class T>
void Matrix<T>::printMatrix() const
{
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<W; j++)
        {
            cout<< M[ i*W + j ]<<" ";
        }
        cout<< "\n";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//OPERATORI DI INSERIMENTO ELEMENTI

template <class T>
void Matrix<T>::setElem(int posr, int posc , T elm)
{
    try
    {
        if(posr>L-1 || posr<0) //controllo indici utilizzati per l'inserimento
        {
            throw 1;
        }
        if (posc>W-1 || posc<0 )
        {
            throw 2;
        }
        M[ W*posr + posc ]=elm;
    }
    
    catch (int t) //torna la stringa di errore
    {
        if (t==1)
        {
             throw "Indice riga errato";
        }
        else
        {
            throw "Indice colonna errato";
        }
    }
}

template <class T>
void Matrix<T>::setRow(int row , vector<T>& elem)
{
    try
    {
        if(elem.size()<W || elem.size()>W) //controllo sulla dimensione della colonna dei valori
            throw 1;
        for (int i=0; i<W; i++)
        {
            setElem(row,i, elem.at(i));
        }
    }
    
    catch (int t) //torna la stringa di errore
    {
        if(t==1)
        {
            throw "Dimensione riga errata" ;
        }
    }
}

template <class T>
void Matrix<T>::setCol(int col , vector<T>& elem)
{
    try
    {
        if(elem.size()<L || elem.size()>L) //controllo sulla dimensione della riga dei valori
            throw 1;
        for (int i=0; i<L; i++)
        {
            setElem(i,col, elem.at(i));
        }
    }
    
    catch (int t) //torna la stringa di errore
    {
        if(t==1)
        {
            throw "Dimensione colonna errato" ;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//OPERAZIONI TRA MATRICI
template <class T>
Matrix<T>* Matrix<T>::sumMatrix(const Matrix<T>* M2) const
{
    try
    {
        if(M2->getNcol()!=W || M2->getNrow()!=L)
        {
            throw 1;
        }
        Matrix<T>* M3=new Matrix<T>(L,W); //matrice risultante
        T* vec=M2->getMatrix(); // prendo il vettore che implementa la seconda matrice
        
        for (int i=0; i<L; i++)
        {
            for (int j=0; j<W; j++)
            {
                M3->setElem(i,j,M[ i*W + j ] + vec[ i*W + j ]); //ogni elemento nella matrice risultante avrà valore pari alla somma degli elementi in quella posizione nelle due matrici della somma
            }
        }
        return M3;
    }
    
    catch (int t)
    {
        if(t==1)
        {
            throw "Dimensioni matrici diverse";
        }
    }
    return NULL;
}

template <class T>
Matrix<T>* Matrix<T>::scalarMul(const T& scalar) const
{
    try
    {
        if(scalar==NULL)
            throw 1;
        Matrix<T>* M2=new Matrix<T>(L,W); //matrice risultante
        
        for (int i=0; i<L; i++)
        {
            for (int j=0; j<W; j++)
            {
                M2->setElem(j,i,M[ i*W + j ] * scalar); //ogni elemento della matrice risultante avrà valore pari all'elemento della matrice M moltiplicato per lo scalare
            }
        }
        return M2;
    }
    
    catch (int t)
    {
        if(t==1)
            throw "Valore scalare nullo";
    }
    return NULL;
}

template <class T>
Matrix<T>* Matrix<T>::transp() const
{
    Matrix<T>* M2=new Matrix<T>(W,L); //matrice risultante
    
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<W; j++)
        {
            M2->setElem(j,i,M[ i*W + j ]); //calcola l'elemento trasposto
        }
    }
    return M2;
}

template <class T> //funzione supplementare per il calcolo del prodotto tra matrici. Riceve in ingresso:
/*
 - M1 ed M2: vettori contenenti la prima e la seconda matrice
 - i ed j: indici della cella da calcolare 
 - W1 ed W2: dimensioni delle righe delle due matrici. W1 è anche la dimensione comune alle due matrici (colonne prima matrice, righe seconda matrice)
 Ritorna il valore di: sum k=1..W di M1[i,k] * M2[k,j]
 */
int Calcval(const T* M1,const T* M2,int i,int j,int W1,int W2 )
{
    int res=0;
    for (int k=0; k<W1; k++)
    {
        res=res + (M1[ i*W1 + k ] * M2[ k*W2 + j ]); //sum k=1..W di M1[i,k] * M2[k,j]
    }
    return res;
}

template <class T>
Matrix<T>* Matrix<T>::multMatrix(const Matrix<T>* M2) const
{
    try
    {
        if(W!=M2->getNrow())
            throw 1;
        Matrix<T>* M3=new Matrix<T>(L,M2->getNcol()); //matrice risultante
        for (int i=0; i<L ; i++)
        {
            for (int j=0; j<M2->getNcol() ; j++)
            {
                M3->setElem(i,j, Calcval(M,M2->getMatrix(),i,j,W,M2->getNcol())); //calcola il valore degli elementi della matrice risultante
            }
        }
        return M3;
    }
    
    catch (int t)
    {
        if(t==1)
        throw "Dimensioni delle matrici errate";
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//OPERAZIONI SU RIGHE/COLONNE
template <class T>
Matrix<T>* Matrix<T>::rowSwitch(int r1, int r2) const
{
    try
    {
        if(r1>L-1 || r1<0 || r2>L-1 || r2<0) //controllo sui parametri passati
            throw 1;
        for (int i=0; i<W; i++)
        {
            T varsup=M[r1*W + i]; //inverte ogni valore elemento per elemento aiutandosi con una variabile supplementare
            M[r1*W + i]=M[r2*W + i];
            M[r2*W + i]=varsup;
        }
    }
    
    catch (int t)
    {
        if(t==1)
            throw "Indici righe errati";
    }
    return NULL;
}

template <class T>
Matrix<T>* Matrix<T>::colSwitch(int c1, int c2) const
{
    try
    {
        if(c1>W-1 || c1<0 || c2>W-1 || c2<0) //controllo sui parametri passati
            throw 1;
        for (int i=0; i<L; i++)
        {
            T varsup=M[i*W + c1]; //inverte ogni valore elemento per elemento aiutandosi con una variabile supplementare
            M[i*W + c1]=M[i*W + c2];
            M[i*W + c2]=varsup;
        }
    }
    
    catch (int t)
    {
        if(t==1)
            throw "Indici colonne errati";
    }
    return NULL;
}

template <class T>
Matrix<T>* Matrix<T>::multRow(int r, const T& scalar)const
{
    try
    {
        if(r>L-1 || r<0) //controllo sui parametri passati
            throw 1;
        if(scalar==NULL)
            throw 2;
        for (int i=0; i<W ; i++)
        {
            M[W*r + i]=M[W*r + i] * scalar;
        }
    }
    
    catch (int t)
    {
        if(t==1)
            throw "Indice riga sbagliato";
        if(t==2)
            throw "Scalare nullo";
    }
    return NULL;
}

template <class T>
Matrix<T>* Matrix<T>::multCol(int c, const T& scalar)const
{
    try
    {
        if(c>W-1 || c<0) //controllo sui parametri passati
            throw 1;
        if(scalar==NULL)
            throw 2;
        for (int i=0; i<L ; i++)
        {
            M[i*W + c]=M[i*W + c] * scalar;
        }
    }
    
    catch (int t)
    {
        if(t==1)
            throw "Indice colonna sbagliato";
        if(t==2)
            throw "Scalare nullo";
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
Matrix<T>* Matrix<T>::submatrix(int r,int c) const
{
    try
    {
        if(r<0 || r>L) //controllo sui parametri in ingresso
            throw 1;
        if(c<0 || c>W)
            throw 2;
        int w=W;
        int l=L;
        if(r<L) //aggiornamento dimensioni matrice di ritorno
            l=l-1;
        if (c<W)
            w=w-1;
        Matrix<T>* M2=new Matrix<T>(l,w); //matrice di ritorno
        T* vect=M2->getMatrix(); //vettore della matrice di ritorno
        int k=0; //indice sulla matrice di ritorno
        for (int i=0;i<L ; i++ )
        {
            for (int j=0 ; j<W; j++)
            {
                if(i!=r && j!=c) //se l'elemento non è da eliminare
                {
                    vect[k]=M[i*W + j]; //copia l'elemento nella matrice di ritorno(direttamente nel vettore che la rappresenta)
                    k++; //elemento successivo in cui verrà salvato il valore
                }
            }
        }
        return M2;
    }
    
    catch (int t)
    {
        if(t==1)
            throw "Indice righe errato";
        if(t==2)
            throw "Indice colonne errato";
    }
    return NULL;
}

#endif

