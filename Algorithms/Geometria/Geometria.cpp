#include "Geometria.h"

int Angle_Left(Punto p0, Punto p1, Punto p2) //ogni punto ha proprie cordinate (x,y), P0 punto in comune tra i due vettori
{
    return (p1.getx()-p0.getx())*(p2.gety()-p0.gety()) - (p2.getx()-p0.getx())*(p1.gety()-p0.gety());   //prodotto vettoriale tra i due vettori P0P1 e P0P2
    // se ritorna un valore >0 l'angolo tra i vettori è orientato in senso antiorario
    // se ritorna un valore =0 i due segmenti sono collineari o almeno uno dei due è degenere
    // se ritorna un valore <0 l'angolo è orientato in senso orario
}

/////////////////////////////////////////////////////////////////////////////////////

int Turn_Left(Punto p0, Punto p1, Punto p2)
{
    int d=Angle_Left(p0,p1,p2);
    return d;
}

/////////////////////////////////////////////////////////////////////////////////////

bool Segments_Intersec(Punto p1, Punto p2, Punto p3, Punto p4) // dati due vettori
{
    int d1=Angle_Left(p3,p4,p1); //posizione di p1 rispetto al vettore p3p4
    int d2=Angle_Left(p3,p4,p2); //posizione di p2 rispetto al vettore p3p4
    int d3=Angle_Left(p1,p2,p3); //posizione di p3 rispetto al vettore p1p2
    int d4=Angle_Left(p1,p2,p4); //posizione di p4 rispetto al vettore p1p2
    if (d1==0 && d2==0 && d3==0 && d4==0)   //se i segmenti sono collineari, si controlla se i vettori si incontrano
    {
        bool r1a=( ( p2.getx() - p3.getx() ) * ( p1.getx() - p3.getx() ) )<=0; //controlla se p3 è in p1p2
        bool r1b=( ( p2.gety() - p3.gety() ) * ( p1.gety() - p3.gety() ) )<=0;
        bool r2a=( ( p2.getx() - p4.getx() ) * ( p1.getx() - p4.getx() ) )<=0; //controlla se p4 è in p1p2
        bool r2b=( ( p2.gety() - p4.gety() ) * ( p1.gety() - p4.gety() ) )<=0;
        bool r3a=( ( p4.getx() - p1.getx() ) * ( p3.getx() - p1.getx() ) )<=0; //controlla se p1 è in p3p4
        bool r3b=( ( p4.gety() - p1.gety() ) * ( p3.gety() - p1.gety() ) )<=0; //basta questo per verificare
        // se p1p2 è contenuto in p3p4
        return ((r1a && r1b )|| (r2a && r2b) || (r3a && r3b)); //ritorna true se i segmenti si intersecano, false altrimenti
    }
    else //se non sono collineari
    {
        bool r4=(d1<=0 && d2>=0) || (d1>=0 && d2<=0); //se stanno da parti opposte p1 e p2
        bool r5=(d3<=0 && d4>=0) || (d3>=0 && d4<=0); //se stanno da parti opposte p3 e p4
        
        return (r4 && r5); // Se stanno da parti opposte in entrambe i casi i segmenti si intersecano altrimenti torna false
    }
}

///////////////////////////////////////////////////////////////////////////////////////

int Punto_Piu_Basso(Punto array[], int n) //ritorna l'indice del punto più in basso a sinistra
{
    int min=0;
    for(int i=0; i<n ; i++) //scorre tutti i punti
    {
        if(array[i].gety()<array[min].gety()) //cerca il punto con la y minore
        {
            min=i;
        }
        else
        {
            if(array[i].gety()==array[min].gety()) //se la y è uguale
            {
                if(array[i].getx()<array[min].getx()) //controlla la x
                {
                    min=i;
                }
            }
        }
    }
    return min;
}

bool confrontaAngoli(Punto* A,Punto* B,Punto* C) //esegue il confronto tra gli angoli, torna vero se A[i] ha un angolo minore rispetto a A[j], falso se viceversa. In caso di angolo uguale confronta la lontananza
{
    int res=Angle_Left(*A,*B,*C);
    if(res>0) // è più piccolo i
        return true;
    else
    {
        if(res==0) //sono sulla stessa riga
        {
            if(A->getx() != B->getx() && A->getx() != C->getx()) //Se non sono sulla stessa riga verticale, sono sulla stessa riga orrizzontale o diagonale
            {
                if( std::abs( A->getx() - B->getx() ) < std::abs( A->getx() - C->getx() ) ) //prendo quello più vicino rispetto la coordinata x
                    return true;
                else
                    return false;
            }
            else // se sono sulla stessa riga verticale
            {
                if(B->gety() < C->gety()) // confronta le y,
                    return true;
                else
                    return false;
            }
        }
        else // non sono sulla stessa riga, è più piccolo j
            return false;
    }
}

//merge con confronto basato sull'angolo polare
void mergepol(Punto A[], int l, int c, int r) //l indice sinistro, c indice centrale, r indice destro
{
    Punto* B=(Punto*) malloc(sizeof(Punto)*(r-l)); //vettore di appoggio
    int i=l;
    int j=c+1;
    int k=0;
    while((i<=c) && (j<=r)) //fusione delle due metà
    {
        if(confrontaAngoli(&A[0],&A[i],&A[j]))  //confronto tra gli angoli
        {
            B[k]=A[i];
            i++;
        }
        else
        {
            B[k]=A[j];
            j++;
        }
        k++;;
    }
    while (i<=c) //se i minore di center significa che alcuni elementi della prima metà no sono stati inseriti nel vettore
    { //vengono aggiunti in coda
        B[k]=A[i];
        i++;
        k++;
    }
    while(j<=r)// se j minore di r significa che alcuni elementi della seconda metà non sono stati inseriti  nel vettore
    {
        B[k]=A[j];
        j++;
        k++;
    }
    for (k=l; k<=r; k++) //copio il vettore di appoggio B nel vettore A
    {
        A[k]=B[k-l];
    }
    free(B);
}

//Mergesort con confronto sull'angolo polare
void mergesortpol(Punto A[], int l, int r) //l indice sinistro, r indice destro
{
    if (l<r)
    {
        int c=(l+r)/2; //centro del vettore
        mergesortpol(A,l,c); //chiama ricorsivamente sulla prima parte del vettore
        mergesortpol(A,c+1,r); //chiama ricorsivamente sulla seconda parte
        mergepol(A,l,c,r); //funzione di fusione delle metà ordinate
    }
}

Punto* Ordinamento_Polare(Punto array[],int n, int min) //Esegue l'ordinamento polare dei punti nell'array rispetto al punto di indice min
{
    Punto* ordine=(Punto*) malloc (sizeof(Punto)*n); //conterrà i punti ordinati per angolo polare rispetto al più in basso a sinistra
    ordine[0]=array[min]; //array da ordinare
    for(int i=0 ; i<n ; i++) //Copia i valori nell'array ordine
    {
        if(i<min)
            ordine[i+1]=array[i];
        else
            if(i!=min)
                
                ordine[i]=array[i];
    }
    mergesortpol(ordine,1,n-1); //Funzione di ordinamento margesort con confronto basato sull'angolo polare
    return ordine;
}

Pila<Punto>* Graham_Scan(Punto lista[],int n)
{
    Pila<Punto>* P=new Pila<Punto>(); //Struttura che conterrà l'involucro
    int indicep0=Punto_Piu_Basso(lista,n); //Calcola il punto più in basso a sinistra
    Punto* ordine=Ordinamento_Polare(lista,n,indicep0); //Ordina la lista secondo l'angolo polare rispetto all'elemento più basso
    
    P->Push(ordine[0]); //aggiunge all'involucro il primo elemento
    for(int i=1; i<n; i++) // Scorre tutti i restanti elementi
    {
        //Necessari per gestire il caso non ci sia un secondo elemento
        int checkq=1;
        Punto q=Punto(0,0);

        Punto p=P->Top(); //prende l'ultimo elemento inserito
        
        try //Necessario nel caso non ci sia il secondo elemento, in quel caso solleva un eccezione testuale
        {
            q=P->Next_To_Top();
        }
        catch (const char* msg) //Next_to_Top() solleva un eccezione testuale
        {
            checkq=0; // indica che non c'è un secondo elemento
        }
        while(checkq!=0 && (Turn_Left(q,p,ordine[i])<=0)) // il primo controlla se esiste un secondo elemento, il secondo valuta la posizione del nuovo nodo rispetto all'ugli ultimi due inseriti
        {
            checkq=1;
            P->Pop(); //elimina l'ultimo inserito
            p=q;
            try //Necessario nel caso non ci sia il secondo elemento, in quel caso solleva un eccezione testuale
            {
                q=P->Next_To_Top();
            }
            catch (const char* msg) //Next_to_Top() solleva un eccezione testuale
            {
                checkq=0; // indica che non c'è un secondo elemento
            }
        }
        P->Push(ordine[i]);
    }
    free(ordine);
    return P;
}

////////////////////////////////////////////////////////////////////////////////////////////

int Punto_Piu_Alto(Punto array[],int n)  //ritorna il punto più in alto a destra
{
    int max=0;
    for(int i=0; i<n ; i++) //scorre tutti i punti
    {
        if(array[i].gety()>array[max].gety()) //cerca il punto con la y maggiore
        {
            max=i;
        }
        else
        {
            if(array[i].gety()==array[max].gety()) //se la y è uguale
            {
                if(array[i].getx()>array[max].getx()) //controlla la x
                {
                    max=i;
                }
            }
        }
    }
    return max;
}

Punto* Min_Polar_Right(Punto p,Punto lista[],int n) //Calcola il punto con l'angolo polare destro minore rispetto al punto p passato in ingresso
{
    Punto *asse=new Punto(std::numeric_limits<int>::min(),p.gety()); //rappresenta l'asse X dal punto p
    Punto *p0=asse;
    for(int i=0; i<n; i++) //scorre tutti i punti
    {
        if(p.gety()<=lista[i].gety()) //se son sotto l'orrizontale del punto non vengono considerati
            if(p!=lista[i]) //se sono il punto stesso non vengono considerati
                if(confrontaAngoli(&p,&lista[i],p0)) //operazione di confronto
                    p0=&lista[i]; //salvo il punto se ha un angolo polare minore tra quelli fin ora esaminati
    }
    delete(asse);
    return p0; //ritorna il punto con angolo polare minore
}

Punto* Min_Polar_Left(Punto p,Punto lista[],int n)//calcola il punto con angolo polare sinistro minore rispetto al punto p passato in ingresso
{
    Punto *asse=new Punto(std::numeric_limits<int>::max(),p.gety());
    Punto *p0=asse;
    for(int i=0; i<n; i++)
    {
        if(p.gety()>=lista[i].gety())
            if(p!=lista[i])
                if(confrontaAngoli(&p,&lista[i],p0))
                {
                    p0=&lista[i];
                }
    }
    delete(asse);
    return p0;
}

int Jarvis_March(Punto lista[], int n,Punto H[])
{
    int indicep0=Punto_Piu_Basso(lista,n); //Calcola il punto più in basso a sinistra
    int indicept=Punto_Piu_Alto(lista,n); //Calcola il punto più in alto a destra
    Punto *pt=&lista[indicept];
    Punto *p0=&lista[indicep0];
    Punto *q=0;
    H[0]=lista[indicep0];
    int k=0;
    while(H[k]!=*pt) //da p0 a pt
    {
        q=Min_Polar_Right(H[k],lista,n);
        k=k+1;
        H[k]=*q;
    }
    q=Min_Polar_Left(H[k],lista,n);
    while(*q!=*p0) //da pt a p0
    {
        k=k+1;
        H[k]=*q;
        q=Min_Polar_Left(H[k],lista,n);
    }
    return k; //vettore dell'involucro
}

//////////////////////////////////////////////////////////////////////////////////////////////

void ordinaSegmenti(Segmento segmenti[],int n) //ordina gli estremi di ogni segmento in modo che il più piccolo sia all'inizio e il più grande alla fine
{
    for(int i=0; i<n ; i++)
    {
        if(segmenti[i].getf() < segmenti[i].geti())
        {
            Punto h=segmenti[i].getf();
            segmenti[i].setf(segmenti[i].geti());
            segmenti[i].seti(h);
        }
    }
}

Evento* sequenzaEventi(Segmento segmenti[], int n) //costruisce la sequenza di eventi, uno per ogni vertice di ogni segmento
{
    Evento* lista=(Evento*) malloc (sizeof(Evento)*n*2);
    
    for(int i=0; i<n; i++)
    {
        lista[i*2]= Evento(&segmenti[i],true);
        lista[i*2+1]=Evento(&segmenti[i],false);
    }
    return lista;
}

// prende in ingresso un array di segmenti e ritorna se almeno due di essi si intersecano
bool Any_Segment_Intersec(Segmento segmenti[],int n)
{
    AlberoRB<Segmento> *T=new AlberoRB<Segmento>();
    
    ordinaSegmenti(segmenti,n); //Ordina gli estremi dei segmenti
    
    Evento* lista=sequenzaEventi(segmenti,n); //Costruisce la sequenza di eventi
    
    mergesort(lista,0,n*2 - 1); //Ordina glie eventi per coordinata x crescente, se uguale mette prima gli estremi sinistri poi quelli destri. Se sono estremi uguali ordina per y crescente
    
    //
    for(int i=0; i<2*n; i++)
    {
        if(lista[i].gete())
        {
            cout<<"e:"<<lista[i].gete()<<" x:"<<lista[i].gets()->geti().getx()<<" y:"<<lista[i].gets()->geti().gety()<<endl;
        }
        else
        {
           cout<<"e:"<<lista[i].gete()<<" x:"<<lista[i].gets()->getf().getx()<<" y:"<<lista[i].gets()->getf().gety()<<endl;
        }
    }
    //
    
    for(int i=0; i<2*n ; i++)
    {
        Segmento *s=lista[i].gets();
        Segmento *s1=0;
        Segmento *s2=0;
        if(lista[i].gete())
        {
            T->insertElem(new AlberoRBElem<Segmento>(s));
            if(T->successoreVal(*s)==0) //ABOVE
                s1=0;
            else
                s1=T->successoreVal(*s)->getvalue();
            if(s1!=0 && Segments_Intersec(s->geti(),s->getf(),s1->geti(),s1->getf()))
            {
                return true;
            }
            if(T->predecessoreVal(*s)==0) //BELOW
                s2=0;
            else
                s2=T->predecessoreVal(*s)->getvalue();
            if(s2!=0 && Segments_Intersec(s->geti(),s->getf(),s2->geti(),s2->getf()))
            {
                return true;
            }
        }
        else
        {
            if(T->successoreVal(*s)==0) //ABOVE
                s1=0;
            else
                s1=T->successoreVal(*s)->getvalue();
            if(T->predecessoreVal(*s)==0) //BELOW
                s2=0;
            else
                s2=T->predecessoreVal(*s)->getvalue();
            if(s1!=0 && s2!=0 && Segments_Intersec(s1->geti(),s1->getf(),s2->geti(),s2->getf()))
                return true;
            T->deleteElem(*s);
        }
    }
    return false;
}














