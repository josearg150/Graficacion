#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QTimer>
#include "graficos.h"
#include <henon.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void dragon(int limite); //limite para controlar el ciclo for

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    QTimer *timer;
    QPainter *canvas;
    graficos *graf;
    Henon *henon;

    void paintEvent(QPaintEvent *event);// override(;
    void generarDragon(QPainter *canvas);
  //  void lineaDDA(int x1, int y1, int x2, int y2, QPainter *canvas);


    int EjeX[4098], EjeY[4098], paso, signo;

    int limiteInf, limiteSup;
    bool band;
};
#endif // WIDGET_H
