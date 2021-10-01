#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QtGui>
#include <QKeyEvent>
#include <QTimer>
#include "matrix.h"

#include "mapeo.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void paintEvent(QPaintEvent *evt);
    void keyPressEvent(QKeyEvent *evt);
    void asignaFigura();
   // void dibujarFigura();//NO SE UTILIZA, SE PUEDE DESHABILITAR

    void dibujarFiguraMapeada();
    void trasladar(int TX, int TY);
    void escalar(float SX, float SY);
    void escalarPuntoFijo(float sX, float sY, int pfx, int pfy);//punto fijo o punto pivote
    void rotar(float angulo);
    void rotarPuntoFijo(float angulo, double, double);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

private:
    Ui::Dialog *ui;

    QPainter *canvas;
    QColor color;
    QTimer *timer;
    QTimer *timer2;

    float Fig[4][3];   //FIGURA ORIGINAL
    float FigAux[4][3];  //PARA RESPALDAR LOS PUNTOS ORIGINALES

    int ancho;
    //int aumento;
    //PARA MOVER AL CENTRO DE LA FORMA
    int posX, posY;
    int tX,tY;
};
#endif // DIALOG_H
