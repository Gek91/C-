//classe che rappresenta un un albero FSFD (fratello sinistro figlio destro)
#include "AlberoFSFDElem.h"

template <class T>
class AlberoFSFD
{
    AlberoFSFDElem<T>* root;
    void setroot(AlberoFSFDElem<T>* e){root=e;}; //imposta il valore di root
public:
    AlberoFSFD(){root=0;};
    
    void stampaAlberoFSFD()const; //stampa la lista degli elementi dell'albero
    
    
};