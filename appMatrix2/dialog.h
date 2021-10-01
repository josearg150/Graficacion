#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include "mapeo.h"
#include "matrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void PainEvent(QPaintEvent *event);
    void asignarFigura();
    void dibujarFiguraMapeada();

    void trasladar(int TX, int TY);

private:
    Ui::Dialog *ui;
    QPainter *canvas;
    float fig[4][3];
    float figAux[4][3];
    int ancho;
    int centroX, centroY;

    int tx, ty;

};
#endif // DIALOG_H
