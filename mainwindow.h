#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <meteor.h>
#include <mete.h>
#define tiempo 0.1
#define G 10
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


private slots:
    void on_pushButton_clicked();
    void pendulo();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer, *timer2, *timer3;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *pend;
    QPen pen;
    double x1_pend=200;
    double x2_pend=0;
    double y1_pend=0;
    double y2_pend=0;
    double radio1_pend=45;
    double radio2_pend=45;
    double magnitud;

    float dt; float x,y,alto,ancho,te;
    int h_limit,tm;
    int v_limit;
    void keyPressEvent(QKeyEvent *event);
    muros *muro;
    void borderCollision(mete *b);
    QList<meteor *> bars;
};
#endif // MAINWINDOW_H
