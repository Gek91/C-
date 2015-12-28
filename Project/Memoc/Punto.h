#ifndef PUNTO_H
#define PUNTO_H

#include <cmath>
#include <fstream>

// classe utilizzata per rappresentare i punti del problema. Punti a due dimensioni

class Punto
{
    double x; //coordinata x del punto
    double y; //coordinata y del punto
public:
    double distanzaeuclidea(Punto p) const; //calcola la distanza euclidea con il seguente punto e un altro passato come parametro
    Punto(double a, double b){ setvalue(a,b);}//costruttore con in ingresso i due valori
    Punto(){x=0;y=0;};//costruttore senza parametri
    void setvalue(double a, double b){x=a; y=b;} //funzione che imposta i valori delle coordinate del punto
    double getx() const {return x;} //ritorna il valore della coordinata x del punto
    double gety() const {return y;} //ritorna il valore della coordinata y del punto
};

#endif