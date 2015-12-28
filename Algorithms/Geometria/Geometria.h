#ifndef GEOMETRIA_H
#define GEOMETRIA_H
#include "Segmento.h"
#include "Evento.h"
#include <climits>
#include <cstdlib>
#include <math.h> //fabs()
#include <limits> //max int
#include "../Strutture_Dati/Pila/Pila.h"
#include "../Ordinamento/ord.h"
#include "../Strutture_Dati/Albero RB/AlberoRB.h"


int Angle_Left(Punto p0, Punto p1, Punto p2); // Funzione che prende in ingresso tre punti P0 P1 P2 e indica se il vettore P0P2 è ruotato in senso orario o antiorario rispetto al vettore P0P1. Utilizza prodotto vettoriale per determinarlo.

int Turn_Left(Punto p0, Punto p1, Punto p2); //la funzione prende in ingresso tre punti P0 P1 P2, indica in che modo il segmento P1P2 è ruotato rispetto al segmento P0P1. Utilizza la funzione Angle_left

bool Segments_Intersec(Punto p1, Punto p2, Punto p3, Punto p4); // funzione che prende in ingresso 4 punti p0 p1 p2 p3 e indica se i segmenti p1p2 p3p4 si intersecano. utilizza la funzione angle_left per determinare le posizione dei vari punti rispetto all'altro segmento

Pila<Punto>* Graham_Scan(Punto lista[], int n); //Costruisce l'involuco convesso a partire da una lista di punti. Trova il punto più basso a sinistra, ordina gli altri elementi secondo l'angolo polare in relazione a quest'ultimo. A partire da questo ordine inserisce uno alla volta i punti nell'involucro in un pila, se l'inserimento di un punto comporta una curva verso sinistra elimina i precedenti inserimenti fino a quando non è eliminata la curva. Quando termina tutti gli elementi ritorna la pila contenente i punti dell'involuco convesso in ordine

int Jarvis_March(Punto lista[], int n, Punto H[]); // Costruisce l'involucro convesso a partire da una lista di punti. Trova il punto più in basso a sinistra e quello più in alto a destra. A partire da quello più in basso cerca il punto con l'angolo polare destro più piccolo rispetto ad esso e lo aggiunge all'involucro. Dall'ultimo nodo inserito riesegue questa azione fino a trovarsi nel punto più in alto a destra. Da li in poi continua nello stesso modo ma usando l'angolo polare sinistro. Ritorna il numero di elementi presenti nel vettore risultante H

bool Any_Segment_Intersec(Segmento segmenti[],int n); //Da una lista di segmenti ritorna se almeno due di essi si intersecano. Crea un evento per ogni capo di un segmento e li ordina. Scorre poi la lista ordinata deigli eventi, ad ogni evento controsse se si tratta un evento di inizio segmento o fine. Se è inizio controlla se il segmento inserito si intersecherà con i segmenti adiacenti attraverso Segments_Intersec. Ogni fine controlla se i segmenti adiacenti a quello finito si intersecano fra loro.

#endif