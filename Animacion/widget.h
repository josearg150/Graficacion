#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include "mapeo.h"
#include "matrix.h"
#include <QTimer>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *evt);
    void asignaFigura();
    void dibujarFiguraMapeada();
    void rotacionPuntoPivote(float ang, float ppx, float ppy);
    void trasladar(int TX, int TY);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void rotarEstrella();
    void dibujarEsferas();
    void moverRegalos();
private:
    Ui::Widget *ui;

    QPainter *canvas;

    float fig[20][3];
    float figAux[20][3];
    float estrella[11][3];
    float estrellaAux[11][3];
    float regalo[5][3];
    int centroX, centroY;
    int ancho;
    QTimer *timer1;
     QTimer *timer2;
    int color;
    bool moverRegalo;
    int tX,tY;

};

#endif // WIDGET_H
