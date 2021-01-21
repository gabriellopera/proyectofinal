#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <meteor.h>
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


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<muros *> muros2;
    QGraphicsScene *scene;
    QTimer *timer;
    meteor *haley;

    float x,y,ancho,alto;
};
#endif // MAINWINDOW_H
