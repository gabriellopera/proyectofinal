#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QRect Desktop = QApplication::desktop()->screenGeometry();
//    x=Desktop.x();
//    y=Desktop.y();
//    ancho=Desktop.width();
//    alto=Desktop.height();


    scene = new QGraphicsScene(x,y,ancho,alto);
    scene->setSceneRect(0,0,0,0);
    scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
    ui->graphicsView->setScene(scene);

    haley = new meteor();
    haley->setPos(300,270);
    scene->addItem(haley);

    muros2.append(new muros(760,10,-200,-750));
    muros2.append(new muros(760,10,-200,-230));
    muros2.append(new muros(10,510,-200,-240));
    muros2.append(new muros(10,510,-950,-240));
//


    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(moveEnemy()));
    timer->start(8);


    for(auto it=muros2.begin();it!=muros2.end();it++)
    {
        scene->addItem(*it);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

