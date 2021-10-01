#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    dibujarOrientacionNormal = dibujoMapeado = false;
    aumento = 0;
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

void Widget::asignarFigura()
{   //    X              Y           H
    ancho = this->size().width() - ui->widget->size().width();


    fig[0][0] = 8.2; fig[0][1]= 3.8; fig[0][2]= 1;//Base
    fig[1][0] = 8.2; fig[1][1]= 7.3; fig[1][2]= 1;//Base
    fig[2][0] = 3.4; fig[2][1]= 7.3; fig[2][2]= 1;//Pico 1
    fig[3][0] = 6.8; fig[3][1]= 10.8; fig[3][2]= 1;//Pico 2
    fig[4][0] = 4.1; fig[4][1]= 10.8; fig[4][2]= 1;//Pico 2
    fig[5][0] = 7; fig[5][1]= 13.5; fig[5][2]= 1;//Pico 3
    fig[6][0] = 5; fig[6][1]= 13.5; fig[6][2]= 1;//Pico 3
    fig[7][0] = 8; fig[7][1]= 16; fig[7][2]= 1;//pico 4
    fig[8][0] = 6; fig[8][1]= 16; fig[8][2]= 1;//Pico 4
    fig[9][0] = 10.9; fig[9][1]= 20.5; fig[9][2]= 1;//Pico 4
    fig[10][0] = 15.2; fig[10][1]= 16; fig[10][2]= 1;//Pico 4
    fig[11][0] = 13.6; fig[11][1]= 16; fig[11][2]= 1;//Pico 3
    fig[12][0] = 16.7; fig[12][1]= 13.5; fig[12][2]= 1;//Pico 3
    fig[13][0] = 14.4; fig[13][1]= 13.5; fig[13][2]= 1;//Pico 3
    fig[14][0] = 17; fig[14][1]= 10.8; fig[14][2]= 1;//Pico 2
    fig[15][0] = 14.9; fig[15][1]= 10.8; fig[15][2]= 1;//Pico 2
    fig[16][0] = 18.4; fig[16][1]= 7.3; fig[16][2]= 1;//Pico 1
    fig[17][0] = 13.5; fig[17][1]= 7.3; fig[3][2]= 1;//Base
    fig[18][0] = 13.5; fig[18][1]= 3.8; fig[18][2]= 1;//Base
    //fig[19][0] = 13.5; fig[19][1]= 3.8; fig[18][2]= 1;

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

}

void Widget::dibujarFigura()
{
    //DIBUJAR EJE COORDENADO
    //LINEA HORIZONTAL
    //canvas->drawLine(0,this->size().height()/2,ancho, size().height()/2);

    //LINEA VERTICAL
    //canvas->drawLine(ancho/2,0,ancho/2,size().height());

    //DIBUJAR POLIGONO
    //for(int i = 0; i < 3; i++)
      //  canvas->drawLine(centroX+int(fig[i][0]), centroY+fig[i][1],centroX+fig[i+1][0],centroY+fig[i+1][1]);
       //ENVIAMOS AL ORIGEN DE LA PANTALLA EL TRIANGULO
       // canvas->drawLine(int(fig[i][0]),fig[i][1],fig[i+1][0],fig[i+1][1]);

}

void Widget::dibujarFiguraMapeada()
{

    Mapeo dibujo;
    //Mundo real se usara una hoja de maquina

    dibujo.ventana(0, 0, 21.6,27.3);
    dibujo.puerto(150 - aumento,100 - aumento,350 + aumento,400 + aumento);
    canvas->drawRect(150 - aumento,100 - aumento,200 + aumento * 2, 300 + aumento * 2);

    int L = 0;
    int M = 500;

    canvas->setPen(QColor(0,0,0));

    int x1, y1, x2,y2;


    for(int i=0; i < 18; i++)
    {
        if(i == 0 || i == 17 || i == 18)
            canvas->setPen(QColor(128,64,0));
        else
            canvas->setPen(QColor(0,255,0));

        dibujo.mapear(fig[i][0],fig[i][1], x1,&y1,L,M,ui->label_2,ui->label_3);
        dibujo.mapear(fig[i+1][0],fig[i+1][1], x2,&y2,L,M,ui->label_2,ui->label_3);
        canvas->drawLine(x1,y1,x2,y2);
    }

}
void Widget::on_pushButton_clicked()
{
   /*asignarFigura();
   dibujarOrientacionNormal = true;
   dibujoMapeado = false;
   repaint();*/
}

void Widget::on_pushButton_2_clicked()
{
    asignarFigura();
    dibujarOrientacionNormal =false;
    dibujoMapeado = true;
    repaint();

}

void Widget::on_pushButton_3_clicked()
{
  aumento += 25;
  on_pushButton_2_clicked();
}

void Widget::on_pushButton_4_clicked()
{
    if(aumento > -75){
         aumento+= -25;
         on_pushButton_2_clicked();
    }
}

