#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QMouseEvent>
#include <graficos.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::Dialog *ui;
    void paintEvent(QPaintEvent *e);
    QColor color;
    QPainter *canvas;
    graficos *grafico;
    int x1, y1, x2, y2, xc, yc, radio;

    int cont = 0;
    bool linea, circuloPitagoras,circuloPolares,circuloTres,circuloBresenham,circuloParam, espiral1, espiral2;
    float factor,factor2, teta;

protected:
    void mousePressEvent(QMouseEvent *evt) override;
    void mouseReleaseEvent(QMouseEvent *evt) override;
    void mouseMoveEvent(QMouseEvent *evt) override;
    void mouseDoubleClickEvent(QMouseEvent *evt) override;
};
#endif // DIALOG_H
