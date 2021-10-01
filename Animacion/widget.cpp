#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    asignaFigura();

    timer1 = new QTimer();
    connect(timer1, SIGNAL(timeout()), this, SLOT(rotarEstrella()));
    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(moverRegalos()));
    color = 1;
    moverRegalo = false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    canvas = new QPainter(this);
    dibujarFiguraMapeada();

    canvas->end();

}

void Widget::asignaFigura()
{

    //Arbol
    fig[0][0] = 8.2;   fig[0][1]= 3.8;   fig[0][2]= 1;//Base
    fig[1][0] = 8.2;   fig[1][1]= 7.3;   fig[1][2]= 1;//Base
    fig[2][0] = 3.4;   fig[2][1]= 7.3;   fig[2][2]= 1;//Pico 1
    fig[3][0] = 6.8;   fig[3][1]= 10.8;  fig[3][2]= 1;//Pico 2
    fig[4][0] = 4.1;   fig[4][1]= 10.8;  fig[4][2]= 1;//Pico 2
    fig[5][0] = 7;     fig[5][1]= 13.5;  fig[5][2]= 1;//Pico 3
    fig[6][0] = 5;     fig[6][1]= 13.5;  fig[6][2]= 1;//Pico 3
    fig[7][0] = 8;     fig[7][1]= 16;    fig[7][2]= 1;//pico 4
    fig[8][0] = 6;     fig[8][1]= 16;    fig[8][2]= 1;//Pico 4
    fig[9][0] = 10.9;  fig[9][1]= 20.5;  fig[9][2]= 1;//Pico 4
    fig[10][0] = 15.2; fig[10][1]= 16;   fig[10][2]= 1;//Pico 4
    fig[11][0] = 13.6; fig[11][1]= 16;   fig[11][2]= 1;//Pico 3
    fig[12][0] = 16.7; fig[12][1]= 13.5; fig[12][2]= 1;//Pico 3
    fig[13][0] = 14.4; fig[13][1]= 13.5; fig[13][2]= 1;//Pico 3
    fig[14][0] = 17;   fig[14][1]= 10.8; fig[14][2]= 1;//Pico 2
    fig[15][0] = 14.9; fig[15][1]= 10.8; fig[15][2]= 1;//Pico 2
    fig[16][0] = 18.4; fig[16][1]= 7.3;  fig[16][2]= 1;//Pico 1
    fig[17][0] = 13.5; fig[17][1]= 7.3;  fig[17][2]= 1;//Base
    fig[18][0] = 13.5; fig[18][1]= 3.8;  fig[18][2]= 1;//Base
    fig[19][0] = 8.2;  fig[19][1]= 3.8;  fig[19][2]= 1;


    estrella[0][0] = 8; estrella[0][1] = 19; estrella[0][2] = 1;
    estrella[1][0] = 9; estrella[1][1] = 21; estrella[1][2] = 1;
    estrella[2][0] = 7; estrella[2][1] = 22; estrella[2][2] = 1;
    estrella[3][0] = 9; estrella[3][1] = 22; estrella[3][2] = 1;
    estrella[4][0] = 10; estrella[4][1] = 24; estrella[4][2] = 1;
    estrella[5][0] = 11; estrella[5][1] = 22; estrella[5][2] = 1;
    estrella[6][0] = 13; estrella[6][1] = 22; estrella[6][2] = 1;
    estrella[7][0] = 11; estrella[7][1] = 21; estrella[7][2] = 1;
    estrella[8][0] = 12; estrella[8][1] = 19; estrella[8][2] = 1;
    estrella[9][0] = 10; estrella[9][1] = 20; estrella[9][2] = 1;
    estrella[10][0] = 8; estrella[10][1] = 19; estrella[10][2] = 1;

    regalo[0][0] = 14; regalo[0][1] = 3; regalo[0][2] = 1;
    regalo[1][0] = 14; regalo[1][1] = 5; regalo[1][2] = 1;
    regalo[2][0] = 16; regalo[2][1] = 5; regalo[2][2] = 1;
    regalo[3][0] = 16; regalo[3][1] = 3; regalo[3][2] = 1;
    regalo[4][0] = 14; regalo[4][1] = 3; regalo[4][2] = 1;

    tX = tY = 0;

    /*
    for (int r = 0; r < 18; r ++)
    {
        for (int c = 0;c < 3;c++) {
            figAux[r][c] = fig[r][c];
        }

    }
    */

    centroX = this->size().width()/2;
    centroY = this->size().height()/2;

}

void Widget::dibujarFiguraMapeada()
{

    Mapeo dibujo;
    //Mundo real se usara una hoja de maquina

    dibujo.ventana(0, 0, 22,28);
    dibujo.puerto(50, 0, 450, 500);
    //canvas->drawRect(150,100,200, 300);

    int L = 150;
    int M = 500;

    QPen pluma;
    pluma.setWidth(3);

    canvas->setPen(pluma);

    int x1, y1, x2,y2;


    for(int i=0; i < 19; i++)
    {
        if(i == 0 || i == 17 || i == 18){
            pluma.setColor(QColor(128,64,0));
            canvas->setPen(pluma);
        }
        else{
            pluma.setColor(QColor(0,255,0));
            canvas->setPen(pluma);
        }

        dibujo.mapear(fig[i][0],fig[i][1], x1,y1,L,M);
        dibujo.mapear(fig[i+1][0],fig[i+1][1], x2,y2,L,M);
        canvas->drawLine(x1,y1,x2,y2);
    }
    pluma.setColor(QColor(0,255,0));
    canvas->setPen(pluma);
    canvas->drawLine(345,375,435,375);


    pluma.setColor(QColor(255,255,0));
    canvas->setPen(pluma);
    for(int i=0; i < 10; i++)
    {
        dibujo.mapear(estrella[i][0], estrella[i][1], x1,y1,L,M);
        dibujo.mapear(estrella[i+1][0],estrella[i+1][1], x2,y2,L,M);
        canvas->drawLine(x1,y1,x2,y2);
    }

    pluma.setColor(QColor(255,0,0));
    canvas->setPen(pluma);

    for(int i=0; i < 4; i++)
    {
        dibujo.mapear(regalo[i][0], regalo[i][1], x1,y1,L,M);
        dibujo.mapear(regalo[i+1][0],regalo[i+1][1], x2,y2,L,M);
        canvas->drawLine(x1,y1,x2,y2);
    }
    dibujarEsferas();
}

void Widget::dibujarEsferas()
{
    QPen pluma;
    pluma.setWidth(3);


    if(color == 1)
        pluma.setColor(QColor(255,0,0));
    else
        pluma.setColor(QColor(0,0,255));

    canvas->setPen(pluma);

    //Linea 1 de esferas
    canvas->drawEllipse(410,165,10,10);
    canvas->drawEllipse(390,185,10,10);
    canvas->drawEllipse(370,205,10,10);
    canvas->drawEllipse(350,225,10,10);
    canvas->drawEllipse(330,245,10,10);
    canvas->drawEllipse(315,260,10,10);
    //Linea 2 de esferas
    canvas->drawEllipse(450,230,10,10);
    canvas->drawEllipse(420,255,10,10);
    canvas->drawEllipse(390,280,10,10);
    canvas->drawEllipse(360,305,10,10);
    canvas->drawEllipse(330,330,10,10);
    canvas->drawEllipse(300,355,10,10);
    //Linea 3 de esferas
    canvas->drawEllipse(475,290,10,10);
    canvas->drawEllipse(455,310,10,10);
    canvas->drawEllipse(435,330,10,10);
    canvas->drawEllipse(415,350,10,10);
    canvas->drawEllipse(395,370,10,10);

    color *= -1;
}

void Widget::moverRegalos()
{
    float izq = 0.3;
    for(int i = 0; i < 10; i++){
     trasladar(tX - izq,0);
     izq += 0.3;

    }

    float der = 0.3;
    for(int i = 0; i < 10; i++){
     trasladar(tX + der,0);
     der += 0.3;
    }
}



void Widget::rotarEstrella()
{
    static int angulo = 0;
    static int cont = 0;
    if(cont <= 4){
        angulo = 90;
        if(cont == 4){
            angulo = 0;
            cont = 0;
        }
        double pfx =10;
        double pfy =21;
        rotacionPuntoPivote(angulo, pfx, pfy);
        cont++;
    }
}

void Widget::rotacionPuntoPivote(float ang, float ppx, float ppy)
{
    Matrix figM, id, figres;
    figM.Inicializa(11,3);
    id.Inicializa(3,3);
    figres.Inicializa(11,3);

    for(int i=0; i<figM.numRen(); i++)
        for(int j=0; j< figM.numCol(); j++)
            figM.SETM(i,j,estrella[i][j]);

    //Fig. Resultante es decir figura transformada
    figres.rotacionPuntoPivote(figM, id, ang, ppx, ppy);

    //ASIGNA LOS NUEVOS VALORES A FIGURA
    for(int i=0;i<figres.numRen();i++)
       for(int j=0;j<figres.numCol();j++)
           estrella[i][j]=figres.GETM(i,j);
    repaint();
}

void Widget::trasladar(int TX, int TY)
{
    Matrix fig,id,fres;  //OBJETOS ESTATICOS
    fig.Inicializa(5,3);

    fres.Inicializa(5,3);

    id.Inicializa(3,3);
    //ASIGNAR PUNTOS
    for(int i=0;i<fig.numRen();i++)
       for(int j=0;j<fig.numCol();j++)
           fig.SETM(i,j,regalo[i][j]);
    //APLICAR LA TRASLACION
    fres.traslacion(fig,id,TX,TY);    //tX,tY);
    //ASIGNA LOS NUEVOS VALORES A FIGURA
    for(int i=0;i<fres.numRen();i++)
       for(int j=0;j<fres.numCol();j++)
           regalo[i][j]=fres.GETM(i,j);

    repaint();//INVOCA A paintEvent
}

void Widget::on_pushButton_clicked()
{
    asignaFigura();
    timer1->start(15);
    timer2->start(500);
    repaint();
}

void Widget::on_pushButton_2_clicked()
{
    timer1->stop();
    timer2->stop();
}
