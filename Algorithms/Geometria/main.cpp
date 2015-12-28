#include "Geometria.h"



int main()
{
    Punto* lista=(Punto*) malloc (sizeof( Punto)*9);
    lista[0]=Punto(2,2);
    lista[1]=Punto(1,1);
    lista[2]=Punto(2,1);
    lista[3]=Punto(1,2);
    lista[4]=Punto(3,2);
    lista[5]=Punto(1,3);
    lista[6]=Punto(3,3);
    lista[7]=Punto(2,3);
    lista[8]=Punto(4,4);
    

    Segmento* segmenti=(Segmento*) malloc (sizeof(Segmento)*2);
    segmenti[0]=Segmento(lista[0],lista[1]);
    segmenti[1]=Segmento(lista[2],lista[3]);
    
    // PROVA ANGLe_LEFT
    cout<<"Angle_Left"<<endl;
    int d=Angle_Left(lista[0],lista[1],lista[2]);
    
    if(d>0)
    {
        std::cout<<"Antiorario"<< std::endl;
    }
    else if(d<0)
    {
        std::cout<<"Orario"<< std::endl;
    }
    else
    {
        std::cout<<"Collineari"<< std::endl;
    }
    
    //PROVA SEGMENT_INTERSC
    cout<<"Segment_Intersec"<<endl;
    bool res= Segments_Intersec(lista[0],lista[1],lista[2],lista[3]);
    if(res)
    {
        std::cout<<"Si intersecano"<<std::endl;
    }
    else
    {
        std::cout<<"Non si intersecano"<<std::endl;
    }
    
    cout<<"Graham"<<endl;
    //Graham
    Pila<Punto>* P=Graham_Scan(lista,9);
    cout<<P->getDim()<<endl;
    P->printPila();
    delete(P);
    
    cout<<"Jarvis"<<endl;
    //Jarvis
    Punto* H=(Punto*) malloc (sizeof(Punto)*9); //vettore che contiene l'involucro
    int k=Jarvis_March(lista,9,H);
    for (int i=0; i<=k; i++)
    {
        cout<<H[i]<<endl;
    }
    
    cout<<"Any_Segment_Intersec"<<endl;
    //Any_Segment_Intersec
    std::cout<<segmenti[0].geti().getx()<<","<<segmenti[0].geti().gety()<<std::endl;
    std::cout<<segmenti[0].getf().getx()<<","<<segmenti[0].getf().gety()<<std::endl;
    std::cout<<segmenti[1].geti().getx()<<","<<segmenti[1].geti().gety()<<std::endl;
    std::cout<<segmenti[1].getf().getx()<<","<<segmenti[1].getf().gety()<<std::endl;
    cout<<Any_Segment_Intersec(segmenti,2)<<endl;

   
    return 0;
}