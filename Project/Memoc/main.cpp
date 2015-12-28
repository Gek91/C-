

//#include "cplex.cpp"
#include <stdio.h>
#include "TSP.h"
#include <time.h>
#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <limits>
#include <sstream>
#include <string>
#include <cmath>

int main(int argc, char* argv[])
{
    if(argc<=6)
    {
        std::cout<<"Numero parametri sbagliato:\n 1 = numero nodi del problema \n 2 = tipologia del generatore(1-4) \n 3 = 2otp/3opt(1-0) \n 4 = Numero restart per risolutore con random multistart\n 5 = Lunghezza tabu list per tabu search\n 6 = numero iterazioni senza miglioramenti per tabu search"<<std::endl;
        exit(0);
    }
    int N_NODI=atoi(argv[1]); //grandezza del problema
    int T_GEN=atoi(argv[2]); //tipologia di generatore per il problema: 1=random, 2=circle, 3=linear, 4=cluster
    int N_OPT=atoi(argv[3]); //0=3 opt , 1= 2 opt
    int N_REST=atoi(argv[4]); //n restart
    int L_LIST=atoi(argv[5]); //lunghezza tabu list
    int ITER=atoi(argv[6]); //numero iterazioni senza miglioramenti
    
    srand(time(0));
    
    FILE *archi;
    FILE *nodi;
    
    archi=fopen("archi.txt","w");    //apri il file su cui verranno salvati i valori del peso degli archi
    if(!archi) {
        std::cout<<"Errore nella creazione del file!";
        return -1;
    }
    
    nodi=fopen("nodi.txt","w");    //apri il file su cui verranno salvate le coordinate dei punti per la stampa
    if(!nodi) {
        std::cout<<"Errore nella creazione del file!";
        return -1;
    }
    
    /////////////////////////////////////////////////////////////////////////////////
    //Generazione del problema
    
    // crea un design nel TSP
    TSP* problema= new TSP(N_NODI);
    
    switch (T_GEN) {
        case 1:
            problema->randomdesign();
            break;
        case 2:
            problema->circledesign();
            break;
        case 3:
            problema->lineardesign();
            break;
        case 4:
            problema->clusterdesign();
            break;
        default:
            std::cout<<"Valore tipologia di generatore non valido"<<std::endl;
            exit(0);
            break;
    }

    if(N_OPT!=0 && N_OPT!=1)
    {
        std::cout <<"Valore scelta opt non valido"<<std::endl;
        exit(0);
    }
    
    // stampa i dati su file
    problema->stampaarchi(archi);
    problema->stampanodi(nodi);
    
    ///////////////////////////////////////////////////////////////////////////////////
    //Risoluzione del problema
    clock_t start1 = clock();
    Solution *s1=problema->initSolution(); //inizializza una soluzione del problema
    clock_t end1 = clock();
    std::cout<<"Inizializzazione soluzione"<<std::endl;
    printf("Tempo di Esecuzione =  %f secondi \n", ((double)(end1 - start1)) / CLOCKS_PER_SEC);
    std::cout<<"Soluzione definitiva: "<<s1->getValSol()<<std::endl;
    for(int i=0; i < s1->getSolution()->size() ; i++)
    {
        std::cout<< s1->getSolution()->at(i)<< " ";
    }
    std::cout<<"\n\n\n";


    clock_t start2 = clock();
    Solution *s2=problema->resolveTSP(N_REST,N_OPT); //utilizza il metodo Random Multistart
    clock_t end2 = clock();
    std::cout<<"Random Multistart: N restart="<<N_REST<<std::endl;
    printf("Tempo di Esecuzione =  %f secondi \n", ((double)(end2 - start2)) / CLOCKS_PER_SEC);
    std::cout<<"Soluzione definitiva: "<<s2->getValSol()<<std::endl;
    for(int i=0; i < s2->getSolution()->size() ; i++)
    {
        std::cout<< s2->getSolution()->at(i)<< " ";
    }
    std::cout<<"\n\n\n";
    
    
    clock_t start3 = clock();
    Solution *s3=problema->TabuSearch(L_LIST,ITER,N_OPT); //utilizza il metodo Tabu Search
    clock_t end3 = clock();
    std::cout<<"Tabu Search: Lunghezza Tabu list="<<L_LIST<<" Iterazioni senza miglioramenti="<<ITER<<std::endl;
    printf("Tempo di Esecuzione =  %f secondi \n", ((double)(end3 - start3)) / CLOCKS_PER_SEC);
    std::cout<<"Soluzione definitiva: "<<s3->getValSol()<<std::endl;
    for(int i=0; i < s3->getSolution()->size() ; i++)
    {
        std::cout<< s3->getSolution()->at(i)<< " ";
    }
    std::cout<<"\n\n\n";
    
    delete(s1);
    delete(s2);
    delete(s3);
    delete(problema);
    fclose(archi);
    fclose(nodi);
}
