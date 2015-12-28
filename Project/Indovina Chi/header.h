#ifndef HEADER_H
#define HEADER_H
#include "Coda.h"

#ifndef N_PERSONE
# error ERROR: N_PERSONE undefined
#endif

#ifndef N_STEP
# error ERROR: N_STEP undefined
#endif

#ifndef ALGORITMO
# error ERROR: ALGORITMO undefined
#endif

#ifndef GIOCATORE1
# error ERROR: ALGORITMO undefined
#endif

#ifndef GIOCATORE2
# error ERROR: ALGORITMO undefined
#endif

Domanda domande[N_DOMANDE];//array delle domande
//////////////////////////////////////////////////////////////
//Fuznioni manipolazione della lista ed ausiliarie

bool checkugualianza(Persona *first, Persona *nuova) //funzione che controlla che il nuovo personaggio creato non sia uguale ad uno precedentemente creato
{
    bool check=true;
    while( check && first!=NULL)//scorre tutti i personaggi
    {
        if(first->getcapelli()==nuova->getcapelli())// controlla tutti gli attributi
        {
            if(first->getocchi()==nuova->getocchi())
            {
                if(first->getnaso()==nuova->getnaso())
                {
                    if(first->getorecchie()==nuova->getorecchie())
                    {
                        if(first->getbocca()==nuova->getbocca())
                        {
                            if(first->getocchiali()==nuova->getocchiali())
                            {
                                if(first->getcappello()==nuova->getcappello())
                                {
                                    if(first->getsesso()==nuova->getsesso())
                                    {
                                        if(first->getbaffi()==nuova->getbaffi())
                                        {
                                            if(first->getbarba()==nuova->getbarba())
                                            {
                                                check=false; //se hanno tutte gli attributi uguali
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(check)
        first=first->getnext();
    }//Fine while;
    if(check)
    {
        return false;
    }
    else
    {
        return true;
    }
}


Persona* aggiungipersona(Persona *first, int i) //crea ed aggiunge una persona in cima alla lista
{
    bool check=true;
    Persona* nuova=NULL;
    while(check)
    {
        nuova=new Persona(i);
        check=checkugualianza(first,nuova);//controlla che la persona appena generata non sia uguale ad altre
        if(check==true)
        {
            delete(nuova);
        }
    }
    nuova->setnext(first);
    return nuova;
}


Persona* toglidallalista(Persona* first) //rimuove il primo elemento dalla lista e lo elimina
{
    Persona* ritorno=first->getnext();
    delete (first);
    return ritorno;
}

Persona* rimuoviscelta(Persona* first,Persona* scelta)// rimuove l'elemento passato dalla lista
{
    if(first->getnome()==scelta->getnome())
    {
        first=toglidallalista(first);
    }
    else
        first->setnext(rimuoviscelta(first->getnext(),scelta));
    
    return first;
}


int contaPersone(Persona* first) //conta elementi della lista
{
    if(first==NULL)
        return 0;
    return (1 + contaPersone(first->getnext()));
}


Persona* sceltapersona(Persona* first)// sceglie il personaggio da indovinare
{
    int numeropersona=(rand()%N_PERSONE)-1;
    for(int i=0; i<numeropersona;i++)
    {
        first=first->getnext();
    }
    Persona* ritorno=new Persona(first,NULL);
    return ritorno;
}

Persona* copialista(Persona* lista, Persona* copia) // esegue la copia di una lista(in maniera non ordinata)
{
    int lenght=contaPersone(lista);
    copia=new Persona(lista,NULL);
    for (int i=1; i<lenght; i++)
    {
        lista=lista->getnext();
        copia=new Persona(lista,copia);
    }
    return copia;
}

///////////////////////////////////////////////////////////////////////////////////
//Funzioni di eliminazione elementi
//elimina sesso
Persona* eliminasesso(Persona* first, sesso value) //eliminano gli elementi con il determinato valore
{
    if(first==NULL)
        return NULL;
    
    if(first->getsesso()==value)
    {
        first=toglidallalista(first);
        first=eliminasesso(first,value);
    }
    else
        first->setnext(eliminasesso(first->getnext(),value));
    return first;
}
Persona* eliminasessouomo(Persona* first, bool value)//eliminano l'elemento con il valore desiderato in relazione al valore booleano passatogli in ingresso
{
    if(value)
    {
        first=eliminasesso(first,uomo);
    }
    else
    {
        first=eliminasesso(first,donna);
    }
    return first;
}
Persona* eliminasessodonna(Persona* first, bool value)
{
    if(value)
    {
        first=eliminasesso(first,donna);
    }
    else
    {
        first=eliminasesso(first,uomo);
    }
    return first;
}
//elimina baffi
Persona* eliminabaffi(Persona* first, dimensioni value)
{
    if(first==NULL)
        return NULL;
    
    if(first->getbaffi()==value)
    {
        first=toglidallalista(first);
        first=eliminabaffi(first,value);
    }
    else
        first->setnext(eliminabaffi(first->getnext(),value));
    return first;
}
Persona* eliminabaffigrandi(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabaffi(first,grande);
    }
    else
    {
        first=eliminabaffi(first,normale);
        first=eliminabaffi(first,piccolo);
        first=eliminabaffi(first,assente);
    }
    return first;
}
Persona* eliminabaffinormali(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabaffi(first,normale);
    }
    else
    {
        first=eliminabaffi(first,grande);
        first=eliminabaffi(first,piccolo);
        first=eliminabaffi(first,assente);
    }
    return first;
}
Persona* eliminabaffipiccoli(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabaffi(first,piccolo);
    }
    else
    {
        first=eliminabaffi(first,normale);
        first=eliminabaffi(first,grande);
        first=eliminabaffi(first,assente);
    }
    return first;
}
Persona* eliminabaffiassenti(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabaffi(first,assente);
    }
    else
    {
        first=eliminabaffi(first,normale);
        first=eliminabaffi(first,piccolo);
        first=eliminabaffi(first,grande);
    }
    return first;
}
//elimina barba
Persona* eliminabarba(Persona* first, dimensioni value)
{
    if(first==NULL)
        return NULL;
    
    if(first->getbarba()==value)
    {
        first=toglidallalista(first);
        first=eliminabarba(first,value);
    }
    else
        first->setnext(eliminabarba(first->getnext(),value));
    return first;
}
Persona* eliminabarbagrande(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabarba(first,grande);
    }
    else
    {
        first=eliminabarba(first,normale);
        first=eliminabarba(first,piccolo);
        first=eliminabarba(first,assente);
    }
    return first;
}
Persona* eliminabarbanormale(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabarba(first,normale);
    }
    else
    {
        first=eliminabarba(first,grande);
        first=eliminabarba(first,piccolo);
        first=eliminabarba(first,assente);
    }
    return first;
}
Persona* eliminabarbapiccola(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabarba(first,piccolo);
    }
    else
    {
        first=eliminabarba(first,normale);
        first=eliminabarba(first,grande);
        first=eliminabarba(first,assente);
    }
    return first;
}
Persona* eliminabarbaassente(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabarba(first,assente);
    }
    else
    {
        first=eliminabarba(first,normale);
        first=eliminabarba(first,piccolo);
        first=eliminabarba(first,grande);
    }
    return first;
}
//elimina bocca
Persona* eliminabocca(Persona* first, dimensioni value)
{
    if(first==NULL)
        return NULL;
    
    if(first->getbocca()==value)
    {
        first=toglidallalista(first);
        first=eliminabocca(first,value);
    }
    else
        first->setnext(eliminabocca(first->getnext(),value));
    return first;
}
Persona* eliminaboccagrande(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabocca(first,grande);
    }
    else
    {
        first=eliminabocca(first,normale);
        first=eliminabocca(first,piccolo);
    }
    return first;
}
Persona* eliminaboccanormale(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabocca(first,normale);
    }
    else
    {
        first=eliminabocca(first,grande);
        first=eliminabocca(first,piccolo);
    }
    return first;
}
Persona* eliminaboccapiccola(Persona* first, bool value)
{
    if(value)
    {
        first=eliminabocca(first,piccolo);
    }
    else
    {
        first=eliminabocca(first,normale);
        first=eliminabocca(first,grande);
    }
    return first;
}
//elimina cappello
Persona* eliminacappello(Persona* first, dimensioni value)
{
    if(first==NULL)
        return NULL;
    
    if(first->getcappello()==value)
    {
        first=toglidallalista(first);
        first=eliminacappello(first,value);
    }
    else
        first->setnext(eliminacappello(first->getnext(),value));
    return first;
}
Persona* eliminacappellogrande(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacappello(first,grande);
    }
    else
    {
        first=eliminacappello(first,normale);
        first=eliminacappello(first,piccolo);
        first=eliminacappello(first,assente);
    }
    return first;
}
Persona* eliminacappellonormale(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacappello(first,normale);
    }
    else
    {
        first=eliminacappello(first,grande);
        first=eliminacappello(first,piccolo);
        first=eliminacappello(first,assente);
    }
    return first;
}
Persona* eliminacappellopiccolo(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacappello(first,piccolo);
    }
    else
    {
        first=eliminacappello(first,normale);
        first=eliminacappello(first,grande);
        first=eliminacappello(first,assente);
    }
    return first;
}
Persona* eliminacappelloassente(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacappello(first,assente);
    }
    else
    {
        first=eliminacappello(first,normale);
        first=eliminacappello(first,piccolo);
        first=eliminacappello(first,grande);
    }
    return first;
}
//elimina occhiali
Persona* eliminaocchiali(Persona* first, dimensioni value)
{
    if(first==NULL)
        return NULL;
    
    if(first->getocchiali()==value)
    {
        first=toglidallalista(first);
        first=eliminaocchiali(first,value);
    }
    else
        first->setnext(eliminaocchiali(first->getnext(),value));
    return first;
}
Persona* eliminaocchialigrandi(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaocchiali(first,grande);
    }
    else
    {
        first=eliminaocchiali(first,normale);
        first=eliminaocchiali(first,piccolo);
        first=eliminaocchiali(first,assente);
    }
    return first;
}
Persona* eliminaocchialinormali(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaocchiali(first,normale);
    }
    else
    {
        first=eliminaocchiali(first,grande);
        first=eliminaocchiali(first,piccolo);
        first=eliminaocchiali(first,assente);
    }
    return first;
}
Persona* eliminaocchialipiccoli(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaocchiali(first,piccolo);
    }
    else
    {
        first=eliminaocchiali(first,grande);
        first=eliminaocchiali(first,normale);
        first=eliminaocchiali(first,assente);
    }
    return first;
}
Persona* eliminaocchialiassenti(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaocchiali(first,assente);
    }
    else
    {
        first=eliminaocchiali(first,grande);
        first=eliminaocchiali(first,piccolo);
        first=eliminaocchiali(first,normale);
    }
    return first;
}
//elimina orecchie
Persona* eliminaorecchie(Persona* first, dimensioni value)
{
    if(first==NULL)
        return NULL;
    
    if(first->getorecchie()==value)
    {
        first=toglidallalista(first);
        first=eliminaorecchie(first,value);
    }
    else
        first->setnext(eliminaorecchie(first->getnext(),value));
    return first;
}
Persona* eliminaorecchiegrandi(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaorecchie(first,grande);
    }
    else
    {
        first=eliminaorecchie(first,normale);
        first=eliminaorecchie(first,piccolo);
    }
    return first;
}
Persona* eliminaorecchienormali(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaorecchie(first,normale);
    }
    else
    {
        first=eliminaorecchie(first,grande);
        first=eliminaorecchie(first,piccolo);
    }
    return first;
}
Persona* eliminaorecchiepiccole(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaorecchie(first,piccolo);
    }
    else
    {
        first=eliminaorecchie(first,normale);
        first=eliminaorecchie(first,grande);
    }
    return first;
}
//elimina naso
Persona* eliminanaso(Persona* first, dimensioni value)
{
    if(first==NULL)
        return NULL;
    
    if(first->getnaso()==value)
    {
        first=toglidallalista(first);
        first=eliminanaso(first,value);
    }
    else
        first->setnext(eliminanaso(first->getnext(),value));
    return first;
}
Persona* eliminanasogrande(Persona* first, bool value)
{
    if(value)
    {
        first=eliminanaso(first,grande);
    }
    else
    {
        first=eliminanaso(first,normale);
        first=eliminanaso(first,piccolo);
    }
    return first;
}
Persona* eliminanasonormale(Persona* first, bool value)
{
    if(value)
    {
        first=eliminanaso(first,normale);
    }
    else
    {
        first=eliminanaso(first,grande);
        first=eliminanaso(first,piccolo);
    }
    return first;
}
Persona* eliminanasopiccolo(Persona* first, bool value)
{
    if(value)
    {
        first=eliminanaso(first,piccolo);
    }
    else
    {
        first=eliminanaso(first,normale);
        first=eliminanaso(first,grande);
    }
    return first;
}
//eliminazione capelli
Persona* eliminacapelli(Persona* first, capelli value)
{
    if(first==NULL)
        return NULL;
    
    if(first->getcapelli()==value)
    {
        first=toglidallalista(first);
        first=eliminacapelli(first,value);
    }
    else
        first->setnext(eliminacapelli(first->getnext(),value));
    return first;
}
Persona* eliminacapellineri(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacapelli(first,neri);
    }
    else
    {
        first=eliminacapelli(first,castani);
        first=eliminacapelli(first,biondi);
        first=eliminacapelli(first,rossi);
        first=eliminacapelli(first,bianchi);
        first=eliminacapelli(first,calvo);
    }
    return first;
}
Persona* eliminacapellirossi(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacapelli(first,rossi);
    }
    else
    {
        first=eliminacapelli(first,castani);
        first=eliminacapelli(first,biondi);
        first=eliminacapelli(first,neri);
        first=eliminacapelli(first,bianchi);
        first=eliminacapelli(first,calvo);
    }
    return first;
}
Persona* eliminacapellibiondi(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacapelli(first,biondi);
    }
    else
    {
        first=eliminacapelli(first,castani);
        first=eliminacapelli(first,rossi);
        first=eliminacapelli(first,neri);
        first=eliminacapelli(first,bianchi);
        first=eliminacapelli(first,calvo);
    }
    return first;
}
Persona* eliminacapellibianchi(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacapelli(first,bianchi);
    }
    else
    {
        first=eliminacapelli(first,castani);
        first=eliminacapelli(first,biondi);
        first=eliminacapelli(first,neri);
        first=eliminacapelli(first,rossi);
        first=eliminacapelli(first,calvo);
    }
    return first;
}
Persona* eliminacapellicastani(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacapelli(first,castani);
    }
    else
    {
        first=eliminacapelli(first,neri);
        first=eliminacapelli(first,biondi);
        first=eliminacapelli(first,rossi);
        first=eliminacapelli(first,bianchi);
        first=eliminacapelli(first,calvo);
    }
    return first;
}
Persona* eliminacapellicalvo(Persona* first, bool value)
{
    if(value)
    {
        first=eliminacapelli(first,calvo);
    }
    else
    {
        first=eliminacapelli(first,castani);
        first=eliminacapelli(first,biondi);
        first=eliminacapelli(first,neri);
        first=eliminacapelli(first,bianchi);
        first=eliminacapelli(first,rossi);
    }
    return first;
}
//eliminazione occhi
Persona* eliminaocchi(Persona* first, occhi value)
{
    if(first==NULL)
        return NULL;
    
    if(first->getocchi()==value)
    {
        first=toglidallalista(first);
        first=eliminaocchi(first,value);
    }
    else
        first->setnext(eliminaocchi(first->getnext(),value));
    return first;
}
Persona* eliminaocchiazzurri(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaocchi(first,azzurri);
    }
    else
    {
        first=eliminaocchi(first,marroni);
        first=eliminaocchi(first,verdi);
    }
    return first;
}
Persona* eliminaocchimarroni(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaocchi(first,marroni);
    }
    else
    {
        first=eliminaocchi(first,azzurri);
        first=eliminaocchi(first,verdi);
    }
    return first;
}
Persona* eliminaocchiverdi(Persona* first, bool value)
{
    if(value)
    {
        first=eliminaocchi(first,verdi);
    }
    else
    {
        first=eliminaocchi(first,marroni);
        first=eliminaocchi(first,azzurri);
    }
    return first;
}

void liberalista(Persona* first)  //dealloca la lista passata in ingresso
{
    while(first!=NULL)
    {
        Persona* help=first;
        first=first->getnext();
        if(help==NULL)
        {
            cout <<"NULL"<<endl;
        }
        delete(help);
    }
}

void initdomande(Domanda *domande) //inizializza il vettore delle domande
{
    
    domande[0].settesto("Ha gli occhiali grandi?");
    domande[0].setfunz(eliminaocchialigrandi);
    
    domande[1].settesto("Ha gli occhiali piccoli?");
    domande[1].setfunz(eliminaocchialipiccoli);

    domande[2].settesto("Ha gli occhiali normali?");
    domande[2].setfunz(eliminaocchialinormali);
    
    domande[3].settesto("Non ha gli occhiali?");
    domande[3].setfunz(eliminaocchialiassenti);
    
    domande[4].settesto("Ha i baffi grandi?");
    domande[4].setfunz(eliminabaffigrandi);
    
    domande[5].settesto("Ha i baffi normali?");
    domande[5].setfunz(eliminabaffinormali);
    
    domande[6].settesto("Ha i baffi piccoli?");
    domande[6].setfunz(eliminabaffipiccoli);
    
    domande[7].settesto("Non ha i baffi?");
    domande[7].setfunz(eliminabaffiassenti);
    
    domande[8].settesto("Ha il cappello grande?");
    domande[8].setfunz(eliminacappellogrande);
    
    domande[9].settesto("Ha il cappello piccolo?");
    domande[9].setfunz(eliminacappellopiccolo);
    
    domande[10].settesto("Ha il cappello normale?");
    domande[10].setfunz(eliminacappellonormale);
    
    domande[11].settesto("Non ha il cappello?");
    domande[11].setfunz(eliminacappelloassente);
    
    domande[12].settesto("Ha la barba grande?");
    domande[12].setfunz(eliminabarbagrande);
    
    domande[13].settesto("Ha la barba piccola?");
    domande[13].setfunz(eliminabarbapiccola);
    
    domande[14].settesto("Ha la barba normale?");
    domande[14].setfunz(eliminabarbanormale);
    
    domande[15].settesto("Non ha la barba?");
    domande[15].setfunz(eliminabarbaassente);
    
    domande[16].settesto("È una donna?");
    domande[16].setfunz(eliminasessodonna);
    
    domande[17].settesto("È un uomo?");
    domande[17].setfunz(eliminasessouomo);
    
    domande[18].settesto("Ha gli occhi marroni?");
    domande[18].setfunz(eliminaocchimarroni);
    
    domande[19].settesto("Ha gli occhi azzurri?");
    domande[19].setfunz(eliminaocchiazzurri);
    
    domande[20].settesto("Ha gli occhi verdi?");
    domande[20].setfunz(eliminaocchiverdi);
    
    domande[21].settesto("Ha la bocca grande?");
    domande[21].setfunz(eliminaboccagrande);
    
    domande[22].settesto("Ha la bocca piccola?");
    domande[22].setfunz(eliminaboccapiccola);
    
    domande[23].settesto("Ha la bocca normale?");
    domande[23].setfunz(eliminaboccanormale);
    
    domande[24].settesto("Ha il naso grande?");
    domande[24].setfunz(eliminanasogrande);
    
    domande[25].settesto("Ha il naso piccolo?");
    domande[25].setfunz(eliminanasopiccolo);
    
    domande[26].settesto("Ha il naso normale?");
    domande[26].setfunz(eliminanasonormale);
    
    domande[27].settesto("Ha le orecchie grandi?");
    domande[27].setfunz(eliminaorecchiegrandi);
    
    domande[28].settesto("Ha le orecchie piccole?");
    domande[28].setfunz(eliminaorecchiepiccole);
    
    domande[29].settesto("Ha le orecchie piccole?");
    domande[29].setfunz(eliminaorecchienormali);
    
    domande[30].settesto("Ha i capelli biondi?");
    domande[30].setfunz(eliminacapellibiondi);
    
    domande[31].settesto("Ha i capelli castani?");
    domande[31].setfunz(eliminacapellicastani);
    
    domande[32].settesto("Ha i capelli neri?");
    domande[32].setfunz(eliminacapellineri);
    
    domande[33].settesto("Ha i capelli rossi?");
    domande[33].setfunz(eliminacapellirossi);
    
    domande[34].settesto("Ha i capelli bianchi?");
    domande[34].setfunz(eliminacapellibianchi);
    
    domande[35].settesto("È calvo?");
    domande[35].setfunz(eliminacapellicalvo);
     
}
//////////////////////////////////////////////////////////////////////////////////
/// Funzioni per l'IA

int minvalue(int i,Persona *first,int *array,int numerocicli);//funzione min
int maxvalue(Persona *first, int *array,int numerocicli);//funzione max

int minvaluepruning(int i,Persona *first, int alfa , int beta,int *array,int numerocicli);//funzione min
int maxvaluepruning(Persona *first, int alfa, int beta,int *array,int numerocicli);//funzione max
//cost uni


//////////Breadth limited
Coda* aggiungiqueue(Coda* queue,Coda* nuova) // aggiunge un elemento al termine della coda
{
    if(queue==NULL)
    {
        nuova->setnext(NULL);
        queue=nuova;
        return queue;
    }
    queue->setnext(aggiungiqueue(queue->getnxt(),nuova));
    return queue;
}

void bfs(Coda* queue)   //funzione che aggiunge alla coda i figli di un nodo
{
    for(int i=0;i<N_DOMANDE;i++)    //per ogni possibile figlio del nodo
    {
        int array[N_DOMANDE];
        memcpy(array,queue->getarray(),N_DOMANDE*sizeof(int));
        if(array[i]==0) //se nel cammino seguito non è gia stata fatta la domanda
        {
            int copyarray[N_DOMANDE];
            Persona* lista1=NULL;
            Persona* lista2=NULL;
            lista1=copialista(queue->getelemento(),lista1);
            lista2=copialista(queue->getelemento(),lista2);
            lista1=domande[i].execfunz(lista1,false); //calcola i valori delle due possibili risposte e sceglie quello peggiore
            lista2=domande[i].execfunz(lista2,true);
            int a=contaPersone(lista1);
            int b=contaPersone(lista2);
            int cont;
            if(b>a) //MAX //if(b<a) MIN
            {
                cont=b;
                liberalista(lista1);
                lista1=lista2;
            }
            else
            {
                cont=a;
                liberalista(lista2);
            }
            memcpy(copyarray,array,N_DOMANDE*sizeof(int));
            copyarray[i]=1; //segna la domanda eseguita
            Coda *nuova=new Coda(lista1,NULL,copyarray,queue->getdomanda(),queue->getnumerocicli()-1);  //crea l'elemento da aggiungere alla coda
            queue=aggiungiqueue(queue,nuova); //accoda l'elemento
        }
    }
}

int breadthlimited(Persona* first,int* arraydomande, int numerocicli)// esegue la visita per ampiezza al fine di trovare la risposta migliore
{
    Coda *queue=NULL;
    for(int i=0;i<N_DOMANDE;i++)//prova tutte le possibili domande
    {
        if(arraydomande[i]==0)//se la domanda non è gia stata fatta
        {
            int copyarray[N_DOMANDE];
            Persona* lista1=NULL;
            Persona* lista2=NULL;
            lista1=copialista(first,lista1);
            lista2=copialista(first,lista2);
            lista1=domande[i].execfunz(lista1,false);//calcola i valori delle due possibili risposte e sceglie il peggiore
            lista2=domande[i].execfunz(lista2,true);
            int a=contaPersone(lista1);
            int b=contaPersone(lista2);
            if(b>a)//MAX //if(b<a) MIN
            {
                liberalista(lista1);
                lista1=lista2;
            }
            else
            {
                liberalista(lista2);
            }
            memcpy(copyarray,arraydomande,N_DOMANDE*sizeof(int));
            copyarray[i]=1;
            Coda *nuova=new Coda(lista1,NULL,copyarray,i,numerocicli-1);    //crea l'elemento da accodare
            queue=aggiungiqueue(queue,nuova);   //accoda l'elemento
        }
    }
    int ritorno=-1;
    int valore=INT_MAX;
    while(queue!=NULL) //finche la coda non è vuota
    {
        Coda *lista=queue;
        queue=queue->getnxt(); //estrae un elemento dalla coda
        Persona* elemento=lista->getelemento();
        int cont=contaPersone(elemento);

        if(cont!=0) //condizioni di terminazione
        {
            if(cont==1) //se ha trovato la soluzione
            {
                liberalista(elemento);
                ritorno=lista->getdomanda();
                delete(lista);
                return ritorno;
            }
            
            if(lista->getnumerocicli()<=0)  //se ha raggiunto il limite di profondità
            {
                liberalista(elemento);
                if(cont<valore) //se il valore è migliore di quello trovato fin ora lo salva
                {
                    ritorno=lista->getdomanda();
                    valore=cont;
                }
                delete(lista);
            }
            else
            {
                bfs(lista);
                liberalista(elemento);
                delete(lista);
            }
        }
    }
    return ritorno; //ritorna la domanda con il valore migliore
}

///////////Depth limited

int dlricorsiva(Persona* first,int domanda,int* array, int numerocicli) //esegue ricorsivamente la visita in profondità
{
    int cont;
    Persona* lista=NULL;
    lista=copialista(first,lista);
    lista=domande[domanda].execfunz(lista,false);
    first=domande[domanda].execfunz(first,true);
    int a=contaPersone(lista);
    int b=contaPersone(first);
    if(b>a)//MAX if(b<a) MIN
    {
        cont=b;
        liberalista(lista);
        lista=first;
    }
    else
    {
        cont=a;
        liberalista(first);
    }
    if(numerocicli<=0)
    {
        liberalista(lista);
        return cont;
    }

    if(cont<=1)
    {
        liberalista(lista);
        return cont;
    }
    int risultato=INT_MAX;//MIN
    for(int i=0;i<N_DOMANDE;i++)
    {
        if(array[i]==0)
        {
            int copyarray[N_DOMANDE];
            Persona* copy=NULL;
            copy=copialista(lista,copy);
            memcpy(copyarray,array,N_DOMANDE*sizeof(int));
            copyarray[i]=1;
            int risposta=dlricorsiva(copy,i,copyarray,numerocicli-1);
            if(risposta!=0)
            {
                if(risposta==1)
                    return risposta;
                risultato=min(risultato,risposta);
            }
        }
    }
    liberalista(lista);
    return risultato;
}

int depthlimited(Persona* first,int* arraydomande, int numerocicli) //funzione che esegue la visita in profondità per trovare una soluzione
{
    int valore=-1;
    int risultato=INT_MAX;
    for(int i=0;i<N_DOMANDE;i++)// esplora tutte le possibili domande
    {
        if(arraydomande[i]==0) // se la domanda non è gia stata fatta
        {
            int copyarray[N_DOMANDE];
            Persona* copy=NULL;
            copy=copialista(first,copy);
            memcpy(copyarray,arraydomande,N_DOMANDE*sizeof(int));
            int risposta=dlricorsiva(copy,i,copyarray,numerocicli-1);//effettua la visità in profondità ricorsivamente
            if(risposta!=0)// condizioni di terminazione
            {
                if(risposta==1)// se ha trovato la soluzione
                    return i;
                if(risposta<risultato)//salva il risultato migliore
                {
                    valore=i;
                    risultato=risposta;
                }
            }
        }
    }
    return valore; //ritorna il risultato migliore
}

////////////////////////////versione pruning

int minvaluepruning(int i,Persona *first,int alfa,int beta,int *array,int numerocicli)//funzione min con pruning
{
    Persona* copy=NULL;
    copy=copialista(first,copy);
    array[i]=1; //segna che la domanda è stata effettuata
    int util=INT_MIN;
    int copyarray[N_DOMANDE];
    memcpy(copyarray,array,N_DOMANDE*sizeof(int));
    //la fase min ha solo due possibili valori:si,no.
    int risposta=maxvaluepruning(domande[i].execfunz(first,true),alfa,beta,&array[0],numerocicli);  //chiama la fase max con un valore di risposta
    util=max(util,risposta);    // controlla se il valore trovato è migliore
    if(util>=beta)  //se il valore è migliore di beta
    {
        return util;    //effettua il pruning
    }
    alfa=max(util,alfa);    //aggiorna alfa
    
    risposta=maxvaluepruning(domande[i].execfunz(copy,false),alfa,beta,&copyarray[0],numerocicli);  //chiama  la fase max con il secondo valore
    util=max(util,risposta);    // controlla se il valore trovato è migliore
    if(util>=beta)  //se il valore è migliore di beta
    {
        return util; // effettua il pruning
    }
    alfa=max(util,alfa);    //aggiorna alfa
    return util;
}

int maxvaluepruning(Persona *first,int alfa,int beta, int *array,int numerocicli)//funzione max con puning
{
    int cont=contaPersone(first);
    if(numerocicli<=0)  //condizione di terminazione per profondità
    {
        liberalista(first);
        return cont;
    }
    if(cont<=1) //se trova la soluzione
    {
        liberalista(first);
        return cont;
    }
    int util=INT_MAX;
    for(int i=0;i<N_DOMANDE;i++)    //se non termina controlla i figli
    {
        if(array[i]==0)
        {
            int copyarray[N_DOMANDE];
            Persona* copy=NULL;
            copy=copialista(first,copy);
            memcpy(copyarray,array,N_DOMANDE*sizeof(int));
            int risposta=minvaluepruning(i,copy,alfa,beta,&copyarray[0],numerocicli-1); //chiama  la funzione min con una determinata domanda
            if(risposta!=0)
            {
                util=min(risposta,util);    //controlla se i valori tornati sono migliori
                if(util<=alfa)  //se il valore è migliore
                {
                    return util;    //effettua il pruning
                }
                beta=min(util,beta);    //aggiorna beta
            }
        }
    }
    liberalista(first);
    return util;    //ritorna il valore migliore
}

int minimaxdecisionpruning(Persona *first,int* arraydomande,int numerocicli)//minimax con pruning
{
    int util=INT_MAX;
    int alfa=INT_MIN;
    int beta=INT_MAX;
    int ritorno=-1;
    for(int i=0;i<N_DOMANDE;i++)    //esegue tutte le domande
    {
        if(arraydomande[i]==0)  //se non son gia state fatte
        {
            Persona* copy=NULL;
            copy=copialista(first,copy);
            int array[N_DOMANDE];
            memcpy(array,arraydomande,N_DOMANDE*sizeof(int));
            int risposta=minvaluepruning(i,copy,alfa,beta,&array[0],numerocicli-1); //chiama la funzione min con una determinata domanda
            if(risposta!=0)
            {
                if(risposta<util)   //se la risposta ottenuta è migliore
                {
                    util=risposta;
                    ritorno=i;
                }
                if(util<=alfa)
                {
                    return ritorno;     //effettuo il pruning
                }
                beta=min(util,beta); //aggiorna beta
            }
        }
    }
    return ritorno;
}

/////////////////////////////versione ricorsiva con scelta di passi




int minvalue(int i,Persona *first,int *array,int numerocicli)//funzione min
{
    Persona* copy=NULL;
    copy=copialista(first,copy);
    array[i]=1; //segna che la domanda è stata effettuata
    int copyarray[N_DOMANDE];
    memcpy(copyarray,array,N_DOMANDE*sizeof(int));
    int a=maxvalue(domande[i].execfunz(first,true),&array[0],numerocicli);  //chiama la fase max con un valore di risposta
    int b=maxvalue(domande[i].execfunz(copy,false),&copyarray[0],numerocicli);  //chiama  la fase max con il secondo valore
    return max(a,b);    //sceglie quello con il valore peggiore
}
 
 

int maxvalue(Persona *first, int *array,int numerocicli)//funzione max
{
    int cont=contaPersone(first);
    if(numerocicli<=0)  //condizione di terminazione per profondità
    {
        liberalista(first);
        return cont;
    }
    if(cont<=1) //se ha trovato la soluzione
    {
        liberalista(first);
        return cont;
    }
    int util=INT_MAX;
    for(int i=0;i<N_DOMANDE;i++)    //sse non termina controlla tutti i figli
    {
        if(array[i]==0) //se la domanda non è gia stata fatta
        {
            int copyarray[N_DOMANDE];
            Persona* copy=NULL;
            copy=copialista(first,copy);
            memcpy(copyarray,array,N_DOMANDE*sizeof(int));
            int risposta=minvalue(i,copy,&copyarray[0],numerocicli-1);  //chiama la funzione min con una determinata domanda
            if(risposta<util && risposta!=0)    //se la risposta è migliore
            {
                util=risposta;
            }
        }
        
    }
    liberalista(first);
    return util;    //ritorna il risultato migliore
}

int minimaxdecision(Persona *first,int* arraydomande,int numerocicli)//funzione minimax
{
    int util=INT_MAX;
    int ritorno=-1;
    for(int i=0;i<N_DOMANDE;i++) //esegue tutte le domande
    {
        if(arraydomande[i]==0)  //se non sono gia state fatte
        {
            Persona* copy=NULL;
            copy=copialista(first,copy);
            int array[N_DOMANDE];
            memcpy(array,arraydomande,N_DOMANDE*sizeof(int));
            int risposta=minvalue(i,copy,&array[0],numerocicli-1);  //chiama la funzione min con una domanda specifica
            if(risposta<util && risposta!=0)    //salva il risultato migliore
            {
                util=risposta;
                ritorno=i;
            }
        }
    }
    return ritorno; //torna il risultato migliore
}


///////////////////////////////////////////////////////////////////////////////////
//Funzioni di richiesta
Persona* domandaIA(Persona* first, Persona* scelta,int *array)//  funzione che gestisce le domande per l' IA
{
    int codicedomanda=0;
    switch (ALGORITMO) {    //scelta dell'algoritmo
        case 1:
            codicedomanda=minimaxdecision(first,&array[0],N_STEP)+1;
            break;
        case 2:
            codicedomanda=minimaxdecisionpruning(first,&array[0],N_STEP)+1;
            break;
        case 3:
            codicedomanda=depthlimited(first,&array[0],N_STEP)+1;
            break;
        case 4:
            codicedomanda=breadthlimited(first,&array[0],N_STEP)+1;
            break;
        default:
            cout<<"VALORE NON VALIDO"<<endl;
    }
    array[codicedomanda-1]=1;   //segnala che la domanda scelta
    cout<<"Domanda : "<<domande[codicedomanda-1].gettesto();
    cout<<"  Risposta: "<<endl;
    switch (codicedomanda) {    //in base alla domanda e alla scelta da la risposta e aggiorna la lista dei personaggi
        case 1:
            if(scelta->getocchiali()==grande)
            {
               cout<<"Si"<<endl;
                first=domande[0].execfunz(first,false);
            }
            else
            {
               cout<<"No"<<endl;
                first=domande[0].execfunz(first,true);
            }
            break;
        case 2:
            if(scelta->getocchiali()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[1].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[1].execfunz(first,true);
            }
            break;
        case 3:
            if(scelta->getocchiali()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[2].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[2].execfunz(first,true);
            }
            break;
        case 4:
            if(scelta->getocchiali()==assente)
            {
                cout<<"Si"<<endl;
                first=domande[3].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[3].execfunz(first,true);
            }
            break;
        case 5:
            if(scelta->getbaffi()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[4].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[4].execfunz(first,true);
            }
            break;
        case 6:
            if(scelta->getbaffi()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[5].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[5].execfunz(first,true);
            }
            break;
        case 7:
            if(scelta->getbaffi()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[6].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[6].execfunz(first,true);
            }
            break;
        case 8:
            if(scelta->getbaffi()==assente)
            {
                cout<<"Si"<<endl;
                first=domande[7].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[7].execfunz(first,true);
            }
            break;
        case 9:
            if(scelta->getcappello()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[8].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[8].execfunz(first,true);
            }
            break;
        case 10:
            if(scelta->getcappello()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[9].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[9].execfunz(first,true);
            }
            break;
        case 11:
            if(scelta->getcappello()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[10].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[10].execfunz(first,true);
            }
            break;
        case 12:
            if(scelta->getcappello()==assente)
            {
                cout<<"Si"<<endl;
                first=domande[11].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[11].execfunz(first,true);
            }
            break;
        case 13:
            if(scelta->getbarba()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[12].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[12].execfunz(first,true);
            }
            break;
        case 14:
            if(scelta->getbarba()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[13].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[13].execfunz(first,true);
            }
            break;
        case 15:
            if(scelta->getbarba()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[14].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[14].execfunz(first,true);
            }
            break;
        case 16:
            if(scelta->getbarba()==assente)
            {
                cout<<"Si"<<endl;
                first=domande[15].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[15].execfunz(first,true);
            }
            break;
        case 17:
            if(scelta->getsesso()==donna)
            {
                cout<<"Si"<<endl;
                first=domande[16].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[16].execfunz(first,true);
            }
            break;
        case 18:
            if(scelta->getsesso()==uomo)
            {
                cout<<"Si"<<endl;
                first=domande[17].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[17].execfunz(first,true);
            }
            break;
        case 19:
            if(scelta->getocchi()==marroni)
            {
                cout<<"Si"<<endl;
                first=domande[18].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[18].execfunz(first,true);
            }
            break;
        case 20:
            if(scelta->getocchi()==azzurri)
            {
                cout<<"Si"<<endl;
                first=domande[19].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[19].execfunz(first,true);
            }
            break;
        case 21:
            if(scelta->getocchi()==verdi)
            {
                cout<<"Si"<<endl;
                first=domande[20].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[20].execfunz(first,true);
            }
            break;
        case 22:
            if(scelta->getbocca()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[21].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[21].execfunz(first,true);
            }
            break;
        case 23:
            if(scelta->getbocca()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[22].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[22].execfunz(first,true);
            }
            break;
        case 24:
            if(scelta->getbocca()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[23].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[23].execfunz(first,true);
            }
            break;
        case 25:
            if(scelta->getnaso()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[24].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[24].execfunz(first,true);
            }
            break;
        case 26:
            if(scelta->getnaso()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[25].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[25].execfunz(first,true);
            }
            break;
        case 27:
            if(scelta->getnaso()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[26].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[26].execfunz(first,true);
            }
            break;
        case 28:
            if(scelta->getorecchie()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[27].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[27].execfunz(first,true);
            }
            break;
        case 29:
            if(scelta->getorecchie()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[28].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[28].execfunz(first,true);
            }
            break;
        case 30:
            if(scelta->getorecchie()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[29].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[29].execfunz(first,true);
            }
            break;
        case 31:
            if(scelta->getcapelli()==biondi)
            {
                cout<<"Si"<<endl;
                first=domande[30].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[30].execfunz(first,true);
            }
            break;
        case 32:
            if(scelta->getcapelli()==castani)
            {
                cout<<"Si"<<endl;
                first=domande[31].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[31].execfunz(first,true);
            }
            break;
        case 33:
            if(scelta->getcapelli()==neri)
            {
                cout<<"Si"<<endl;
                first=domande[32].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[32].execfunz(first,true);
            }
            break;
        case 34:
            if(scelta->getcapelli()==rossi)
            {
                cout<<"Si"<<endl;
                first=domande[33].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[33].execfunz(first,true);
            }
            break;
        case 35:
            if(scelta->getcapelli()==bianchi)
            {
                cout<<"Si"<<endl;
                first=domande[34].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[34].execfunz(first,true);
            }
            break;
        case 36:
            if(scelta->getcapelli()==calvo)
            {
                cout<<"Si"<<endl;
                first=domande[35].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[35].execfunz(first,true);
            }
            break;
    }
    //cout<<endl;
    //getchar();
    return first; //ritorna la lista aggiornata dei personaggi
}

Persona* domanda(Persona* first, Persona* scelta)//funzione che gestisce le domande delgiocatore
{
    int codicedomanda=0;
    
    while(codicedomanda<1 || codicedomanda>N_DOMANDE)   //stampa la lista delle domande e riceve la risposta
    {
        for(int i=0;i<=N_DOMANDE;i++) //stampa le domande
        {
            cout << i+1 <<": "<<domande[i].gettesto()<<endl;
        }
        cout<<"Domanda n:(1/"<<N_DOMANDE<<")";
        cin>>codicedomanda;
        while(codicedomanda<1 || codicedomanda>36)
        {
            cout << "Codice domanda errato, riprovare"<< endl;
            cout<<"Domanda n:(1/"<<N_DOMANDE<<")";
            cin>>codicedomanda;
        }
        
        cout<<endl;
    }
    cout<<"Risposta:";
    switch (codicedomanda) {    //gestisce la domanda fatta e la risposta, aggiorna infine la lista dei personaggi
        case 1:
            if(scelta->getocchiali()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[0].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[0].execfunz(first,true);
            }
            break;
        case 2:
            if(scelta->getocchiali()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[1].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[1].execfunz(first,true);
            }
            break;
        case 3:
            if(scelta->getocchiali()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[2].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[2].execfunz(first,true);
            }
            break;
        case 4:
            if(scelta->getocchiali()==assente)
            {
                cout<<"Si"<<endl;
                first=domande[3].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[3].execfunz(first,true);
            }
            break;
        case 5:
            if(scelta->getbaffi()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[4].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[4].execfunz(first,true);
            }
            break;
        case 6:
            if(scelta->getbaffi()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[5].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[5].execfunz(first,true);
            }
            break;
        case 7:
            if(scelta->getbaffi()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[6].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[6].execfunz(first,true);
            }
            break;
        case 8:
            if(scelta->getbaffi()==assente)
            {
                cout<<"Si"<<endl;
                first=domande[7].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[7].execfunz(first,true);
            }
            break;
        case 9:
            if(scelta->getcappello()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[8].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[8].execfunz(first,true);
            }
            break;
        case 10:
            if(scelta->getcappello()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[9].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[9].execfunz(first,true);
            }
            break;
        case 11:
            if(scelta->getcappello()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[10].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[10].execfunz(first,true);
            }
            break;
        case 12:
            if(scelta->getcappello()==assente)
            {
                cout<<"Si"<<endl;
                first=domande[11].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[11].execfunz(first,true);
            }
            break;
        case 13:
            if(scelta->getbarba()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[12].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[12].execfunz(first,true);
            }
            break;
        case 14:
            if(scelta->getbarba()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[13].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[13].execfunz(first,true);
            }
            break;
        case 15:
            if(scelta->getbarba()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[14].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[14].execfunz(first,true);
            }
            break;
        case 16:
            if(scelta->getbarba()==assente)
            {
                cout<<"Si"<<endl;
                first=domande[15].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[15].execfunz(first,true);
            }
            break;
        case 17:
            if(scelta->getsesso()==donna)
            {
                cout<<"Si"<<endl;
                first=domande[16].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[16].execfunz(first,true);
            }
            break;
        case 18:
            if(scelta->getsesso()==uomo)
            {
                cout<<"Si"<<endl;
                first=domande[17].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[17].execfunz(first,true);
            }
            break;
        case 19:
            if(scelta->getocchi()==marroni)
            {
                cout<<"Si"<<endl;
                first=domande[18].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[18].execfunz(first,true);
            }
            break;
        case 20:
            if(scelta->getocchi()==azzurri)
            {
                cout<<"Si"<<endl;
                first=domande[19].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[19].execfunz(first,true);
            }
            break;
        case 21:
            if(scelta->getocchi()==verdi)
            {
                cout<<"Si"<<endl;
                first=domande[20].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[20].execfunz(first,true);
            }
            break;
        case 22:
            if(scelta->getbocca()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[21].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[21].execfunz(first,true);
            }
            break;
        case 23:
            if(scelta->getbocca()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[22].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[22].execfunz(first,true);
            }
            break;
        case 24:
            if(scelta->getbocca()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[23].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[23].execfunz(first,true);
            }
            break;
        case 25:
            if(scelta->getnaso()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[24].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[24].execfunz(first,true);
            }
            break;
        case 26:
            if(scelta->getnaso()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[25].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[25].execfunz(first,true);
            }
            break;
        case 27:
            if(scelta->getnaso()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[26].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[26].execfunz(first,true);
            }
            break;
        case 28:
            if(scelta->getorecchie()==grande)
            {
                cout<<"Si"<<endl;
                first=domande[27].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[27].execfunz(first,true);
            }
            break;
        case 29:
            if(scelta->getorecchie()==piccolo)
            {
                cout<<"Si"<<endl;
                first=domande[28].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[28].execfunz(first,true);
            }
            break;
        case 30:
            if(scelta->getorecchie()==normale)
            {
                cout<<"Si"<<endl;
                first=domande[29].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[29].execfunz(first,true);
            }
            break;
        case 31:
            if(scelta->getcapelli()==biondi)
            {
                cout<<"Si"<<endl;
                first=domande[30].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[30].execfunz(first,true);
            }
            break;
        case 32:
            if(scelta->getcapelli()==castani)
            {
                cout<<"Si"<<endl;
                first=domande[31].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[31].execfunz(first,true);
            }
            break;
        case 33:
            if(scelta->getcapelli()==neri)
            {
                cout<<"Si"<<endl;
                first=domande[32].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[32].execfunz(first,true);
            }
            break;
        case 34:
            if(scelta->getcapelli()==rossi)
            {
                cout<<"Si"<<endl;
                first=domande[33].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[33].execfunz(first,true);
            }
            break;
        case 35:
            if(scelta->getcapelli()==bianchi)
            {
                cout<<"Si"<<endl;
                first=domande[34].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[34].execfunz(first,true);
            }
            break;
        case 36:
            if(scelta->getcapelli()==calvo)
            {
                cout<<"Si"<<endl;
                first=domande[35].execfunz(first,false);
            }
            else
            {
                cout<<"No"<<endl;
                first=domande[35].execfunz(first,true);
            }
            break;
    }
    //cout<<endl;
    //getchar();
    return first;
}


//////////////////////////////////////////////////////////////////////////////////////
//Funzioni per la stampa

string checkdimensioni1(int input)//naso,cappello
{
    switch (input) {
        case 0:
            return "grande";
        case 1:
            return "normale";
        case 2:
            return "piccolo";
        case 3:
            return "assente";
        default:
            return "ERORR";
    }
}
string checkdimensioni2(int input)//occhiali,baffi
{
    switch (input) {
        case 0:
            return "grandi";
        case 1:
            return "normali";
        case 2:
            return "piccoli";
        case 3:
            return "assenti";
        default:
            return "ERORR";
    }
}
string checkdimensioni3(int input)//barba,bocca
{
    switch (input) {
        case 0:
            return "grande";
        case 1:
            return "normale";
        case 2:
            return "piccola";
        case 3:
            return "assente";
        default:
            return "ERORR";
    }
}
string checkdimensioni4(int input)//orecchie
{
    switch (input) {
        case 0:
            return "grandi";
        case 1:
            return "normali";
        case 2:
            return "piccole";
        default:
            return "ERORR";
    }
}


string checkboolsesso(int input)
{
    switch (input) {
        case 0:
            return "maschio";
        case 1:
            return "femmina";
        default:
            return "ERORR";
    }
}

string checkenumocchi(int input)
{
    switch (input) {
        case 0:
            return "marroni";
        case 1:
            return "azzurri";
        case 2:
            return "verdi";
        default:
            return "ERORR";
    }
}

string checkenumcapelli(int input)
{
    switch (input) {
        case 0:
            return "biondi";
        case 1:
            return "castani";
        case 2:
            return "rossi";
        case 3:
            return "bianchi";
        case 4:
            return "neri";
        case 5:
            return "calvo";
        default:
            return "ERORR";
    }
}

ostream& operator<<(ostream &os, Persona &p) //ridefinizione dell'output per la classe persona
{
    return os
    << "Nome:" <<p.getnome()
    << " Cappello:" << checkdimensioni1(p.getcappello())
    << " Occhiali:" << checkdimensioni2(p.getocchiali())
    << " Barba:" << checkdimensioni3(p.getbarba())
    << " Baffi:" << checkdimensioni2(p.getbaffi())
    << " Bocca:" << checkdimensioni3(p.getbocca())
    << " Naso:" << checkdimensioni1(p.getnaso())
    << " Orecchie:" << checkdimensioni4(p.getorecchie())
    << " Sesso:" << checkboolsesso(p.getsesso())
    << " Capelli:" << checkenumcapelli(p.getcapelli())
    << " Occhi:" << checkenumocchi(p.getocchi())
    
    << endl;
}

void stampaLista(Persona* first) //stampa la lista delle persone
{
    if(first!=NULL)
    {
        cout<< *first << endl;
        stampaLista(first->getnext());
    }
}

void stampaListanomi(Persona* first) //stampa la lista delle persone
{
    if(first!=NULL)
    {
        cout<< first->getnome() << ", ";
        stampaListanomi(first->getnext());
    }
    else
        cout <<"NULL"<<endl;
}


#endif


