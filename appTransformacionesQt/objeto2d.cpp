#include "objeto2d.h"
#include <math.h>

Objeto2D::Objeto2D(QObject *parent) : QObject(parent)
{
    Tx = Ty = 0;
    Sx = Sy = 1.0;
    angulo = 0.0;
    Traslacion = new QTransform();
    Escalacion = new QTransform();
    Rotacion = new QTransform();
    timer = new QTimer();
    timer2 = new QTimer();
    timer3 = new QTimer();
    contador = 0;
    connect(timer,SIGNAL(timeout()),this,SLOT(mover()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(animacion()));
    connect(timer3,SIGNAL(timeout()),this,SLOT(animacion2()));


}
//Traslacion 2D utilizando el metodo setPos
/*void Objeto2D::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key() == Qt::Key_Left)
        setPos(this->x()-10, y());
    if(evento->key() == Qt::Key_Right)
        setPos(this->x()+10, y());
    if(evento->key() == Qt::Key_Up)
        setPos(this->x(), y()-10);
    if(evento->key() == Qt::Key_Down)
        setPos(this->x(), y()+10);
}*/

void Objeto2D::keyPressEvent(QKeyEvent *evento)
{

    switch(evento->key()) {
    case Qt::Key_Space : timer->start(50);
        break;
    case Qt::Key_Q: timer->stop();
        break;
    case Qt::Key_Left: Tx -= 10;
        break;
    case Qt::Key_Right: Tx += 10;
        break;
    case Qt::Key_Up: Ty -= 10;
        break;
    case Qt::Key_Down: Ty += 10;
        break;
    case Qt::Key_G: timer2->start(100);
        break;
    case Qt::Key_B: timer2->stop();
        break;
    case Qt::Key_H: timer3->start(100);
        break;
    case Qt::Key_N: timer3->stop();
        break;

    }
   /* if(evento->key() == Qt::Key_Space)
        timer->start(50);
    if(evento->key() == Qt::Key_Q)
        timer->stop();
    //Traslacion
    if(evento->key() == Qt::Key_Left)
        Tx -= 10;
    if(evento->key() == Qt::Key_Right)
        Tx += 10;
    if(evento->key() == Qt::Key_Up)
        Ty -= 10;
    if(evento->key() == Qt::Key_Down)
        Ty += 10;*/

   //Traslacion->setMatrix(1, 0, 0,
                       //   0, 1, 0,
                        //  Tx, Ty, 1);
    //this->setTransform(*Traslacion);


    /*Escalacion
    if(evento->key() == Qt::Key_X)
        Sx += .1;
    if(evento->key() == Qt::Key_S)
        Sy += .1;
    if(evento->key() == Qt::Key_A)
        if(Sx >0.2)
            Sx -= .1;
    if(evento->key() == Qt::Key_Z)
        if(Sy > 0.2)
            Sy -= .1;


    //VAlidar el decremento en la escalacion

    Escalacion->setMatrix(Sx, 0,  0,
                          0 , Sy, 0,
                          0 , 0 , 1);
    //this->setTransform(*Escalacion);

    //this->setScale(Sx);

    //this->setTransform(*Traslacion * *Escalacion);

    //Rotacion
    if(evento->key() == Qt::Key_D)
        angulo -= 5.0;
    if(evento->key() == Qt::Key_C)
        angulo += 5.0;

    //this->setRotation(angulo);
    //No convertimos a radianes
    Rotacion->setMatrix(cos(angulo),  sin(angulo),  0,
                        -sin(angulo), cos(angulo),  0,
                        0,            0,            1);
    this->setTransform(*Rotacion);*/

     double radianes = angulo * M_PI / 180.0;
     Rotacion->setMatrix(cos(radianes),   sin(radianes), 0,
                        -sin(radianes),  cos(radianes), 0,
                        0,               0,             1);
    this->setTransform(*Rotacion);


                   //ppx                    ppy
    float ren20 = -25 * (cos(radianes)-1) + 25 * sin(radianes);
                   //ppy                   //ppx
    float ren21 = -25 * (cos(radianes)-1) -25 * sin(radianes);

    Rotacion->setMatrix(cos(radianes),  sin(radianes), 0,
                        -sin(radianes), cos(radianes), 0,
                        ren20,          ren21,         1);
    this->setTransform(*Rotacion);


}

void Objeto2D::mover()
{
    if(contador <= 30){
        Tx-=10;
        Traslacion->setMatrix(1, 0, 0,
                              0, 1, 0,
                              Tx, Ty, 1);
        this->setTransform(*Traslacion);
    }else if(contador > 30 && contador <= 60){
        Tx+=10;
        Traslacion->setMatrix(1, 0, 0,
                              0, 1, 0,
                              Tx, Ty, 1);
        this->setTransform(*Traslacion);
    }

    if(contador == 61)
        contador = 0;

    contador++;

}

void Objeto2D::animacion()
{
    static int angulo = 0;
    static int cont = 0;
    if(cont <= 8){
        angulo = 45;
        if(cont == 8){
            angulo = 0;
            cont = 0;
        }
        double ppx =25;
        double ppy =25;
        rotacionPivote(angulo, ppx, ppy);
        cont++;
    }

}

void Objeto2D::rotacionPivote(double angulo, float ppx, float ppy)
{
    double radianes = angulo * M_PI / 180.0;
                   //ppx                    ppy
    float ren20 = -ppx * (cos(radianes)-1) + ppy * sin(radianes);
                   //ppy                   //ppx
    float ren21 = -ppy * (cos(radianes)-1) -ppx * sin(radianes);

    Rotacion->setMatrix(cos(radianes),  sin(radianes), 0,
                        -sin(radianes), cos(radianes), 0,
                        ren20,          ren21,         1);
    this->setTransform(*Rotacion);
}

void Objeto2D::animacion2()
{
    static bool dir = true;
    //angulo es positivo la rotacion es en sentido anti horario
    //si es negativo es en sentido horario
    static int angulo = 0;
    static int cont = 0;
    if(cont <= 9 && dir == true){
        angulo = 45;
        double pfx = 0;
        double pfy = 50;
        rotacionPivote(angulo, pfx, pfy);
        cont++;
        if(cont == 9){
            angulo = 0;
            cont = 0;
            dir = false;
        }
    }
    if(!dir){
        angulo = -45;
        double pfx = 0;
        double pfy = 50;
        rotacionPivote(angulo, pfx, pfy);
        cont++;
        if(cont == 9){
            angulo = 0;
            cont = 0;
            dir = true;
        }
}
}




