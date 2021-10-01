#ifndef OBJETO2D_H
#define OBJETO2D_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

class Objeto2D : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Objeto2D(QObject *parent = nullptr);
    void keyPressEvent(QKeyEvent *evento);

private:
    QTransform *Traslacion;
    QTransform *Escalacion;
    QTransform *Rotacion;

    int Tx, Ty;
    double Sx, Sy, angulo;
    QTimer *timer, *timer2, *timer3;
    int contador;
public slots:
    void mover();
    void animacion();
    void rotacionPivote(double angulo,float ppx, float ppy);
    void animacion2();

};

#endif // OBJETO2D_H
