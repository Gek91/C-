#include "Punto.h"

std::ostream& operator<< (std::ostream &os, const Punto &p)
{
    os << "("<<p.getx()<<","<<p.gety()<<")";
    return os;
    }
