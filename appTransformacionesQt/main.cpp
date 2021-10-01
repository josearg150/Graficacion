#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
//#include <QGraphicsRectItem>
#include "objeto2d.h"
#include <QGraphicsPolygonItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *escena = new QGraphicsScene();
    Objeto2D *rectangulo = new Objeto2D();
    rectangulo->setRect(0, 0, 50, 50);
    rectangulo->setFlag(QGraphicsRectItem::ItemIsFocusable);
    rectangulo->setFocus();



    escena->addItem(rectangulo);




   // poligono->setPen(QPen(Qt::darkGreen));
    //poligono->setBrush(Qt::green);
    //estrella->setPen(QPen(Qt::darkRed, 3, Qt::DotLine));
    //estrella->setBrush(Qt::red);



    QGraphicsView *vista = new QGraphicsView(escena);
    vista->resize(400, 400);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->show();



    return a.exec();

    //Aplicar el concepto del punto pivote

}
