#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

#include "mapeo.h"

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
    void asignarFigura();
    void dibujarFigura();
    void dibujarFiguraMapeada();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;

    QPainter *canvas;

    //INVESTIGAR Y DIBUJAR ALGUN OBJETO O ANIMAL, LIBRE

    float fig[20][3];
    float figAux[20][3];
    int aumento;
    int centroX, centroY;
    int ancho; //SE UTILIZARA PARA ESTABLECER EL AREA DE DIBUJO RESTANDO EL ANCHO DEL WIDGET(PANEL)

    bool dibujarOrientacionNormal;// Y hacia abajo
    bool dibujoMapeado;           // Y hacia arriba


};
#endif // WIDGET_H
