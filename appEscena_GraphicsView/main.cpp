#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*CREAMOS LA ESCENA
    QGraphicsScene *escena = new QGraphicsScene();
    QGraphicsRectItem *rectangulo = new QGraphicsRectItem(0, 0, 50, 50);
    rectangulo->setRect(0,0, 100,100);
    escena->addItem(rectangulo);

    //Creamos la vista para poder visualizar los objetos
    QGraphicsView *vista = new QGraphicsView(escena);
    vista->resize(400,400);
    vista->show();*/

    //mostrando varios items 2D

    QGraphicsScene escenaS(QRect(-50, -50, 400, 200));
    QGraphicsRectItem *rectangulo = new QGraphicsRectItem(QRect(-50, -50, 200, 50));
    rectangulo->setPen(QPen(Qt::red, 3, Qt::DashDotLine));
    rectangulo->setBrush(Qt::gray);

    QGraphicsSimpleTextItem *texto = new QGraphicsSimpleTextItem("TEC LAGUNA");
    texto->setPos(0, 0);

    QGraphicsEllipseItem *elipse = new QGraphicsEllipseItem(QRect(170, 20, 100, 75));
    elipse->setPen(QPen(Qt::darkBlue));
    elipse->setBrush(Qt::blue);

    QGraphicsPolygonItem *poligono = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>()<< QPointF(10, 10)
                                                                                           << QPointF(0, 90)
                                                                                           << QPointF(40, 70)
                                                                                           << QPointF(80, 110)
                                                                                           << QPointF(70, 20)));

    QGraphicsPolygonItem *estrella = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>()<< QPointF(90, 100)
                                                                                           << QPointF(120, 10)
                                                                                           << QPointF(150, 100)
                                                                                           << QPointF(85, 40)
                                                                                           << QPointF(155, 40)));

    QGraphicsPolygonItem *arbol = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>()<< QPointF(80.2, 30.8)
                                                                                           << QPointF(80.2, 70.3)
                                                                                           << QPointF(30.4, 70.3)
                                                                                           << QPointF(60.8, 100.8)
                                                                                           << QPointF(40.1, 100.8)
                                                                                           << QPointF(70, 135)
                                                                                           << QPointF(50, 135)
                                                                                           << QPointF(80, 160)
                                                                                           << QPointF(60, 160)
                                                                                           << QPointF(100.9, 200.5)
                                                                                           << QPointF(150.2, 160)
                                                                                           << QPointF(130.6, 160)
                                                                                           << QPointF(160.7, 130.5)
                                                                                           << QPointF(140.4, 130.5)
                                                                                           << QPointF(170, 100.8)
                                                                                           << QPointF(140.9, 100.8)
                                                                                           << QPointF(180.4, 70.3)
                                                                                           << QPointF(130.5, 70.3)
                                                                                           << QPointF(130.5, 30.8)
                                                                                           << QPointF(80.2, 30.8)));

    QGraphicsPolygonItem *estrella2 = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>()<< QPointF(80, 190)
                                                                                           << QPointF(90, 210)
                                                                                           << QPointF(70, 220)
                                                                                           << QPointF(90., 220)
                                                                                           << QPointF(100, 240)
                                                                                           << QPointF(110, 220)
                                                                                           << QPointF(130, 220)
                                                                                           << QPointF(110, 210)
                                                                                           << QPointF(120, 190)
                                                                                           << QPointF(100, 200)
                                                                                           << QPointF(80, 190)));

   // poligono->setPen(QPen(Qt::darkGreen));
    //poligono->setBrush(Qt::green);
    //estrella->setPen(QPen(Qt::darkRed, 3, Qt::DotLine));
    //estrella->setBrush(Qt::red);
    arbol->setPen(QPen(Qt::darkGreen, 3, Qt::SolidLine));
    arbol->setBrush(Qt::green);
    escenaS.addItem(arbol);
    estrella2->setPen(QPen(Qt::darkYellow, 3, Qt::DotLine));
    estrella2->setBrush(Qt::yellow);
    escenaS.addItem(estrella2);

    arbol->setRotation(180);
    estrella2->setRotation(180);
    arbol->setX(200);
    arbol->setY(200);
    estrella2->setX(200);
    estrella2->setY(200);


    //escenaS.addItem(estrella);
    //escenaS.addItem(rectangulo);
    //escenaS.addItem(texto);
    //escenaS.addItem(elipse);
    //escenaS.addItem(poligono);

    QGraphicsView vistaStatic;
    vistaStatic.setScene(&escenaS);
    vistaStatic.show();
    vistaStatic.resize(220,280);

    return a.exec();
}
