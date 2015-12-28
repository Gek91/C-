#include "PM.h"

int main()
{
    std::string P="TTAC";
    std::string T="GCTTACAGATTCAGTCTTACAGATGGT";
    //ingenuo(P,T);
    //ingenuoSentinella(P,T);
    /*int* prefissi=funzionePrefisso(T);
    
    for(int i=0;i<T.size();i++)
    {
        std::cout<<"prefisso "<<i<<":"<<prefissi[i]<<std::endl;
    }*/
    //matchingPrefisso(P,T);
    //KnuthMorrisPratt(P,T);
    
    BoyerMoore(P,T);
    
    Shift_And(P,T);
    return 0;
}