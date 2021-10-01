#ifndef MAPEO_H
#define MAPEO_H
#include <math.h>
#include <QLabel>

class Mapeo
{
    //EN EL MUNDO REAL SE PUEDEN UTILIZAR DIFERENTES TIPOS DE MEDIDAS (mm,cm,m,  pulg, yardas, millas...)
    float XWmin, YWmin, XWmax,YWmax;
    int XPVmin, YPVmin, XPVmax, YPVMax;

public:
    Mapeo();
    //DEFINIMOS EL AREA RECTANGULAR DEL MUNDO, DE DONDE PROVIENE LO QUE SE VA A DIBUJAR
    void ventana(float WX1,float WY1, float WX2, float WY2);

    //DEFINIMOS EL AREA RECTANGULAR DEL PUERTO DE VISION, DE DONDE SE VA A DIBUJAR
    void  puerto(int PVX1, int PVY1, int PVX2, int PVY2);

    void mapear(int X, int Y, int &XT, int *YT, int L, int M);
                           // & = referencia o direccion de memoria
                           // * = puntero
                                              //SOLO PARA ESCRIBIR LOS VALORES DE ESCALACIÓN APLICADA
    void mapear(int X, int Y, int &XT, int *YT, int L, int M, QLabel *label2,QLabel *label3);
                           // & = referencia o direccion de memoria
                           // * = puntero

};

#endif // MAPEO_H
