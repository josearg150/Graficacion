#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    limiteInf = 1; //TOMAR ESTOS VALORES DEL IDE GRAFICO
    limiteSup = 12;
    band = true;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    ui->comboBox->addItem("Dragon");
    ui->comboBox->addItem("Arabesco");
}

Widget::~Widget()
{
    delete ui;
    graf = new graficos();

    //PROVOCA CRASHEO
    //henon = new Henon();

}


void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    canvas = new QPainter(this);
    qsrand(unsigned(time(nullptr)));
    //henon->iniciar(canvas);
     if(band){
        if(limiteInf <= limiteSup){
            dragon(limiteInf);
            limiteInf++;
        }else{
            band = false;
        }
    }
    if(!band){
        limiteInf--;
        dragon(limiteInf);
        if(limiteInf == 0){
            band = true;
        }
    }

    canvas->end();

}

void Widget::dragon(int limite)
{
    //QPainter canvas(this);
    int i;

    paso = 4096;
    if(ui->comboBox->currentIndex() == 0)
    {
       signo = -1;
    }else if(ui->comboBox->currentIndex() == 1){
       signo *= -1;
    }
    EjeX[1] = canvas->window().width() / 4;
    EjeX[4097] = 3 * canvas->window().width() / 4;
    if(ui->comboBox->currentIndex() == 0)
    {
       EjeY[1] = EjeY[4097] = 2 * canvas->window().height() / 3;
    }else if(ui->comboBox->currentIndex() == 1){
       EjeY[1] = EjeY[4097] = canvas->window().height() / 4;

    }
    //DIBUJAMOS LA LINEA HORIZONTAL INICIAL O QUE SE VA A FRACRALIZAR
   // canvas->drawLine(EjeX[1],EjeY[1],EjeX[4097],EjeY[4097]);

    //usando lineaDDA
    graf->lineaDDA(EjeX[1],EjeY[1],EjeX[4097],EjeY[4097],canvas);
    canvas->drawText(5,15,"CURVA FRACTAL DEL DRAGON");

    for(i = 1; i <= limite; i++){
        generarDragon(canvas);
        paso /= 2;
    }

    //canvas->end();
}

void Widget::generarDragon(QPainter *canvas)
{
    int j, dx, dy;
    j = paso / 2;
    canvas->setPen(QColor(qrand()%155+100,qrand()%155+100,qrand()%155+100));

    for(int i = 1; i <= 4096; i+= paso){
        dx = EjeX[paso + i] - EjeX[i];
        dy = EjeY[paso + i] - EjeY[i];
        if(ui->comboBox->currentIndex() == 0)
        {
           signo *= -1;
        }else if(ui->comboBox->currentIndex() == 1){
           signo = -1;
        }
        EjeX[i + j] = EjeX[i] + (dx + (dy * signo)) / 2;
        EjeY[i + j] = EjeY[i] + (dy - (dx * signo)) / 2;
       //canvas->drawLine(EjeX[i],EjeY[i],EjeX[i + j], EjeY[i + j]);
       //canvas->drawLine(EjeX[i + j],EjeY[i + j],EjeX[i + paso], EjeY[i + paso]);

        //usando lineaDDA

        graf->lineaDDA(EjeX[i],EjeY[i],EjeX[i + j], EjeY[i + j],canvas);
        graf->lineaDDA(EjeX[i + j],EjeY[i + j],EjeX[i + paso], EjeY[i + paso],canvas);


    }
}




void Widget::on_pushButton_clicked()
{
    timer->start(100);

}

void Widget::on_pushButton_2_clicked()
{
   timer->stop();
}


