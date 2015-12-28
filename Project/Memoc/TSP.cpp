
#include "TSP.h"


int distribuzione(int n) //calcola un numero maggiorante al numero passato in ingresso(il numero dei nodi) in modo da definire un valore massimo nella generazione dei numeri casuali
{
    int num=10;
    while(num<n)
    {
        num=num*10;
    }
    return num;
}

double fRand(double fMin, double fMax) // funzione per la generazione di numeri casuali tra due valori
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

bool TSP::inseriscinodo(Punto p)
{
    for(int i=0 ; i < getlista()->size() ; i++ )// controlla che non vi siano altri nodi uguali
    {
        if ( getlista()->at(i).getx() == p.getx() && getlista()->at(i).gety()==p.gety() ) //controlla se le coordinate di un punto conicidono con quello che si vuole inserire
        {
            return false; //nel caso vi siano punti uguali gia inseriti
        }
    }
    getlista()->push_back(p); //lo inserisce nella lista dei punti
    for (int i=0; i < (getlista()->size()-1); i++) //calcola la distanza euclidea da ogni altro punto gia inserito nel tsp
    {
        getarchi()->push_back(p.distanzaeuclidea(getlista()->at(i)));   //calcola la distanza euclidea e la inserisce nella lista
    }
    return true; //punto correttamente inserito
}

////////////////////////////////////////////////////////////////////////
//FUNZIONI DI CREAZIONE DEI DESIGN

void TSP::randomdesign() //design con punti disposti in maniera causuale in uno spazio delimitato
{
    int range=distribuzione(numero_punti);
    for(int i=0 ; i < numero_punti ; i++)
    {
        bool check=false;
        while (!check)
        {
            Punto p(fRand(0,range),fRand(0,range));
            check=inseriscinodo(p);
        }
    }
}

void TSP::clusterdesign()   //crea il problema generando due cluster in due posizioni casuali
{
    int range=distribuzione(numero_punti);
    Punto p1(fRand(0,range),fRand(0,range)); //punto di centro del primo cluster
    inseriscinodo(p1);
    for(int i=0 ; i < ((numero_punti/2)-1) ; i++) //punti intorno primo cluster
    {
        bool check=false;
        while (!check)
        {
            Punto p(p1.getx() + fRand(0,range)/5 , p1.gety() + fRand(0,range)/5);
            check=inseriscinodo(p);
        }
    }
    Punto p2; //punto di centro del secondo cluster
    bool check=false;
    while (!check)
    {
        p2.setvalue(fRand(0,range),fRand(0,range));
        check=inseriscinodo(p2);
    }
    for(int i=0 ; i < ((numero_punti/2)-1) ; i++) //punti intorno secondo cluster
    {
        bool check=false;
        while (!check)
        {
            Punto p( p2.getx() + fRand(0,range)/5 , p2.gety() + fRand(0,range)/5 );
            check=inseriscinodo(p);
        }
    }
}

void TSP::lineardesign()    //distribuzioni dei punti su una retta definita dai primi due punti generati casualmente
{
    int range=distribuzione(numero_punti);
    //definisco la retta usando due punti
    Punto p1(fRand(0,range),fRand(0,range)); //primo punto della retta
    inseriscinodo(p1);
    Punto p2; //secondo punto sulla retta
    bool check=false;
    while (!check)
    {
        p2.setvalue(fRand(0,range),fRand(0,range));
        check=inseriscinodo(p2);
    }

    if(p1.getx()!=p2.getx())
    { //y = mx + q, uso questa formulazione
        float m=( p2.gety() - p1.gety() )/( p2.getx() - p1.getx() ); //coefficiente m
        float q=( ( p2.getx() * p1.gety() ) - ( p1.getx() * p2.gety()))/(p2.getx()-p1.getx()); //coefficiente q
        for (int i=2; i<=numero_punti ; i++) //inserisce i restanti punti
        {
            bool check=false;
            while(!check)
            {
                double x=fRand(p1.getx(),p2.getx());
                Punto p(x,x*m+q);
                check=inseriscinodo(p);
            }
        }
    }
    else    //se i primi due punti sono su una retta orizzontale
    {
        for (int i=2; i<=numero_punti ; i++) //inserisce i restanti punti
        {
            bool check=false;
            while(!check)
            {
                double y=fRand(p1.gety(),p2.gety());
                Punto p(p1.getx(),y);
                check=inseriscinodo(p);
            }
        }
    }
}


void TSP::circledesign()    //distribuisce i punti su una circonferenza con centro al centro della distribuzione e raggio random
{
    int range=distribuzione(numero_punti);
    Punto C(fRand(0,range),fRand(0,range)); //centro della circonferenza
    double R=fRand(range/6,range/3); //dimensione del raggio della circonferenza
    for (int i=0; i < numero_punti ; i++ ) //generazione dei punti
    {
        bool check=false;
        while(!check)
        {
            double radiante=(360*fRand(0,range)*M_PI)/180; //calcolo del radiante per le coordinate del punto sulla circonferenza
            Punto p(C.getx()+(cos(radiante)*R),C.gety()+(sin(radiante)*R)); //genera il punto
            check=inseriscinodo(p); //inserisce il punto nel TSP
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//FUNZIONI DI STAMPA DATI SU FILE

void TSP::stampaarchi(FILE* f)  const   //inserisce nel file i valori degli archi
{
    fprintf(f,"%d\n\n",numero_punti); //numero dei punti nel TSP
    
    for (int i=0; i<archi.size(); i++)
    {
        fprintf(f,"%lf ",archi.at(i)); //stampa su file il valore di ogni arco
    }
}

void TSP::stampanodi(FILE* plot) const  //inserisce nel file i valori dei nodi
{
    for (int i=0; i<lista.size(); i++)
    {
        fprintf(plot,"%f,%f\n",lista.at(i).getx(),lista.at(i).gety());
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// FUNZIONI RISOLUZIONE TSP

///////////////
//calcolo soluzione iniziale

/*maxEdge
 * La funzione trova tra gli archi del problema quello più lungo e ritorna il suo indice
 * - std::vector<double> &archi: vettore contenente gli archi del problema
 * return: indice dell'arco più lungo
 */
int maxEdge(const std::vector<double> &archi)
{
    double max=-(std::numeric_limits<double>::max());
    int imax=-1;
    for (int i=0; i<archi.size(); i++) //scorre tutti gli archi
    {
        if(archi.at(i)>max) //si salva l'arco più lungo trovato fino a quel momento
        {
            imax=i;
            max=archi.at(i);
        }
    }
    return imax;
}

/*findFirstNode
 * La funzione calcola l'indice più alto degli estremi dell'arco con indice passato in ingresso
 * - int imax: indice dell'arco di cui si vuole trovare l'estremo
 * return: indice del nodo, nella lista dei nodi del problema, estremo dell'arco
 */
int findFirstNode(int imax)
{
    int j=1; //1<=j<=n*(n-1)/2
    bool find=false;
    while(!find) //trova l'estremo con l'indice più alto nel vettore dei nodi
    {
        if(imax <= indexToEdge(j,j-1) ) //(j-1)*(j-2)/2 +j-1 è il massimo indice relativo ad una arco del nodo j ((j-1)*(j-2)/2 +1 <-> (j-1)*(j-2)/2 +j-1)
        {
            find=true;
        }
        else
        {
            j++;
        }
    }
    return j;
}

/*findSecondNode
 * La funzione calcola l'indice più basso degli estremi dell'arco con indice passato in ingresso
  - int imax: indice dell'arco di cui si vuole trovare l'estremo
  - int j: indice dell'altro estremo dell'arco
 * return: secondo indice del nodo, nella lista dei nodi del problema, estremo dell'arco
 */
int findSecondNode(int imax, int j)
{
    int k=0; // 0<=k<=j-1
    bool find=false;
    while(!find) //trova l'estremo con l'indice più basso nel vettore dei nodi
    {
        if(imax == indexToEdge(j,k) ) //(j-1)*(j-2)/2 + k indici relativi ai valori da k a j
        {
            find=true;
        }
        else
        {
            k++;
        }
    }
    return k;
}

/*calculateSolution
 * richiamata da FarthestInsertion per calcolare la soluzione del problema dopo che essa è inizializzata con i primi due elementi
 * - Solution* Sol: puntatore all'oggetto che contiene la soluzione
 * - bool *Insert: vettore contenente l'informazione dei nodi ancora da inserire ed inseriti
 * - double* value: vettore contenente i valori delle distanze dal ciclo contenuto nella soluzione
 * - std::vector<double> &archi: vettore degli archi del problema
 * - int n: lunghezza della soluzione da calcolare
 */
void calculateSolution(Solution* Sol, bool *Insert, double *value, const std::vector<double> &archi, int n)
{
    while(Sol->getSolution()->size()<n)
    {
        int max=-(std::numeric_limits<double>::max());
        int imax=-1;
        for (int i=0;i<n ; i++) //cerca l'elemento più lontano dal ciclo fin ora calcolato
        {
            if(Insert[i]!=1) //se l'elemento non è gia stato inserito
            {
                if(value[i]>max) //se si è trovato un valore migliore di quello trovato fin ora aggiorno il valore di max e dell'indice corrispondente
                {
                    max=value[i];
                    imax=i;
                }
            }
        }
        Sol->insertElem(imax,archi); //inserisco il nodo trovato nella soluzione
        Insert[imax]=1; //segnalo di aver inserito il nodo nella soluzione
        for (int i=0;i<n ; i++) //aggiorna i valori delle distanze aggiungendo quelle relative al nuovo elemento inserito nella soluzione
        {
            if(Insert[i]!=1) //controlla distanze solo da nodi non inseriti
            {
                value[i]=value[i]+archi.at(indexToEdge(imax,i)); //distanze dal nodo inserito in soluzione
            }
        }
    }
}

/*FarthestInserition
 *Realizza il metodo di creazione di una soluzione FarthestInserition. Riceve in ingresso le informazioni dell'arco di inizio per la risoluzione. Genera una soluzione completa iterativamente. Ad ogni passo inserisce nella soluzione l'elemento con distanza maggiore dal ciclo già presente nella soluzione.
 * - int j: primo indice dell'arco di inizio del calcolo della soluzione
 * - int k: secondo indice dell'arco di inizio del calcolo della soluzione
 * - int iarco: indice dell'arco di inizio del calcolo della soluzione
 * - std::vector<double> &archi: vettore contenente i valori degli archi presenti nel problema
 * - int n: lunghezza della soluzione da calcolare
 * return : Soluzione del problema calcolata dalla funzione
 */
Solution* FarthestInsertion(int j, int k, int iarco,const std::vector<double> &archi, int n)
{
    Solution* Sol= new Solution(); //creo un oggetto soluzione
    bool *Insert=(bool*) calloc (n,sizeof(bool)); //vettore che indica quali nodi sono gia stati inseriti nella soluzione identificati dall'indice nel vettore che li contiene
    double *value=(double*) calloc (n,sizeof(double)); //vettore utile per salvare le distanze tra i nodi nella soluzione e i nodi non nella soluzione
    
    //inizializza la soluzione con il ciclo di due elementi estremi dell'arco calcolato,
    Sol->setValSol(archi.at(iarco)*2);
    Sol->insertElem(j,archi);
    Insert[j]=1; //indico nel vettore Insert che li ho inseriti nella soluzione
    Sol->insertElem(k,archi);
    Insert[k]=1;
    for (int i=0;i<n ; i++) //inizializza il vettore delle distanze inserendo le distanze dai nodi non nella soluzione con i primi due nodi inseriti
    {
        if(Insert[i]!=1) //controlla solo distanze da nodi non inseriti
        {
            value[i]=archi.at(indexToEdge(j,i)); //distanze da j
            value[i]=value[i]+archi.at(indexToEdge(k,i)); //distanze da k
        }
    }
    //inserisce gli altri elementi nella soluzione
    calculateSolution(Sol,Insert,value,archi,n);
    
    free(Insert);
    free(value);
    return Sol;
}

Solution* TSP::initSolution() const  //calcola una soluzione iniziare del problema usando la tecnica di Farthest Insertion
{
    //Inizia calcolando il ciclo di due elementi scegliendo i più distanti nel TSP
    int imax=maxEdge(archi); //calcola l'arco più lungo del TSP
    //trova gli estremi dell'arco
    int j=findFirstNode(imax); //trova l'indice del primo estremo dell'arco
    int k=findSecondNode(imax,j); //trova l'indice del secondo estremo
    // k e j contengono gli indici relativi all'arco selezionato
    Solution* Sol=FarthestInsertion(j,k,imax,archi,numero_punti); //metodo Farthest Insertion
    return Sol;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Ricerca di vicinato


/////////TwoOPT
/* twoOpt
 * Inverte gli elementi all'interno della soluzione dalla posizione i alla posizione j
 * - std::vector<int> &S: vettore contenente la soluzione del problema
 * - int i: primo indice delle due posizione tra cui invertire i valori
 * - int j: secondo indice delle due posizione tra cui invertire i valori
 */
void twoOpt( std::vector<int> &S,int i, int j) //inverte gli elementi di S dalla posizione i alla posizione j
{
    int n=j-i;
    n=n/2;
    int sup;
    for (int k=0; k<=n; k++)
    {
        sup=S.at(i+k);
        S.at(i+k)=S.at(j-k);
        S.at(j-k)=sup;
    }
}

/* twoOptvalue
 * calcola in maniera veloce come si modificherebbe la soluzione nel caso si applicasse l'operazione di twoOpt con i due indici passati in ingresso. Utile per scegliere il vicino migliore senza doverlo calcolare
 * - std::vector<int> *S: vettore contenente la soluzione
 * - std::vector<double> &archi: vettore contenente gli archi del problema
 * - int i: primo indice per l'applicazione del twoOpt
 * - int j: secondo indice per l'applicazione del twoOpt
 * return: ritorna la differenza di valore che subirebbe la funzione obbiettivo se si applicase il twoOpt tra i due indici passati
 */
double twoOptvalue(const std::vector<int> *S, const std::vector<double> &archi, int i, int j )//valore nuova soluzione pari ad: Cnew=Cold - C(i-1,i) - C(j,j+1) + C(i-1,j) + C(i,j+1)
{
    double value= -archi.at(indexToEdge(S->at(i-1),S->at(i))) - archi.at(indexToEdge(S->at(j),S->at(j+1))) + archi.at(indexToEdge(S->at(i-1),S->at(j))) +archi.at(indexToEdge(S->at(i),S->at(j+1))) ;
    if (fabs(value) < 0.00001) //elimina eventuali errori di troncamento
        value=0;
    return value;
}

/*checktlist2opt
 * Funzione che controlla se i due indici passati in ingresso siano già stati usati per effettuare una mossa nell'algoritmo. Se così è vieta il loro utilizzo
 * int i: primo indice in ingresso
 * int j: secondo indice in ingresso
 * tabuList* tl: tabu list su cui si effettua il controllo
 */
bool checktlist2opt(int i, int j, TabuList* tl)
{
    if(tl==0) //se la lista è vuota permette la mossa
    {
        return 1;
    }
    
    for(int h=0; h<tl->getTlist()->size(); h++)
    {
        if(i==tl->getTlist()->at(h).getIndici()[0] || i==tl->getTlist()->at(h).getIndici()[1]) //primo indice, controlla se nella tabu list esiste una mossa contenente quell'indice
        {
            if (j==tl->getTlist()->at(h).getIndici()[0] || j==tl->getTlist()->at(h).getIndici()[1] ) //se esiste controlla se tale mossa utilizza anche il secondo indice
            {
                return 0; //se trova una mossa che ha utilizzato i due indici vieta il loro utilizzo per la prossima mossa
            }
        }
    }
    return 1; //se non vi è nessuna mossa con gli indici specificati permette la mossa
}

/*twoOptFunc
 * Esplora il vicinato della soluzione e ritorna il migliore valore in esso. Utilizza twoOptvalue per il calcolo della variazione del risultato, ed in relazione ad esso seleziona il migliore
 * - std::vector<int> *S: vettore contenente la soluzione
 * - std::vector<double> &archi: vettore contenente gli archi del problema
 * - double &min: soluzione minima di centro, aggiornata se trovato valore migliore
 * - TabuList* tl: tabu list utilizzata per la risoluzione della tabu search, 0 se non usato
 * return: gli indici corrispondenti alla mossa da eseguire, in min sarà tornata la variazione di risultato all'applicare la mossa scelta
 */
int* twoOptFunc(std::vector<int> *S,const std::vector<double> &archi, double &min, TabuList* tl)
{
    int* imin=(int*) calloc (2,sizeof(int)); //indici utilizzati per calcolcolare la soluzione
    for(int i=1; i < (S->size()-2); i++)
    {
        for(int j=i+1; j < (S->size()-1); j++) //tutte le possibili combinazioni di indici
        {
            if(checktlist2opt(i,j,tl))
            {
                double value= twoOptvalue(S,archi,i,j) ;
                if(value<min) // si salva il valore minimo trovato fin ora nel vicinato e i relativi vicini
                {
                    imin[0]=i;
                    imin[1]=j;
                    min=value;
                }
            }
        }
    }
    return imin;
}

/////////ThreeOPT
/* threeOpt
 * Inverte gli elementi all'interno della soluzione dalla posizione i alla posizione j e dalla posizione j e k
 * - std::vector<int> &S: vettore contenente la soluzione del problema
 * - int i: primo indice delle tre posizione tra cui invertire i valori
 * - int j: secondo indice delle tre posizione tra cui invertire i valori
 * - int k: terzo indice delle tre posizione tra cui invertire i valori
 */
void threeOpt( std::vector<int> &S,int i, int j, int k )
{
    twoOpt(S,i,j);
    twoOpt(S,j,k);
}

/* threeOptvalue
 * calcola in maniera veloce come si modificherebbe la soluzione nel caso si applicasse l'operazione di threeOpt con i tre indici passati in ingresso. Utile per scegliere il vicino migliore senza doverlo calcolare
 * - std::vector<int> *S: vettore contenente la soluzione
 * - std::vector<double> &archi: vettore contenente gli archi del problema
 * - int i: primo indice per l'applicazione del threeOpt
 * - int j: secondo indice per l'applicazione del threeOpt
 * - int k: terzo indice per l'applicazione del threeOpt
 * return: ritorna la differenza di valore che subirebbe la funzione obbiettivo se si applicase il threeOpt tra i due indici passati
 */
double threeOptvalue(const std::vector<int> *S, const std::vector<double> &archi, int i, int j, int k )
{
    std::vector<int> sol=*S;
    double value= twoOptvalue(&sol,archi,i,j);
    twoOpt(sol,i,j); //occorre calcolare il secondo spostamento (j,k) dopo aver eseguito la modifica portata dal primo(i,j) per ottenere il risultato giusto
    return value + twoOptvalue(&sol,archi,j,k);
}

/*checktlist3opt
 * Funzione che controlla se i tre indici passati in ingresso sono già stati usati per effettuare una mossa nell'algoritmo. Se così è vieta il loro utilizzo
 * int i: primo indice in ingresso
 * int j: secondo indice in ingresso
 * int k: terzo indice in ingresso
 * tabuList* tl: tabu list su cui si effettua il controllo
 */
bool checktlist3opt(int i, int j, int k, TabuList* tl)
{
    if(tl==0) //se la tabu list è vuota permette la mossa
    {
        return 1;
    }
    
    for(int h=0; h<tl->getTlist()->size(); h++) //scorre gli elementi della tabu list
    {
        if(i==tl->getTlist()->at(h).getIndici()[0] || i==tl->getTlist()->at(h).getIndici()[1] || i==tl->getTlist()->at(h).getIndici()[2] ) //primo indice, controlla vi sia una mossa con quell'indice
        {
           if (j==tl->getTlist()->at(h).getIndici()[0] || j==tl->getTlist()->at(h).getIndici()[1] || j==tl->getTlist()->at(h).getIndici()[2] ) //se vi è una mossa che utilizza il primo indice controlla se utilizzi anche il secondo indice
            {
                if(k==tl->getTlist()->at(h).getIndici()[0] || k==tl->getTlist()->at(h).getIndici()[1] || k==tl->getTlist()->at(h).getIndici()[2] ) //se vi è una mossa che utilizza il primo e il secondo indice controlla se utilizzi anche il terzo indice
                {
                    return 0; //se nella lista esiste una mossa che ha già utilizzato tutti e tre gli indici vieta l'esecuzione della mossa
                }
            }
        }
    }
    return 1; // se non vi è la permette
}

/*threeOptFunc
 * Esplora il vicinato e ritorna la soluzione la soluzione migliore
 * - std::vector<int> *S: vettore contenente la soluzione
 * - std::vector<double> &archi: vettore contenente gli archi del problema
 * - double &min: soluzione minima di centro, aggiornata se trovato valore migliore
 * - TabuList* tl: tabu list utilizzata per la risoluzione della tabu search, 0 se non usato
 * return: gli indici corrispondenti alla mossa da eseguire, in mi sarà tornata la variazione di risultato all'applicare la mossa scelta
 */
int* threeOptFunc(std::vector<int> *S,const std::vector<double> &archi, double &min, TabuList* tl)
{
    int* imin=(int*) calloc (3,sizeof(int)); //indici utilizzati per calcolcolare la soluzione
    for(int i=1; i < (S->size()-3) ; i++)
    {
        for(int j=i+1; j < (S->size()-2); j++) //tutte le possibili combinazioni di indici
        {
            for (int k=j+1; k < (S->size()-1) ; k++)
            {
                if(checktlist3opt(i,j,k,tl))
                {
                    double value= threeOptvalue(S,archi,i,j,k) ;
                    if(value<min) // si salva il valore minimo trovato fin ora nel vicinato e i relativi vicini
                    {
                        imin[0]=i;
                        imin[1]=j;
                        imin[2]=k;
                        min=value;
                    }
                }
            }
        }
    }
    return imin;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Neighborhood

/*neighborhoodSolution
 * Calcola a partire da una soluzione iniziale la migliore soluzione di vicinato. Se non la trova ritorna la soluzione in ingresso altrimenti ripete la ricerca di vicinato da quella che ha trovato. Può utilizzare ricerca di vicinato attraverso twoOpt o ThreeOpt
 * - Solution *Sol: soluzione iniziale passata in ingresso
 * - const std::vector<double> &archi: vettore contenente gli archi del problema
 * - bool opt: valore boolenato utile ad indicare se si utilizzerà twoOpt o Three Opt
 */
Solution * neighborhoodSolution(Solution *Sol, const std::vector<double> &archi , bool opt)
{
    double variazione_miglior_scelta=std::numeric_limits<double>::max(); //inizializza min con il massimo valore, in modo da accettare qualsiasi soluzione trovata
    std::vector<int> *S=Sol->getSolution(); //vettore contenente la soluzione di centro
    //Esecuzione della ricerca di vicinato
    if(opt)    //TWOOPVALUE
    {
        int* bestmove=twoOptFunc(S,archi,variazione_miglior_scelta,0);

        if(variazione_miglior_scelta<0) //se la variazione è negativa la soluzione trovata sarà migliore
        {
            twoOpt(*S, bestmove[0], bestmove[1]); //calcola la soluzione trovata
            Sol->ricalcolaVal(archi);
            Sol=neighborhoodSolution(Sol,archi,opt); // esegue la ricerca di vicinato a partire dalla soluzione trovata
        }
        free(bestmove);
    }
    else    // THREEOPVALUE
    {
        int* bestmove=threeOptFunc(S,archi,variazione_miglior_scelta,0);

        if(variazione_miglior_scelta<0) //se la variazione è negativa la soluzione trovata sarà migliore
        {
            threeOpt(*S, bestmove[0], bestmove[1],bestmove[2]); //calcola la soluzione trovata
            Sol->ricalcolaVal(archi);
            Sol=neighborhoodSolution(Sol,archi,opt); // esegue la ricerca di vicinato a partire dalla soluzione trovata
        }
        free(bestmove);
    }
    return Sol;
}

////////////////////////////
//generazione random

void scambiorandom(std::vector<int>* S,int n) //scambia casualmente alcuni indici della soluzione generando un'altra soluzione casuale
{
    int scambi=n/2;
    for (int i=0; i<scambi ; i++)
    {
        int indice1 = rand() % n;
        int indice2 = rand() % n;
        int h;
        h=S->at(indice1);
        S->at(indice1)=S->at(indice2);
        S->at(indice2)=h;
    }
}

/*resolveTSP
 * Genera una soluzione iniziale attraverso initSolution, a partire da essa esegue delle ricerche di vicinato applicando perturbazioni in modo da calcolare altri minimi locali.
 * - int n_ripartenze: numero di ripartenze effettuate dall'algoritmo 
 * - bool opt: metodologia di ricerca vicinato utilizzata
 * return: migliore soluzione calcolata dall'algoritmo
 */
Solution* TSP::resolveTSP(int n_ripartenze, bool opt) const
{
    Solution *s=initSolution(); //genera la soluzione iniziale con un metodo euristico
    Solution *s2=new Solution(*s);
    Solution *ret=new Solution(*s);
    
    

    for (int i=0; i<n_ripartenze; i++)
    {
        //Applico perturbazioni sulla soluzione iniziale
        s=neighborhoodSolution(s,archi,opt); //calcola la migliore soluzione di vicinato
        if( s->getValSol() < ret->getValSol() ) //mantiene solo il valore migliore
        {
            ret= new Solution(*s);;
        }
        s=new Solution(*s2); //ricopia la soluzione iniziale
        scambiorandom(s->getSolution(), numero_punti); //esegue degli scambi random tra gli archi
        s->ricalcolaVal(archi); //aggiorna il valore della soluzione dopo gli scambi
    }
    
    delete(s);
    delete (s2);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//TABUSEARCH

/*  neighborhoodTabuSolution
 * La funzione esegue il calcolo del miglior valore di vicinato trovato a partire da una soluzione di centro al netto delle mosse rese tabu. Confronta poi il valore calcolato con il migliore trovato fino a quel momento. Al termine in Ret si trova la miglior soluzione trovata dall'algoritmo
 * - Solution *Sol: soluzione di centro su cui eseguire la ricerca di vicinato
 * - Solution *Ret: soluzione migliore trovata fin ora
 * - const std::vector<double> &archi: vettore contenente gli archi del problema
 * - TabuList* Tl: tabu list utilizzata dal metodo
 * - int &iter: numero di iterazioni senza soluzioni miglioranti
 * - int maxiter: numero massimo di iterazioni senza soluzioni miglioranti, criterio di arresto
 * - bool opt: metodologia di ricerca vicinato utilizzata
 */

Solution * neighborhoodTabuSolution( Solution *Sol, Solution *Ret, const std::vector<double> &archi ,TabuList* Tl,int &iter, int maxiter ,bool opt)
{
    double variazione_miglior_scelta=std::numeric_limits<double>::max(); //inizializza min con il massimo valore, in modo da accettare qualsiasi soluzione trovata
    std::vector<int> *S=Sol->getSolution(); //vettore contenente la soluzione di centro

    if(opt)    //TWOOPVALUE
    {
        int* bestmove=twoOptFunc(S,archi,variazione_miglior_scelta,Tl);

        Mossa m(2); //inserisce la mossa nella tabu list
        m.setIndice(bestmove[0],0);
        m.setIndice(bestmove[1],1);
        Tl->addElem(m);
        
        twoOpt(*S, bestmove[0], bestmove[1]); //calcola la soluzione trovata
        free(bestmove);
    }
    else    // THREEOPVALUE
    {
        int* bestmove=threeOptFunc(S,archi,variazione_miglior_scelta,Tl);
        
        Mossa m(3); //inserisce la mossa nella tabu list
        m.setIndice(bestmove[0],0);
        m.setIndice(bestmove[1],1);
        m.setIndice(bestmove[2],2);
        Tl->addElem(m);
        
        threeOpt(*S, bestmove[0], bestmove[1],bestmove[2]); //calcola la soluzione trovata
        free(bestmove);
    }
    Sol->ricalcolaVal(archi); //calcola il valore della soluzione trovata nel vicinato
    //std::cout<<Sol->getValSol()<<","<< Ret->getValSol()<<"  "<<iter <<std::endl;
    if(Sol->getValSol() < Ret->getValSol()) //controlla se il miglior valore di vicinato trovato ha un valore migliore a quello fin ora trovato dall'algoritmo
    {
        delete(Ret);
        Ret=new Solution(*Sol); //aggiorna il valore della miglior soluzione
        iter=0; // azzera il numero di iterazioni senza miglioramenti
    }
    else
    {
        iter++; //altrimenti aumenta il numero di iterazioni senza miglioramenti
    }

    if(iter<maxiter) //se non si è arrivato al criterio di arresto
    {
        Ret=neighborhoodTabuSolution(Sol,Ret,archi ,Tl,iter,maxiter ,opt); //richiama la funzione ricorsivamente con centro del vicinato il nuovo valore trovato
    }
    return Ret;
}

/*TabuSearch
 * genera la soluzione iniziale attraverso initSolution, a partire da essa esegue una ricerca di vicinato utilizzando la tecnica della tabu search
 * - int dim: dimensioni della tabu list
 * - int maxiter: massimo numero di iterazioni senza migliorare il risultato, criterio d'arresto del metodo
 * - bool opt: metodologia di ricerca vicinato utilizzata
 */
Solution* TSP::TabuSearch(int dim, int maxiter, bool opt) const
{
    Solution *s=initSolution(); //genera la soluzione iniziale con un metodo euristico

    Solution *ret=new Solution(*s);
    int iter=0;
    TabuList* Tl= new TabuList(dim); //tabu list utilizzata dall'algoritmo di ricerca vicinato
    
    ret=neighborhoodTabuSolution(s,ret,archi,Tl,iter, maxiter, opt ); //ricerca di vicinato con tabu list
    
    delete(s);
    delete (Tl);
    return ret;
}



