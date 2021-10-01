#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    asignarFigura();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::PainEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    canvas = new QPainter(this);
    dibujarFiguraMapeada();
    canvas->end();
}

void Dialog::asignarFigura()
{
    ancho = this->size().width() - ui->widget->size().width();
         //    X              Y           H
    fig[0][0] = 10; fig[0][1]=10; fig[0][2]= 1;
    fig[1][0] = 30; fig[1][1]=10; fig[1][2]= 1;
    fig[2][0] = 10; fig[2][1]=30; fig[2][2]= 1;
    //SOLO SI SE REQUIERE EN EL METODO DE DIBUJO AGREGAMOS EL PUNTO DE CIERRE DEL MISMO
    fig[3][0] = 10; fig[3][1]=10; fig[3][2]= 1;

    //RESPALDAR LOS VALORES DEL POLIGONO
               //AQUI NO SE REQUIERE EL ULTIMO PUNTO
    for (int r = 0; r < 3; r ++)
    {
        for (int c = 0;c < 3;c++) {
            figAux[r][c] = fig[r][c];
        }

    }
    centroX = ancho/2;
    centroY = this->size().height()/2;
    tx = ty = 0;
}

void Dialog::dibujarFiguraMapeada()
{

    canvas->drawLine(0, size().height() / 2,ancho, size().height() / 2);

    canvas->drawLine(ancho / 2, 0, ancho / 2, size().height());

    //OBJETO DINAMICO SE REQUIERE USAR FLECHA
    Mapeo *mapeo = new Mapeo();
    mapeo->ventana((size().width() - ancho) / 2, 0, size().width() -ancho, size().height() / 2);
    mapeo->puerto((size().width() - ancho) / 2, 0, size().width() -ancho, size().height() / 2);
    int L = centroX;
    int M = centroY;

    canvas->setPen(QColor(0,0,0));
    int x1, y1, x2, y2;
    mapeo->mapear(fig[0][0], fig[0][1], x1, &y1, L, M);
    mapeo->mapear(fig[2][0], fig[2][1], x2, &y2, L, M);
    canvas->drawLine(x1, y1, x2, y2);
    for (int i = 0; i < 2 ; i++) {
        mapeo->mapear(fig[i][0],fig[i][1], x1,&y1,L,M);
        mapeo->mapear(fig[i+1][0],fig[i+1][1], x2,&y2,L,M);
        canvas->drawLine(x1, y1, x2, y2);
    }
}

void Dialog::trasladar(int TX, int TY)
{
    Matrix figm, id, fres;
    figm.Inicializa(4,3);
    fres.Inicializa(4,3);
    id.Inicializa(3, 3);

    //ASIGNAR LOS PUNTOS DEL OBJETO
    for (int i = 0; i < figm.numRen(); i++)
        for (int j = 0; j < figm.numCol(); j++)
            figm.SET(i, j,fig[i][j]);

    //APlicar traslacion
    fres.traslacion(figm, id, TX, TY);
    //Asigna los nuevos valores a la figura
    for (int i= 0; i < fres.numRen();i++)
        for (int j = 0; j < fres.numCol(); j++)
             fig[i][j] = fres.GET(i,j);

    repaint();
}

