#include "Punto.h"

double Punto::distanzaeuclidea(Punto p) const
{
    return sqrt( pow( (getx() - p.getx()) , 2) + pow( (gety() - p.gety()) , 2) );
}