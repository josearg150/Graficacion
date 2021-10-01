#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    alpha = 63.4f;
    phi = 30.0f;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    inicializaPuerto();
    proyeccionCubo();

}

void Widget::asignarCubo()
{
    Puntos3D cuboBase[] = {{100,50,0,0},{200,50,0,1},{200,150,0,1},
                           {100,150,0,1},{100,50,0,1},{100,50,100,1},
                           {200,50,100,1},{200,150,100,1},{200,150,0,1},
                           {200,50,0,0},{200,50,100,1},{100,50,100,0},
                           {100,150,100,1},{100,150,0,1},{100,150,100,0},
                           {200,150,100,1}};

    cubo = new Puntos3D[16];
    for (int i = 0 ; i < 16; i++)
        cubo[i] = cuboBase[i];
    inicializaPuerto();

    ancho = this->size().width() - ui->widget->size().width();
}

void Widget::proyeccionCubo()
{
    canvas = new QPainter(this);
    canvas->setPen(QPen(Qt::black,3));

    //EJE X
    canvas->drawLine(0, size().height()-1, ancho, size().height());
    //EJE Y
    canvas->drawLine(1, 0, 1,size().height());
    //EJE Z
    int zx1 = 0;
    int zy1 = 0;

    int zx2 = ancho * cos(qDegreesToRadians(phi));//(radianes(phi));
    int zy2 = ancho * sin(qDegreesToRadians(phi));//(radianes(phi));

    //Mapear los valores de Z
    int x1, y1, x2, y2;
    mapeo.mapear(zx1, zy1, x1, y1, L, M);
    mapeo.mapear(zx2, zy2, x2, y2, L, M);
    //YA esta proyectado y mapeado
    //Dibujar eje Z
    canvas->drawLine(x1, y1, x2, y2);

    //Proyectar el cubo
    for (int i = 0; i < 16; ++i) {
        if(cubo[i].opcion)
            lineTo3D(cubo[i].x, cubo[i].y, cubo[i].z, radianes(alpha), qDegreesToRadians(phi), i);
        else
            moveTo3D(cubo[i].x, cubo[i].y, cubo[i].z, radianes(alpha), qDegreesToRadians(phi), i);
    }

    canvas->setPen(QPen(QColor(255,100,0),3));
    dibujarCubo();
    canvas->end();
}

void Widget::dibujarCubo()
{
    for(int i=0; i < 15; i++){
        canvas->drawLine(points[i].x(),points[i].y(),points[i+1].x(),points[i+1].y());
    }
}

void Widget::inicializaPuerto()
{
    mapeo.ventana(0, 0, size().width() - ancho, size().height());
    mapeo.puerto(0, 0, size().width() - ancho, size().height());
    L = 0;
    M = size().height();
}
//Obtener los puntos proyectados xp, yp
//Xp = X + L * Cos(phi)
//Yp = Y + L * Sin(phi)
// L = Z / Tan(phi)
void Widget::lineTo3D(int x, int y, int z, float alpha, float phi, int i)
{
    int xp, yp, longitud;
    float tanalpha;
    if((tanalpha = tan(alpha) != 0))
        longitud = (int)(z/tanalpha);
    else{
        longitud = 0;
    }
    xp = x + longitud * cos(phi);
    yp = y + longitud * sin(phi);

    int x1, y1;
    mapeo.mapear(xp, yp, x1, y1, L, M);
    points[i].setX(x1);
    points[i].setY(y1);
}

void Widget::moveTo3D(int x, int y, int z, float alpha, float phi, int i)
{
    int xp, yp, longitud;
    float tanalpha;
    if((tanalpha = tan(alpha) != 0))
        longitud = (int)(z/tanalpha);
    else{
        longitud = 0;
    }
    xp = x + longitud * cos(phi);
    yp = y + longitud * sin(phi);

    int x1, y1;
    mapeo.mapear(xp, yp, x1, y1, L, M);
    points[i].setX(x1);
    points[i].setY(y1);
}

void Widget::keyPressEvent(QKeyEvent *event)
{

}


void Widget::on_dial_sliderMoved(int position)
{
    phi = position;
    inicializaPuerto();
    repaint();
}

void Widget::on_dial_2_valueChanged(int value)
{

    alpha = ui->dial->value();
    inicializaPuerto();
    update();

}
