#ifndef GRAFICOS_H
#define GRAFICOS_H
#include <QPainter>
#include <QColor>


class graficos
{
public:
    graficos();
    //metodo inline
    int round(float n){//podemos usar qround
        return int(n+0.5f);
    }
    void lineaDDA(int x1, int y1, int x2, int y2, QPainter *canvas);
    void lineaDDA(int x1, int y1, int x2, int y2, QPainter *canvas, QColor color);
    void circuloPitagoras(int xc, int yc, int radio, QPainter *canvas);
    void circuloPolares(int xc, int yc, int radio, QPainter *canvas);
    void circuloTres(int xc, int yc, int radio, QPainter *canvas);
    void circuloBresenham(int xc, int yc, int radio, QPainter *canvas);
    void circuloParametrico(int xc, int yc, int radio, QPainter *canvas);
    void espiral1(QPainter *canvas, QColor color,float factor);
    void espiral2(QPainter *canvas, QColor color,float teta,float factor);
};

#endif // GRAFICOS_H
