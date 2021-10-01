#include "graficos.h"

#include <math.h>
#include <QtMath>

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

void graficos::circuloPitagoras(int xc, int yc, int radio, QPainter *canvas)
{
    canvas->setPen(QColor(0,0,255));
    float y;
    for (int x = xc - radio; x <= xc + radio; x++) {
         y = yc + sqrt(double(double(radio*radio) - pow(double(x-xc),2.0)));
         canvas->drawPoint(x,round(y));
         y = yc - sqrt(double(double(radio*radio) - pow(double(x-xc),2.0)));
         canvas->drawPoint(x,qRound(y));
    }
}

void graficos::circuloPolares(int xc, int yc, int radio, QPainter *canvas)
{
    canvas->setPen(QColor(255,0,0));
    float dth, cdth, sdth, x, y, xt;

    dth = 1.0f / radio;
    cdth = cos(dth);
    sdth = sin(dth);

    x = 0;
    y = radio;

    while(y >= x){
        canvas->drawPoint((round(xc + x)) , round((yc + y)));//1er cuadrante
        canvas->drawPoint((round(xc - x)) , round((yc + y)));//2do cuadrante
        canvas->drawPoint((round(xc - x)) , round((yc - y)));//3er cuadrante
        canvas->drawPoint((round(xc + x)) , round((yc - y)));//4to cuadrante
        xt = x;
        x = xt * cdth - y * sdth;
        y = y * cdth + xt * sdth;
    }
}

void graficos::circuloTres(int xc, int yc, int radio, QPainter *canvas)
{
    QPen pluma(QColor(0,0,255));
    int x, y;
    for (int grados  = 0; grados < 360 ; grados += 2) {
        x = xc + radio * cos(grados / 180.0 * M_PI);
        y = yc + radio * sin(grados / 180.0 * M_PI);
        canvas->drawPoint(x,y);

    }

}

void graficos::circuloBresenham(int xc, int yc, int radio, QPainter *canvas)
{
    int x = 0;
    int y = radio;
    int delta = 2 - 2 * radio;
    int error = 0;

    while(y >= 0){
        canvas->drawPoint(xc + x, yc + y);
        canvas->drawPoint(xc + x, yc - y);
        canvas->drawPoint(xc -x, yc + y);
        canvas->drawPoint(xc - x, yc - y);

        if(delta < 0 && error <= 0){
            ++x;
            delta += 2 * x +1;
            continue;
        }
        error  = 2 * (delta - x) - 1;
        if(delta > 0 && error > 0){
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x-y);
        --y;
    }
}

void graficos::circuloParametrico(int xc, int yc, int radio, QPainter *canvas)
{
            double anguloVariacion = qDegreesToRadians(0.0);
            int x = radio;
            int y = 0;
            while (anguloVariacion <= 2*M_PI) {
                canvas->drawPoint(x + xc, y + yc);
                anguloVariacion += qDegreesToRadians(1.0);
                double xd = radio * cos(anguloVariacion);
                x = (int)round(xd);
                double yd = radio * sin(anguloVariacion);
                y = (int) yd;
            }
}

void graficos::espiral1(QPainter *canvas, QColor color,float factor)
{
    int xc = canvas->window().width() / 2;
    int yc = canvas->window().height() / 2;
    int radio = 5;
    const double dos_pi = 6.28 ;//M_PI_2;

    canvas->setPen(color);

    int cont;
    double dth, cdth, sdth,x,y, x_tmp, xt, yt;
    //modificar el factor mediante valores del usuario
    dth = dos_pi/(factor * radio);
    cdth = cos(dth);
    sdth = sin(dth);
    x = 0.0;
    y = radio;
    cont = 0;
    xt = xc + x;
    yt = yc +y;
    do{
        x_tmp = x;
        x = x * cdth - y * sdth;
        y = y * cdth + x_tmp * sdth;
        if(x > 0)
            x += 0.5;
        else
            x -= 0.5;
        if(y > 0)
            y += 0.5;
        else
            y -= 0.5;

     //   canvas->drawPoint(round(xt),round(yt));
        lineaDDA(round(xt), round(yt), round(xc+x), round(yc+y), canvas);
        xt = xc + x;
        yt = yc + y;
        cont++;

    }while( cont < 300);
}

void graficos::espiral2(QPainter *canvas, QColor color,float teta,float factor)
{
    int xc = canvas->window().width() / 2;
    int yc = canvas->window().height() / 2;
    float radio = 1.0;
    canvas->setPen(color);
    double th, x, y, xt, yt;
    th = 0.0;
    x = radio * cos(th);
    y = radio * sin(th);
    xt = xc + x;
    yt = yc + y;
    while (radio < 250) {
        //modificar valores mediante el usuario
        th += teta;
        radio += factor;
        x = radio * cos(th);
        y = radio * sin(th);
        lineaDDA(round(xt), round(yt), round(xc+x), round(yc+y), canvas);

        xt = xc + x;
        yt = yc + y;
    }
}

