#include "dialog.h"
#include "ui_dialog.h"
#include <QColorDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    asignaFigura();
    setFocusPolicy(Qt::StrongFocus);
    color = QColor(0,0,0);
    //aumento = 0;
    timer = new QTimer();

    timer2 = new QTimer();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *evt)
{
    Q_UNUSED(evt)

    canvas = new QPainter(this);
    //dibujarFigura();
    dibujarFiguraMapeada();

    canvas->end();
}

void Dialog::keyPressEvent(QKeyEvent *evt)
{
    switch (evt->key()) {
    case(Qt::Key_Up):
        trasladar(0, tY + ui->spinBox_2->value() );
        break;
    case(Qt::Key_Down):
        trasladar(0,tY-ui->spinBox_2->value());
        break;
    case(Qt::Key_Left):
        trasladar(tX - ui->spinBox->value(),0);
        break;
    case(Qt::Key_Right):
        trasladar(tX + ui->spinBox->value(),0);
        break;
    }
}

void Dialog::asignaFigura()
{
    //UTILIZAMOS COORDENADAS HOMOGENEAS

    Fig[0][0]= 10; Fig[0][1]= 10; Fig[0][2]= 1;
    Fig[1][0]= 30; Fig[1][1]= 10; Fig[1][2]= 1;
    Fig[2][0]= 20; Fig[2][1]= 30; Fig[2][2]= 1;
//ES EL MISMO PUNTO DE INICIO
    Fig[3][0]= 10; Fig[3][1]= 10; Fig[3][2]= 1;

    //RESPALDAR VALORES
    for(int i = 0; i< 4; i++)
      for(int j = 0; j < 3; j++)
         FigAux[i][j] = Fig[i][j];

    //ESTABLECER EL ORIGEN EN EL CENTRO DE LA FORMA
// WIDTH DE LA FORMA - EL WIDTH DEL WIDGET QUE SE UTILIZA COMO CONTENEDOR
    ancho = this->size().width() - ui->widget->size().width();
//CENTRO DE LA FORMA
    posX = ancho/2;  //size().width()/2;
    posY = this->size().height()/2;

//VARIABLES PARA CONTROLAR LA TRASLACION
    tX = tY = 0;

}

void Dialog::dibujarFiguraMapeada()
{

    //canvas->setRenderHint(QPainter::Antialiasing, true);
    //DIBUJAR EL EJE COORDENADO
    //LINEA HORIZONTAL
    canvas->drawLine(0,this->size().height()/2,ancho,size().height()/2);
    //LINEA VERTICAL
    canvas->drawLine(ancho/2,0,ancho/2,size().height());
//PARA EVALUACION
    //AGREGAR LINEA EN DIAGONAL EN EL PRIMER CUADRANTE

    //dibujar LINEA Y = X   QUE ES LA DIAGONAL

    //MAPEAR DEL MUNDO REAL A COORDENADAS DE DISPOSITIVO

       Mapeo mapeo;

       //PUERTO DE VISION COLOCADO EN EL CENTRO
       //TIENEN LA MISMA DIMENSION

  //  mapeo.ventana(0, 0, 22,28);
  //  mapeo.puerto(15 - aumento,10 - aumento,35 + aumento,40 + aumento);
    mapeo.ventana((size().width()-ancho)/2, 0, (size().width()-ancho),size().height()/2);
    mapeo.puerto((size().width()-ancho)/2, 0, (size().width()-ancho), size().height()/2 );
    int L = posX; //CENTRO_X
    int M = posY;  //CENTRO_Y

    int x1,y1,x2,y2;  //VARIABLES PARA ASIGNAR LAS POSICIONES MAPEADAS

    canvas->setPen(color);

                //  X         Y
    mapeo.mapear(Fig[0][0], Fig[0][1], x1, y1, L, M);
    mapeo.mapear(Fig[2][0], Fig[2][1], x2, y2, L, M);
    //PRIMERO DIBUJAR LA LINEA QUE CIERRA EL TRIANGULO     ????
    canvas->drawLine(x1,y1,x2,y2);
    //canvas->drawLine(posX+Fig[0][0],posY+Fig[0][1],posX+Fig[2][0],posY+Fig[2][1]);
    for(int i=0; i<2; i++)
    {
          //canvas->drawLine(posX+Fig[i][0],posY+Fig[i][1],posX+Fig[i+1][0],posY+Fig[i+1][1]);
        mapeo.mapear(Fig[i][0], Fig[i][1], x1, y1, L, M);
        mapeo.mapear(Fig[i+1][0], Fig[i+1][1], x2, y2, L, M);
        canvas->drawLine(x1,y1,x2,y2);
    }

}

void Dialog::trasladar(int TX, int TY)
{
    Matrix fig,id,fres;  //OBJETOS ESTATICOS
    fig.Inicializa(4,3);

    fres.Inicializa(4,3);

    id.Inicializa(3,3);
    //ASIGNAR PUNTOS
    for(int i=0;i<fig.numRen();i++)
       for(int j=0;j<fig.numCol();j++)
           fig.SETM(i,j,Fig[i][j]);
    //APLICAR LA TRASLACION
    fres.traslacion(fig,id,TX,TY);    //tX,tY);
    //ASIGNA LOS NUEVOS VALORES A FIGURA
    for(int i=0;i<fres.numRen();i++)
       for(int j=0;j<fres.numCol();j++)
           Fig[i][j]=fres.GETM(i,j);

    repaint();//INVOCA A paintEvent
}

void Dialog::escalar(float SX, float SY)
{
    Matrix fig, id, figres;
    fig.Inicializa(4, 3);
    id.Inicializa(3, 3);
    figres.Inicializa(4, 3);

    for (int i = 0; i < fig.numRen(); i++)
        for (int j = 0; j < fig.numCol(); j++)
            fig.SETM(i, j, Fig[i][j]);
    fig.escalacion(fig, id, SX, SY);

    //ASIGNAR PUNTOS
    for(int i=0;i<figres.numRen();i++)
       for(int j=0;j<figres.numCol();j++)
           figres.SETM(i,j,Fig[i][j]);

    //APLICAR LA TRASLACION
    figres.traslacion(fig,id,SX,SY);

    //ASIGNA LOS NUEVOS VALORES A FIGURA
    for(int i=0;i<figres.numRen();i++)
       for(int j=0;j<figres.numCol();j++)
           Fig[i][j]=figres.GETM(i,j);

    repaint();//INVOCA A paintEvent

}

void Dialog::escalarPuntoFijo(float sX, float sY, int pfx, int pfy)
{
    Matrix fig, id, figres;
    fig.Inicializa(4, 3);
    figres.Inicializa(4, 3);
    id.Inicializa(3, 3);


    for (int i = 0; i < fig.numRen(); i++)
        for (int j = 0; j < fig.numCol(); j++)
            fig.SETM(i, j, Fig[i][j]);

    //Figura resultante, es decir transformada
    figres.escalacionPuntoFijo(fig, id, sX, sY, pfx, pfy);

    //ASIGNA LOS NUEVOS VALORES A FIGURA
    for(int i=0;i<figres.numRen();i++)
       for(int j=0;j<figres.numCol();j++)
           Fig[i][j]=figres.GETM(i,j);

    repaint();//INVOCA A paintEvent
}

void Dialog::rotar(float angulo)
{
    Matrix fig, id, figres;
    fig.Inicializa(4, 3);
    figres.Inicializa(4, 3);
    id.Inicializa(3, 3);

   //ASIGNAR PUNTOS
    for (int i = 0; i < fig.numRen(); i++)
        for (int j = 0; j < fig.numCol(); j++)
            fig.SETM(i, j, Fig[i][j]);

    //Figura resultante, es decir transformada
    figres.rotacion(fig, id, angulo);

    //ASIGNA LOS NUEVOS VALORES A FIGURA
    for(int i=0;i<figres.numRen();i++)
       for(int j=0;j<figres.numCol();j++)
           Fig[i][j]=figres.GETM(i,j);

    repaint();//INVOCA A paintEvent
}

void Dialog::rotarPuntoFijo(float angulo, double pfx, double pfy)
{
    Matrix fig, id, figres;
    fig.Inicializa(4, 3);
    id.Inicializa(3, 3);
    figres.Inicializa(4, 3);
    //ASIGNAR PUNTOS
    for(int i=0;i<figres.numRen();i++)
       for(int j=0;j<figres.numCol();j++)
           figres.SETM(i,j,Fig[i][j]);

    //Figura resultante, es decir transformada
    figres.rotacionPuntoPivote(fig, id, angulo, pfx, pfy);

    //ASIGNA LOS NUEVOS VALORES A FIGURA
    for(int i=0;i<figres.numRen();i++)
       for(int j=0;j<figres.numCol();j++)
           Fig[i][j]=figres.GETM(i,j);

    repaint();//INVOCA A paintEvent
}

//TRASLACION
//BOTON FLECHA ARRIBA
void Dialog::on_pushButton_clicked()
{

    //trasladar(0,tY+1);
    trasladar(0,tY+ui->spinBox_2->value());
}
//BOTON FLECHA ABAJO
void Dialog::on_pushButton_2_clicked()
{
    //trasladar(0,tY-1);
    trasladar(0,tY-ui->spinBox_2->value());
}
//BOTON FLECHA DERECHA
void Dialog::on_pushButton_3_clicked()
{
    //trasladar(tX+1,0);
    trasladar(tX + ui->spinBox->value(),0);
}
//BOTON FLECHA IZQ.
void Dialog::on_pushButton_4_clicked()
{
    trasladar(tX - ui->spinBox->value(),0);
}

void Dialog::on_pushButton_5_clicked()
{
    for(int i = 0; i< 4; i++)
      for(int j = 0; j < 3; j++)
         Fig[i][j] = FigAux[i][j];
    tX = tY = 0;
    repaint();
}
//Esquina superior izquierda
void Dialog::on_pushButton_6_clicked()
{
   trasladar(tX - ui->spinBox->value(), tY + ui->spinBox_2->value() );
}
//Esquina superior derecha
void Dialog::on_pushButton_8_clicked()
{
   trasladar(tX + ui->spinBox->value(), tY + ui->spinBox_2->value() );
}
//Esquina inferior izquierda
void Dialog::on_pushButton_7_clicked()
{
    trasladar(tX - ui->spinBox->value(), tY - ui->spinBox_2->value() );
}
//Esquina inferior derecha
void Dialog::on_pushButton_9_clicked()
{
     trasladar(tX + ui->spinBox->value(), tY - ui->spinBox_2->value() );
}

void Dialog::on_pushButton_10_clicked()
{
    QColor color_seleccionado = QColorDialog::getColor(Qt::white,this,"Selecciona el color");
    if(color_seleccionado.isValid()){
        color = color_seleccionado;
        repaint();
    }
}

void Dialog::on_pushButton_11_clicked()
{
    //aumento += 5;
    //repaint();

    //Validar que los line edit tengan valores
    double sX = ui->lineEdit->text().toDouble();
    double sY = ui->lineEdit_2->text().toDouble();
    if( sX != 0 && sY != 0 )
        escalar(sX, sY);
    else{
     double sX = 1;
     double sY = 1;
     ui->lineEdit->setText("1");
     ui->lineEdit_2->setText("1");
     escalar(sX, sY);
    }
}

void Dialog::on_pushButton_12_clicked()
{
    //aumento -= 5;
    //repaint();

    double sX = ui->lineEdit->text().toDouble();
    double sY = ui->lineEdit_2->text().toDouble();
    int pfx = double(ui->spinBox_3->value());
    int pfy = double(ui->spinBox_4->value());

    escalarPuntoFijo(sX, sY, pfx, pfy);
}

void Dialog::on_pushButton_13_clicked()
{
    double angulo = ui->spinBox_5->value();
    rotar(angulo);
}

void Dialog::on_pushButton_14_clicked()
{
    double angulo = ui->spinBox_5->value();
    double pFx = ui->spinBox_6->value();
    double pFy = ui->spinBox_7->value();
    rotarPuntoFijo(angulo, pFx, pFy);
}

void Dialog::on_pushButton_15_clicked()
{

}

void Dialog::on_pushButton_16_clicked()
{

}
