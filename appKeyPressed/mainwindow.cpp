#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evt)
{
    if(evt->key() == Qt::Key_Up)
        ui->label->setText("Presionaste flecha arriba");
    if(evt->key() == Qt::Key_Down)
        ui->label->setText("Presionaste flecha abajo");
    if(evt->key() == Qt::Key_X)
        ui->label->setText("Presionaste la tecla X");
    if(evt->key() == Qt::Key_F10)
        this->close();


}

