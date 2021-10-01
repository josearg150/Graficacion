#ifndef HENON_H
#define HENON_H

#include <QPainter>
class Henon
{
public:
    Henon();
    void iniciar(QPainter *canvas);
private:
    int maxX, maxY;
    double EscalaX, EscalaY, DespX, DespY;
    QPainter *canvas;
    void ExtranioConfinador(QPainter *canvas);
};

#endif // HENON_H
