#include "mapeo.h"
#include <iostream>
using namespace std;


Mapeo::Mapeo()
{

}


void Mapeo::ventana(float WX1,float WY1, float WX2, float WY2)
{
   XWmin = WX1;
   YWmin = WY1;
   XWmax = WX2;
   YWmax = WY2;
}
                   //xpvmin
void  Mapeo::puerto(int PVX1, int PVY1, int PVX2, int PVY2)
{
    XPVmin = PVX1;
    YPVmin = PVY1;
    XPVmax = PVX2;
    YPVMax = PVY2;
}
//XT y YT LA T REPRESENTA : TRANSFORMADA
void Mapeo::mapear(int X, int Y, int &XT, int *YT, int L, int M)
{
    float sX, sY;
    sX = (XPVmax-XPVmin)/(XWmax-XWmin);
    sY = (YPVMax-YPVmin)/(YWmax-YWmin);
    XT = int(round(sX*(X-XWmin)+ XPVmin+L));
    *YT = int(round(sY * ( YWmin - Y)-YPVmin + M));
}

                        //XT y YT LA T REPRESENTA : TRANSFORMADA
void Mapeo::mapear(int X, int Y, int &XT, int *YT, int L, int M, QLabel *label2, QLabel *label3)
{
    float sX, sY;
    sX = (XPVmax-XPVmin)/(XWmax-XWmin);
    label2->setText("sX = "+QString::number(double(sX)));
    sY = (YPVMax-YPVmin)/(YWmax-YWmin);
    label3->setText("sY = "+QString::number(double(sY)));

    XT = int(round(sX*(X-XWmin)+ XPVmin+L));

    *YT = int(round(sY * ( YWmin - Y)-YPVmin + M));


}
