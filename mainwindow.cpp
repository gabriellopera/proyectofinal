#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);

    h_limit = 900;
    v_limit = 450;


    QRect Desktop = QApplication::desktop()->screenGeometry();
    x=Desktop.x();
    y=Desktop.y();
    ancho=Desktop.width();
    alto=Desktop.height();

    scene = new QGraphicsScene(x,y,ancho,alto);

    timer = new QTimer(this);
    //scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);
    scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
    ui->graphicsView->setScene(scene);
    //ui->centralwidget->adjustSize();
    scene->addRect(scene->sceneRect());
    //ui->graphicsView->resize(700,1300);
    //ui->graphicsView->resize(scene->width(),scene->height());
    //this->resize(ui->graphicsView->width()+0,ui->graphicsView->height()+0);

    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    timer->start(3);
    bars.push_back(new meteor);
    bars.back()->actualizar(v_limit);
    scene->addItem(bars.back());


    muro = new muros(20,220,-100,-200);
    scene->addItem(muro);
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
        b->set_vel(10,b->getVY(),b->getPX(),b->getPY());
    }
    if(event->key() == Qt::Key_A){
        b->set_vel(-10,b->getVY(),b->getPX(),b->getPY());
    }
    if(event->key() == Qt::Key_W){
        b->set_vel(b->getVX(),25,b->getPX(),b->getPY());
    }


}

void MainWindow::on_pushButton_clicked()
{

}

