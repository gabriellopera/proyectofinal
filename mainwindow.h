#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <meteor.h>
#include <mete.h>

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

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QGraphicsScene *scene;
    float dt; float x,y,alto,ancho,t;
    int h_limit,tm;
    int v_limit;
    void keyPressEvent(QKeyEvent *event);
    muros *muro;
    void borderCollision(mete *b);
    QList<meteor *> bars;
};
#endif // MAINWINDOW_H
