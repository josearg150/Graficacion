#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtGui>
#include "mapeo.h"

//Macro
#define radianes(g)((double)(g) * M_PI / 180.0)

//Estructura para definir cada punto del cubo
struct Puntos3D
{
   int x, y, z;
   bool opcion; //0 moverse, 1: trazar linea
};


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    void asignarCubo();
    void proyeccionCubo();
    void dibujarCubo();
    void inicializaPuerto();

    void lineTo3D(int x, int y, int z, float alpha, float phi, int i);
    void moveTo3D(int x, int y, int z, float alpha, float phi, int i);

    void keyPressEvent(QKeyEvent *event);


private slots:
    void on_dial_sliderMoved(int position);

    void on_dial_2_valueChanged(int value);

private:
    Ui::Widget *ui;
    QPainter *canvas;
    QPointF points[16];

    Puntos3D *cubo;
    Mapeo mapeo;
    int L, M, ancho;
    float alpha, phi;
};
#endif // WIDGET_H
