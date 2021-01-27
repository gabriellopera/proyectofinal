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
#include <QMessageBox>

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
    void circular();
    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer, *timer2, *timer3;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *pend,*pend2,*negro,circle;
    QString name,name2;
    QPen pen;
    double x1_pend;
    double x2_pend;
    double y1_pend;
    double y2_pend;
    double radio1_pend;
    double radio2_pend;
    double magnitud;
    QMessageBox message;
    float dt; float x,y,alto,ancho,te,i,rad;
    int h_limit,tm;
    int v_limit;
    void keyPressEvent(QKeyEvent *event);
    void borderCollision(mete *b);
    QList<meteor *> bars;
    QList<muros *> muro;
};
#endif // MAINWINDOW_H
