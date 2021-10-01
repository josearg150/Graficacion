#include "henon.h"

Henon::Henon()
{

}

void Henon::iniciar(QPainter *canvas)
{
   maxX = canvas->window().width();
   maxY = canvas->window().height();
   EscalaX = 1;
   EscalaY = 1;
   DespX = 0;
   DespY = 0;
   ExtranioConfinador(canvas);
}

void Henon::ExtranioConfinador(QPainter *canvas)
{
    int a, i, color, PosX, PosY;
    double Xant, Xnuevo, Yant, Ynuevo;

    Xant = Xnuevo = Yant = Ynuevo = 0;

    for( color = 1; color <= 15; color++)
        for(i = 1; i <= 0x02FF; i++){
            Xnuevo = Yant + 1 - (1.4 * Xant * Xant);
            Ynuevo = 0.3 * Xant;
            PosX = (Xnuevo * maxX / 3 * EscalaX ) + maxX /2 + DespX;
            PosY = (Ynuevo * maxY * EscalaY) + maxY / 2 + DespY;
            if( (PosX >= 0) && (PosX <= maxX) && (PosY >= 0) && (PosY <= maxY))
                  canvas->drawPoint(PosX, PosY);
            Yant = Ynuevo;
            Xant = Xnuevo;
        }
    canvas->drawText(10, 110, "Confinador de henon");


}
