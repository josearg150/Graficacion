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
};

#endif // GRAFICOS_H
