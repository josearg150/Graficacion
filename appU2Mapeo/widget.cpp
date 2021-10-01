#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    dibujarOrientacionNormal = dibujoMapeado = false;
    aumento = 0;
    ui->pushButton->setDisabled(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    canvas = new QPainter(this);
   /* if(dibujarOrientacionNormal)
        dibujarFigura();
      else if(dibujoMapeado) */
        dibujarFiguraMapeada();

    canvas->end();
}

void Widget::asignarFigura()
{   //    X              Y           H
    ancho = this->size().width() - ui->widget->size().width();
   
   /* fig[0][0] = 10; fig[0][1]=10; fig[0][2]= 1;
    fig[1][0] = 30; fig[1][1]=10; fig[1][2]= 1;
    fig[2][0] = 10; fig[2][1]=30; fig[2][2]= 1;
    //SOLO SI SE REQUIERE EN EL METODO DE DIBUJO AGREGAMOS EL PUNTO DE CIERRE DEL MISMO
    fig[3][0] = 10; fig[3][1]=10; fig[3][2]= 1;*/

    fig[0][0] = 0; fig[0][1]= 0; fig[0][2]= 1;
    fig[1][0] = 22; fig[1][1]=0; fig[1][2]= 1;
    fig[2][0] = 0; fig[2][1]=28; fig[2][2]= 1;
    //SOLO SI SE REQUIERE EN EL METODO DE DIBUJO AGREGAMOS EL PUNTO DE CIERRE DEL MISMO
    fig[3][0] = 0; fig[3][1]= 0; fig[3][2]= 1;

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
    for(int i = 0; i < 3; i++)
        canvas->drawLine(centroX+int(fig[i][0]), centroY+fig[i][1],centroX+fig[i+1][0],centroY+fig[i+1][1]);
       //ENVIAMOS AL ORIGEN DE LA PANTALLA EL TRIANGULO
       // canvas->drawLine(int(fig[i][0]),fig[i][1],fig[i+1][0],fig[i+1][1]);

}

void Widget::dibujarFiguraMapeada()
{
    //LINEA HORIZONTAL
    //canvas->drawLine(0,this->size().height()/2,ancho, size().height()/2);

    //LINEA VERTICAL
    //canvas->drawLine(ancho/2,0,ancho/2,size().height());

    Mapeo dibujo;
//CENTRO DE LA FORMA

    //Mundo real se usara una hoja de maquina

    dibujo.ventana(0, 0, 22,28);
        //M = Y + YPVmin

    //Valores originales
    //dibujo.puerto(150,100,350,400);
    //canvas->drawRect(150, 100, 200, 300);
    //x1 y y1 son la esquina superior izquierda y x2 y y2 son la esquina inferior derecha
                    //x1          y1            x2          y2
    dibujo.puerto(150 - aumento,100 - aumento,350 + aumento,400 + aumento);
    canvas->drawRect(150 - aumento,100 - aumento,200 + aumento * 2, 300 + aumento * 2);



              //XPVMIN ofrece un factor de traslación
  //  canvas->drawRect(0,0,ancho/2, size().height());
   //dibujo.puerto(0, 0, ancho/2, size().height()/2);



    //dibujo.puerto(0, 0, ancho, size().height()/2);

    int L = 0;
    //int L = centroX; //centro forma
    //int M = centroY;
    int M = 500;



    canvas->setPen(QColor(0,0,255));

    int x1, y1, x2,y2;
                                    //EL METODO RECIBE LA REFERENCIA DE LA VARIABLE x1
                                    //EL METODO RECIBE LA DIRECCION Y LA MANEJA COMO UN PUNTERO DE LA VARIABLE y1
    dibujo.mapear(int(fig[0][0]),int(fig[0][1]), x1,&y1,L,M,ui->label_2,ui->label_3);
    dibujo.mapear(fig[2][0],fig[2][1], x2,&y2,L,M,ui->label_2,ui->label_3);

    canvas->drawLine(x1,y1,x2,y2);

    for(int i=0; i < 2; i++)
    {
        dibujo.mapear(fig[i][0],fig[i][1], x1,&y1,L,M,ui->label_2,ui->label_3);
        dibujo.mapear(fig[i+1][0],fig[i+1][1], x2,&y2,L,M,ui->label_2,ui->label_3);
        canvas->drawLine(x1,y1,x2,y2);
    }
}
void Widget::on_pushButton_clicked()
{
   asignarFigura();
   dibujarOrientacionNormal = true;
   dibujoMapeado = false;
   repaint();
}

void Widget::on_pushButton_2_clicked()
{
    asignarFigura();
    dibujarOrientacionNormal =false;
    dibujoMapeado = true;
    repaint();

}











//ESQUINA SUPERIOR IZQ.
// canvas->drawLine(int(fig[i][0]), fig[i][1],fig[i+1][0],fig[i+1][1]);


/*
  //CENTRO DE LA FORMA
    //dibujo.ventana(ancho/2, 0, ancho, size().height()/2);
    dibujo.ventana(0, 0, ancho, size().height());
    //dibujo.puerto(ancho/2, 0, ancho, size().height()/2);
       //DIBUJA A LA IZQ. EN LO QUE ANTES ERA EL 2do. CUADRANTE
    // dibujo.puerto(0, 0, ancho/2, size().height()/2);
            //DIBUJA FUERA DE LA PANTALLA,
          //ó SE ASIGNA  L=0 ó   XPVmin = 0, uno U OTRO, POR LA TRASLACION QUE SE HACE
    int L = 0;//centroX; //centro forma
    int M = centroY;
*/

//TODA LA FORMA, ESQ. INFERIOR DERECHA
//dibujo.ventana(0, 0, ancho, size().height());
//dibujo.puerto(0, 0, ancho, size().height());

//int L = 0;//centroX; //centro forma
//int M = size().height();//centroY;



//VENTANA DE 10 X 10
//dibujo.ventana(0,0,10,10);
//dibujo.puerto(0, 0, ancho/2, size().height()/2);

void Widget::on_pushButton_3_clicked()
{
  aumento += 25;
  on_pushButton_2_clicked();
}

void Widget::on_pushButton_4_clicked()
{
    aumento+= -25;
    on_pushButton_2_clicked();
}

