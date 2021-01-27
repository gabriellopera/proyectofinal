#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);

    h_limit = 800;
    v_limit = 450;

    //scene = new QGraphicsScene(0,0,0,0);
    timer = new QTimer(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);
    scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
    ui->graphicsView->setScene(scene);

    scene->addRect(scene->sceneRect());


    timer->start(15);
    bars.push_back(new meteor);
    bars.back()->actualizar(v_limit);
    scene->addItem(bars.back());


    muro.append(new muros(20,170,-70,-60));
    muro.append(new muros(220,20,-180,-60));
    muro.append(new muros(220,20,-70,-340));
    for(auto it=muro.begin();it!=muro.end();it++)
    {
        scene->addItem(*it);
    }

    timer2 = new QTimer(this);
    QBrush brush(Qt::yellow);
    QBrush brush2(Qt::black);
    x1_pend=200;
    x2_pend=0;
    y1_pend=0;
    y2_pend=0;
    radio1_pend=45;
    radio2_pend=45;
    pend2 = scene->addEllipse(x1_pend+300,  y1_pend+100,radio1_pend, radio2_pend, pen, brush);
    pend = scene->addEllipse(x1_pend,  y1_pend,radio1_pend, radio2_pend, pen, brush);
    negro = scene->addEllipse(10,10,40,40,pen,brush2);
    negro = scene->addEllipse(x,y,40,40,pen,brush2);
    magnitud = sqrt(pow(x1_pend - x2_pend, 2)+ pow(y1_pend - y2_pend, 2));
    connect(timer2,SIGNAL(timeout()),this,SLOT(pendulo()));
    timer2->start(10);

    rad =0.01745329252;


    ui->pushButton_3->hide();
    ui->pushButton->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->textBrowser_4->hide();
    ui->lcdNumber->hide();
    ui->lineEdit->hide();
    ui->graphicsView->hide();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete timer2;
    delete scene;
    delete ui;
}

void MainWindow::actualizar()
{
    for (int i = 0;i< bars.size() ;i++ ) {
        bars.at(i)->actualizar(v_limit);
        borderCollision(bars.at(i)->getEsf());
    }
    clock_t te;
    te=clock();
    tm=60-(int(te)/CLOCKS_PER_SEC);
    ui->lcdNumber->display(tm);
}

void MainWindow::borderCollision(mete *b)
{   int z=5;
    if(b->getPX()<b->getR()){
        b->set_vel(-1*(0+(rand()%z))*b->getVX(),b->getVY(),b->getR(),b->getPY());
    }
    if(b->getPX()>h_limit-b->getR()){
        b->set_vel(-1*(0+(rand()%z))*b->getVX(),b->getVY(),h_limit-b->getR(),b->getPY());
    }
    if(b->getPY()<b->getR()){
        b->set_vel(b->getVX(),-1*(0+(rand()%z))*b->getVY(),b->getPX(),b->getR());
    }
    if(b->getPY()>v_limit-b->getR()){
        b->set_vel(b->getVX(),-1*(0+(rand()%z))*b->getVY(),b->getPX(),v_limit-b->getR());
    }
    if(bars.back()->collidesWithItem(pend)){
        b->set_vel(0,0,800,-10);

    }
    if(bars.back()->collidesWithItem(pend2)){
        b->set_vel(0,0,800,-10);
    }
    if(bars.back()->collidesWithItem(negro)){
        timer->stop();
        timer2->stop();
        message.setText("PASASTE A LA SEGUNDA GALAXIA!!");
        message.setInformativeText("");
        message.exec();
    }
    for(auto it=muro.begin();it!=muro.end();it++)
    {
        if(bars.back()->collidesWithItem(*it)){
            b->set_vel(0,0,800,-10);
        }
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

void MainWindow::pendulo()
{

    double angulo = asin((x1_pend ) / magnitud);
    double a_x = -G * sin(angulo);
    static double vx = 0;
    vx += a_x * tiempo;
    static double w = 0;
    w = vx / magnitud;
    double ace_angulo = w / tiempo;
    angulo = angulo + w * tiempo  + (ace_angulo / 2 ) * tiempo * tiempo;
    x1_pend = magnitud * sin(angulo);
    y1_pend = magnitud * cos(angulo);
    pend->setPos(x1_pend, y1_pend);
    pend2->setPos(x1_pend, y1_pend);

}

void MainWindow::circular()
{   i+=rad;
    int r=70;
    x=-1*r*cos(i*2);
    y=-1*r*sin(i*2);

}

void MainWindow::on_pushButton_clicked()
{
    name=ui->lineEdit->text();
    if(name==""){
        message.setText("INGRESE UN USUARIO");
        message.setInformativeText("");
        message.exec();
    }
    else if (1) {

    }
    else{
    name=ui->lineEdit->text();
    ui->textBrowser_4->show();
    ui->textBrowser_5->hide();
    ui->graphicsView->show();
    ui->pushButton_3->show();
    ui->pushButton->hide();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    ui->pushButton_6->show();
    ui->pushButton_7->show();
    ui->lcdNumber->show();
    ui->lineEdit->hide();
    ui->pushButton_8->hide();
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(circular()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->show();
    ui->pushButton->show();
    ui->pushButton_2->hide();
}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::on_pushButton_5_clicked()
{

}

void MainWindow::on_pushButton_6_clicked()
{
    timer->start(15);
    timer2->start(10);

}

void MainWindow::on_pushButton_7_clicked()
{
    timer->stop();
    timer2->stop();
}

void MainWindow::on_pushButton_8_clicked()
{

}
