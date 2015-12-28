//classe che rappresenta un elemento di un albero FSFD, ha puntatore al padre al primo figlio a sinistra e al primo fratello a destra. Permette di implementare alberi con un numero infinito di figli
template <class T>
class AlberoFSFDElem
{
    T* value;
    AlberoFSFDElem* p; //padre
    AlberoFSFDElem* FS; //figlio sinistro
    AlberoFSFDElem* FD; //fratello destro
public:
    AlberoFSFDElem(T* v){value=v; p=0; FS=0; FD=0;};
    AlberoFSFDElem(T* v, AlberoFSFDElem* padre){value=v; p=padre; FD=0; FS=0;};
    void setFD(AlberoFSFDElem* e){FD=e;};  //imposta valore di FD
    void setFS(AlberoFSFDElem* e){FS=e;}; //imposta valore di FS
    void setp(AlberoFSFDElem* e){p=e;}; //imposta il valore di padre
    void setvalue(T* v){value=v;}; //imposta il valore interno del nodo
    T* getvalue()const {return value;}; //ritorna il valore nel nodo
    AlberoFSFDElem* getp()const {return p;}; //ritorna un puntatore al padre del nodo
    AlberoFSFDElem* getFD() const {return FD;} //ritorna il figlio fratello destro del nodo
    AlberoFSFDElem* getFS() const {return FD;}; // ritorna il figlio sinistro del nodo
    
};