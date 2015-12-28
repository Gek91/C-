//main.c

#include "header.h"

int main()
{
    
    ////////////////////////////////////////////
    //inizializza le strutture
    initdomande(&domande[0]); //inizializza l'array domande
    srand(time(NULL)); //inizializza le variabili per la generazione casuale
    //int arraydomande1[N_DOMANDE]={0};//array per tenere traccia delle domande gia fatte
    int arraydomande1[N_DOMANDE]={0};
    int arraydomande2[N_DOMANDE]={0};//array per tenere traccia delle domande gia fatte
    Persona* first1=new Persona(1); //prima lista personaggi(giocatore 1)
    Persona* first2=new Persona(first1,NULL);//prima lista personaggi(giocatore 2)
    for(int i=2;i<N_PERSONE;i++)//crea le liste della lunghezza desiderata, uguali
    {
        first1=aggiungipersona(first1,i);
        first2=new Persona(first1,first2);
    }
    Persona* scelta1=sceltapersona(first1);  //sceglie il personaggio del giocatore
    Persona* scelta2=sceltapersona(first2);  //sceglie il personaggio del l'IA
    while(scelta1->getnome()==scelta2->getnome()) //controlla che le due scelte non siano uguali
        scelta2=sceltapersona(first2);
    
    first1=rimuoviscelta(first1,scelta1);   //elimina dalle liste dei proprietari i personaggi scelti
    first2=rimuoviscelta(first2,scelta2);
    
    int turno=1;
    bool fine=false;
    while(fine==false)//ciclo di gioco
    {
        //giocatore
        cout<<"Turno n:"<<turno<<" Giocatore 1"<<endl;
        cout<<endl;
        stampaLista(first1);
        getchar();
        cout<<endl;
        if(GIOCATORE1==1)
            first1=domanda(first1,scelta2);
        else
            first1=domandaIA(first1,scelta2,&arraydomande1[0]);
        getchar();
        cout<<endl;
        stampaLista(first1);
        getchar();
        cout<<endl;
        if(first1->getnext()==NULL)
            if(first1->getnome()==scelta2->getnome())
            {
                cout<<"Giocatore 1 ha vinto in "<<turno<<" turni"<<endl;
                getchar();
                fine=true;
            }
        //IA
        if(fine==false)
        {
            cout<<"Turno n:"<<turno<<" Giocatore 2"<<endl;
            cout<<endl;
            stampaLista(first2);
            getchar();
            cout<<endl;
            if(GIOCATORE2==1)
                first2=domanda(first2,scelta1);
            else
                first2=domandaIA(first2,scelta1,&arraydomande2[0]);
            getchar();
            cout<<endl;
            stampaLista(first2);
            getchar();
            cout<<endl;
            if(first2->getnext()==NULL)
                if(first2->getnome()==scelta1->getnome())
                {
                    cout<<"Giocatore 2 ha vinto in "<<turno<<" turni"<<endl;
                    getchar();
                    fine=true;
                }
        }
        turno++;
    }
    
    cout<<"Personaggio Giocatore 1"<<endl;
    cout<<scelta1->getnome()<<endl;

    cout<<"Personaggio Giocatore 2"<<endl;
    cout<<scelta2->getnome()<<endl;
    
    delete(scelta1);
    liberalista(first1);
    delete(scelta2);
    liberalista(first2);
}