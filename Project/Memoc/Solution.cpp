#include "Solution.h"

Solution::Solution()
{
    Val=0;
}

/* insertElem
 * Inserisce nella soluzione un nuovo elemento p utilizzando la tecnica della Farthest Inserition. Ogni nodo è inserito nella soluzione in modo che il costo di inserimento sia il minimo per il valore totale della soluzione
 * - int p: elemento da inserire nella soluzione rappresentato dall'indice del nodo
 * - std::vector<double> &a: vettore contenente i valori degli archi del problema. Utile al calcolo della posizione di inserimento
 */
void Solution::insertElem(int p,const std::vector<double> &a)
{
    if(S.size()<2) //inserimento dei primi due elementi
    {
        S.push_back(p);
    }
    else //inserimento dei successivi secondo il metodo Farthest Insertion
    {
        double min=std::numeric_limits<double>::max();
        int imin=-1;
        for (int i=0; i<(S.size() -1); i++) //inserisce il nuovo nodo p tra i nodi i e j in modo che il costo di inserimento (Cip + Cpj - Cij) sia minimo
        {
            double value=a.at(indexToEdge(S[i],p)) + a.at(indexToEdge(S[i+1],p)) - a.at(indexToEdge(S[i],S[i+1])); //costo di inserimento
            if(value<min) //se il costo trovato è minore di precedentemente trovato aggiorna il valore di min e l'indice corrispondete
            {
                min=value;
                imin=i+1;
            }
        }
        //Eseguo il calcolo anche per la posizione tra l'ultimo e il primo
        double value=a.at(indexToEdge(S[0],p)) + a.at(indexToEdge(S[S.size()-1],p)) - a.at(indexToEdge(S[0],S[S.size() -1]));
        if(value<min) //se il costo trovato è minore di quello fin ora trovato aggiora il valore di min e l'indice corrispondete
        {
            min=value;
            imin=0;
        }
        
        std::vector<int>::iterator it = S.begin();
        S.insert(it+imin,p); //inserisce l'elemento nella posizione calcolata
        Val=Val+min; //aggiorna il valore della soluzione
    }
}

void Solution::stampasoluzione(FILE* f)  const   //stampa nel file la soluzione del problema
{
    fprintf(f,"%lf\n\n",Val); //stampa valore soluzione
    
    for (int i=0; i<S.size(); i++)
    {
        fprintf(f,"%d ",S.at(i)); //Stampa la sequenza dei nodi della soluzione, rappresentati dagli indici nel vettore che li contiene
    }
    fprintf(f,"\n\n");
}

void Solution::ricalcolaVal(const std::vector<double> &a)
{
    Val=a.at( indexToEdge( S.at(0) , S.at(S.size()-1) ) ); //inserisce l'arco dall'ultimo al primo
    for (int i=0; i < (S.size()-1) ; i++)
    {
        Val=Val + a.at( indexToEdge( S.at(i) , S.at(i+1) ) ); //inserisce tutti gli archi restanti
    }
}

/////////////////////////////////////////////////////////////////////////
//FUNZIONI SUPPLEMENTARI

int indexToEdge(int j, int i) //passati due indici relativi a due nodi nel vettore dei nodi calcola la posizione dell'arco tra i due nel vettore degli archi
{
    if(j>i)
        return (j)*(j-1) / 2 + i;
    else
        return (i)*(i-1) / 2 + j;
}

