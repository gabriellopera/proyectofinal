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
    ui->graphicsView->setScene(scene);
    muros2.append(new muros(760,20,-200,-750));
    muros2.append(new muros(760,20,-200,-230));
    muros2.append(new muros(20,500,-200,-250));
    muros2.append(new muros(20,500,-940,-250));
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

