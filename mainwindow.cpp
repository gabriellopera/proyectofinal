#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);

    h_limit = 1200;
    v_limit = 600;

    //scene = new QGraphicsScene(0,0,0,0);

    timer = new QTimer(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);

    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();
    scene->addRect(scene->sceneRect());
    ui->graphicsView->resize(scene->width(),scene->height());
    this->resize(ui->graphicsView->width()+100,ui->graphicsView->height()+100);

    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    timer->start(3);
    bars.push_back(new meteor);
    bars.back()->actualizar(v_limit);
    scene->addItem(bars.back());
}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete ui;
}

void MainWindow::actualizar()
{
    for (int i = 0;i< bars.size() ;i++ ) {
        bars.at(i)->actualizar(v_limit);
        borderCollision(bars.at(i)->getEsf());
    }
}

void MainWindow::borderCollision(mete *b)
{
    if(b->getPX()<b->getR()){

        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getR(),b->getPY());
    }
    if(b->getPX()>h_limit-b->getR()){
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),h_limit-b->getR(),b->getPY());
    }
    if(b->getPY()<b->getR()){
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getR());
    }
    if(b->getPY()>v_limit-b->getR()){
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),v_limit-b->getR());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    mete * b = bars.at(0)->getEsf();
    if(event->key() == Qt::Key_D){
        b->set_vel(25,b->getVY(),b->getPX(),b->getPY());
    }
    if(event->key() == Qt::Key_A){
        b->set_vel(-25,b->getVY(),b->getPX(),b->getPY());
    }
    if(event->key() == Qt::Key_W){
        b->set_vel(b->getVX(),50,b->getPX(),b->getPY());
    }


}

void MainWindow::on_pushButton_clicked()
{

}

