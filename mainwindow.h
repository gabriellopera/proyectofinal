#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <meteor.h>
#include <mete.h>
#include "moneda.h"
#define tiempo 0.1
#define G 10
#define TT 60
#define xTT 30
#include <QMainWindow>
#include "muros.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QRect>
#include <QDesktopWidget>
#include <QDebug>
#include <ctime>
#include <math.h>
#include <QMessageBox>
#include <string.h>
#include <QString>
#include <string>
#include<conio.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <windows.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void actualizar();
    void actualizar2();
    void crono();
    void crono2();

private slots:
    void on_pushButton_clicked();
    void pendulo();
    void senoidal();
    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QTimer *timer, *timer2, *timer3, *timerP2, *timerCron2;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *pend,*pend2,*negro,*circle,*circle2;
    QString name,name2;
    QPen pen;
    double x1_pend=200,x2_pend=0, y1_pend=0, y2_pend=0, radio1_pend=45, radio2_pend=45, magnitud;
    double posicionX=0, posicionY=0, velocidadX=-7,velocidad2X=8,posicion2X=0, posicion2Y=0;
    QMessageBox message;
    float dt; float x,y,alto,ancho,te,i,rad;float acum=0,acum2=0;
    int h_limit,tm,bandera=0,multijugador=0,difficulty=10;
    int v_limit, cronometro=TT, cronometro2=TT, level=0;
    bool bandP1=false, bandP2=false;
    void keyPressEvent(QKeyEvent *event);
    void borderCollision(mete *b);
    void borderCollision2(mete *b, mete *c);
    QList<meteor *> bars;
    QList<muros *> muro;
    QList<moneda *> monedas;
    meteor *player1, *player2;
};
#endif // MAINWINDOW_H
