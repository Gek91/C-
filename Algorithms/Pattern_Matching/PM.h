#include <string>
#include <iostream>
#include<algorithm> //serve per la funzione max


void ingenuo(std::string P, std::string T); //algoritmo ingenuo per indicare la posizione di un pattern P all'interno di una stringa T. Scorre semplicemente il pattern P confrontandolo con T

void ingenuoSentinella(std::string P, std::string T); //algoritmo ingenuo con l'aggiunta di sentinella

void KnuthMorrisPratt(std::string P, std::string T);// allinea P con T, quanto trova un mismatch calcola spostamenti di P in modo da non ripete il confronto di caratteri già letti di T. Solitamente i casi sono due: spostamento d[j]=min({j} U {h | 1<=h<j, j=1+h+pref[1+h]}). Nel secondo caso se le proprietà riguardanti j sono verificate si troverà un occorrenza prima dell'indice j-> indice di mismatch tra l'occorrenza di P precedente e il testo T, l'occorrenza è in posizione 1+h in P, quindi potrò risparmiare alcuni confronti. Se non è verificata l'occorrenza sarà dopo j e si ricominceranno i confronti da j con P allineato in essa. Gli spostamenti sono precalcolati nella fase di preelaborazione in relazione a j indice in P

void BoyerMoore(std::string P, std::string T); //confronta i caratteri del pattern da destra a sinistra iniziando con P allineato in prima posizione di T. Quando trova un mismatch in j vi sono due casi di spostamento del pattern successivo in cui può trovare l'occorrenza successiva sovrapposta a quella attuale: spostamento 1< h <j o j<=h<m. Il primo caso si verifica nel caso Pr[1,m-j]=Pr[1+h,m-j+h] con Pr P rovesciato. Equivale a dire che prefr[h+1]=m-j -> j=m-prefr[1+h] quindi solo in quel caso si avrà uno spostamento <j. Nel secondo caso lo spostamento sarà j<h<m se P[1,m-h]=P[h+1,m] -> P e Pr hanno bordo lung m-h per cui può esserci un'occorrenza sono per uno spostameto prefr[1+h]=m-h -> h=m-prefr[1+h]. O()


void Shift_And(std::string P, std::string T); // utilizza una rappresentazione binaria per gestire le stringhe. Crea un insieme di vettori binari, uno per ogni carattere dell'alfabeto lunghi quanto il pattern, ognivettore avrà valore 1 nelle caselle in cui la lettera risspondente al vettore compare nel pattern. Scorre poi ogni carattere del testo utilizzando poi il vettore risultato a cui applica l'operazione di bit_shift e di And con il vettore U del carattere che si trova nel posto con cui si sta confrontando. Se nel vettore risultante l'ultimo elemento è 1 si ha un occorrenza in posizione i-m+1

