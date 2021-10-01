#include "graficos.h"


graficos::graficos()
{

}

void graficos::lineaDDA(int x1, int y1, int x2, int y2, QPainter *canvas)
{
    int pasos;
    //Diferencias de x, y
    int dx = x2 - x1;
    int dy = y2 - y1;

    float x_inc, y_inc, x = x1, y = y1;

    if(abs(dx) > abs(dy))
        pasos = abs(dx);
    else
        pasos = abs(dy);

    x_inc = (float)dx/pasos;
    y_inc = (float)dy/pasos;

    QPen pen(QColor(0,0,200),1);//El 1 indica el grosor del pixel
    canvas->setPen(pen);

    canvas->drawPoint(round(x),round(y));
    for(int i = 0; i <= pasos; i++){
        x += x_inc;
        y += y_inc;
        canvas->drawPoint(round(x),round(y));
    }

}

void graficos::lineaDDA(int x1, int y1, int x2, int y2, QPainter *canvas, QColor color)
{
    int pasos;
    //Diferencias de x, y
    int dx = x2 - x1;
    int dy = y2 - y1;

    float x_inc = 0, y_inc = 0, x = x1, y = y1;

    if(abs(dx) > abs(dy))
        pasos = abs(dx);
    else
        pasos = abs(dy);

    x_inc = (float)dx/pasos;
    y_inc = (float)dy/pasos;

    QPen pen(color,15);//El 1 indica el grosor del pixel
    canvas->setPen(color);

    canvas->drawPoint(round(x),round(y));
    for(int i = 0; i <= pasos; i++){
        x += x_inc;
        y += y_inc;
        canvas->drawPoint(round(x),round(y));
    }

}

