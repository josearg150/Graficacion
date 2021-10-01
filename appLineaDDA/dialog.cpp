#include "dialog.h"
#include "ui_dialog.h"

#include <QDialog>
#include <QColorDialog>
#include <graficos.h>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    x1 = 0;
    y1 = 0;
    x1 = y2 = 0;

    cont = 0;
    linea = circuloPolares = circuloPitagoras = circuloTres = circuloBresenham
            = circuloParam = espiral1 = espiral2 =false;

}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    canvas = new QPainter(this);

    grafico = new graficos();
    //grafico->lineaDDA(x1, y1,x2,y2,canvas,color);
    if(linea)
        grafico->lineaDDA(x1, y1, x2, y2, canvas, color);
    else if(circuloPitagoras)
        grafico->circuloPitagoras(xc, yc, radio, canvas);
    else if(circuloPolares)
        grafico->circuloPolares(xc, yc, radio, canvas);
    else if(circuloTres)
        grafico->circuloTres(xc, yc, radio, canvas);
    else if(circuloBresenham)
        grafico->circuloBresenham(xc, yc, radio, canvas);
    else if(circuloParam)
        grafico->circuloParametrico(xc, yc, radio, canvas);
    else if(espiral1)
        grafico->espiral1(canvas,color,factor);
    else if(espiral2)
        grafico->espiral2(canvas,color,teta,factor2);

    linea = circuloPolares = circuloPitagoras = circuloTres = circuloBresenham
            = circuloParam = espiral1 = espiral2 =false;
    canvas->end();
}

void Dialog::mousePressEvent(QMouseEvent *evt)
{
    //x1
    ui->lineEdit->setText(QString::number(evt->pos().x()));
    //y1
    ui->lineEdit_2->setText(QString::number(evt->pos().y()));
}

void Dialog::mouseReleaseEvent(QMouseEvent *evt)
{
    //x2
    ui->lineEdit_3->setText(QString::number(evt->pos().x()));
    //y2
    ui->lineEdit_4->setText(QString::number(evt->pos().y()));
    //llamar al metodo para dibujar la linea
    ui->pushButton->click();
}

void Dialog::mouseMoveEvent(QMouseEvent *evt)
{
    //x2
    ui->lineEdit_3->setText(QString::number(evt->pos().x()));
    //y2
    ui->lineEdit_4->setText(QString::number(evt->pos().y()));
    //llamar al metodo para dibujar la linea
    ui->pushButton->click();
}

void Dialog::mouseDoubleClickEvent(QMouseEvent *evt)
{
    Q_UNUSED(evt);
}

void Dialog::on_pushButton_clicked()
{
    x1 = ui->lineEdit->text().toInt();
    y1 = ui->lineEdit_2->text().toInt();
    x2 = ui->lineEdit_3->text().toInt();
    y2 = ui->lineEdit_4->text().toInt();

    linea = true;

    update();

}

void Dialog::on_pushButton_2_clicked()
{
    QColor color_seleccionado = QColorDialog::getColor(Qt::white,this,"Selecciona el color");
    if(color_seleccionado.isValid()){
        color = color_seleccionado;
    }
}


void Dialog::on_pushButton_3_clicked()
{
    xc = ui->spinBox->value();
    yc = ui->spinBox_2->value();
    radio = ui->spinBox_3->value();

    circuloPitagoras = true;
    update();
}

void Dialog::on_pushButton_4_clicked()
{
    xc = ui->spinBox->value();
    yc = ui->spinBox_2->value();
    radio = ui->spinBox_3->value();

    circuloPolares = true;
    update();
}

void Dialog::on_pushButton_5_clicked()
{
    xc = ui->spinBox->value();
    yc = ui->spinBox_2->value();
    radio = ui->spinBox_3->value();

    circuloTres = true;
    update();
}

void Dialog::on_pushButton_6_clicked()
{
    xc = ui->spinBox->value();
    yc = ui->spinBox_2->value();
    radio = ui->spinBox_3->value();

    circuloBresenham = true;
    update();
}

void Dialog::on_pushButton_7_clicked()
{
    xc = ui->spinBox->value();
    yc = ui->spinBox_2->value();
    radio = ui->spinBox_3->value();

    circuloParam = true;
    update();
}

void Dialog::on_pushButton_8_clicked()
{
    factor = ui->doubleSpinBox_4->value();
    espiral1 = true;
    update();
}

void Dialog::on_pushButton_9_clicked()
{
    factor2 = ui->doubleSpinBox_6->value();
    teta = ui->doubleSpinBox_5->value();
    espiral2 = true;
    update();
}
