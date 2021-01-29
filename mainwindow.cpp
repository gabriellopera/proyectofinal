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
    muro.append(new muros(20,170,-600,-120));
    muro.append(new muros(220,20,-460,-390));
    for(auto it=muro.begin();it!=muro.end();it++)
    {
        scene->addItem(*it);
    }

    timer2 = new QTimer(this);
    QBrush brush(Qt::yellow);
    QBrush brush2(Qt::black);
    QBrush brush3(Qt::red);

    pend2 = scene->addEllipse(x1_pend+300,  y1_pend+100,radio1_pend, radio2_pend, pen, brush);
    pend = scene->addEllipse(x1_pend,  y1_pend,radio1_pend, radio2_pend, pen, brush);
    negro = scene->addEllipse(10,10,40,40,pen,brush2);
    //negro = scene->addEllipse(750,400,40,40,pen,brush2);
    circle = scene->addEllipse(posicionX,posicionY,40,40,pen,brush3);
    magnitud = sqrt(pow(x1_pend - x2_pend, 2)+ pow(y1_pend - y2_pend, 2));
    timer2->start(10);




    timer3 = new QTimer(this);
    timer3->start(1000);


    ui->pushButton_3->hide();
    ui->pushButton->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->textBrowser_4->hide();
    ui->lcdNumber->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->graphicsView->hide();
    ui->textBrowser_6->hide();
    ui->textBrowser_7->hide();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete timer2;
    delete timer3;
    delete scene;
    delete ui;
}

void MainWindow::actualizar()
{
    for (int i = 0;i< bars.size() ;i++ ) {
        bars.at(i)->actualizar(v_limit);
        borderCollision(bars.at(i)->getEsf());
    }
//    clock_t te;
//    te=clock();
//    tm=60-(int(te)/CLOCKS_PER_SEC);
    //ui->lcdNumber->display(tm);

}

void MainWindow::crono()
{
    cronometro-=1;
    ui->lcdNumber->display(cronometro);
    ui->lcdNumber_2->display(level);
}

void MainWindow::borderCollision(mete *b)
{   int z=5;QBrush brush4(Qt::red);
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

    if(posicionX>h_limit-190){
        velocidadX=7;
    }
    if(posicionX<-150){
        velocidadX=-7;
    }
    if(posicion2X>h_limit-190){
        velocidad2X=(7+(rand()%12));
    }
    if(posicion2X<-150){
        velocidad2X=-(5+(rand()%11));
    }
    if(bars.back()->collidesWithItem(pend)){
        b->set_vel(0,0,800,-10);
    }
    if(bars.back()->collidesWithItem(pend2)){
        b->set_vel(0,0,800,-10);
    }
    if(bars.back()->collidesWithItem(circle)){
        b->set_vel(0,0,800,-10);
    }
    if(bars.back()->collidesWithItem(negro)){
        timer->stop();
        timer2->stop();
        timer3->stop();
        if(level==1){
            b->set_vel(0,0,800,400);
            message.setText("PASASTE A LA SEGUNDA GALAXIA!!");
            message.setInformativeText("");
            message.exec();
            bandera=2;
            level+=1;
            circle2 = scene->addEllipse(posicion2X,posicion2Y,40,40,pen,brush4);
            timer->start(15);
            timer2->start(10);
            timer3->start(1000);
            level+=1;
        }
        if(level==2){
            b->set_vel(0,0,800,400);
            message.setText("PASASTE A LA TERCERA GALAXIA!!");
            message.setInformativeText("");
            message.exec();
            bandera=2;
            for(auto it=muro.begin();it!=muro.end();it++)
            {
                if(bars.back()->collidesWithItem(*it)){
                    b->set_vel(0,0,800,-10);
                }
            }
            timer->start(15);
            timer2->start(12);
            timer3->start(1000);
            level+=1;
        }
        if(level==3){
            message.setText("FELICITACIONES, LOGRASTE ESCAPAR DE LAS GALAXIA!!");
            message.setInformativeText("");
            message.exec();
        }
    }
    for(auto it=muro.begin();it!=muro.end();it++)
    {
//        if(bars.back()->collidesWithItem(*it)){
//            b->set_vel(0,0,800,-10);
//        }
        if(bars.back()->collidesWithItem(*it)){
            b->set_vel(-1*b->getVX(),-1*b->getVY(),b->getPX(),b->getPY());
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

void MainWindow::senoidal()
{
    acum+=0.01;
    posicionX = posicionX - velocidadX*tiempo;
    posicionY= 5*sin(2*3.1415*acum/2)+posicionY;
    circle->setPos(posicionX+150,posicionY+70);

    if(bandera==2){
        posicion2X = posicion2X - velocidad2X*tiempo;
        posicion2Y= -5*sin(2*3.1415*acum/2)+posicion2Y;
        circle2->setPos(posicion2X+150,posicion2Y+80);}

}

void MainWindow::on_pushButton_clicked() //start
{
    name=ui->lineEdit->text();
    if(name==""){
        message.setText("INGRESE UN USUARIO");
        message.setInformativeText("");
        message.exec();
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
    ui->pushButton_7->show();
    ui->pushButton_11->show();
    ui->lcdNumber->show();
    ui->lineEdit->hide();
    ui->pushButton_8->hide();
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->lineEdit_2->hide();
    ui->textBrowser_6->hide();
    ui->textBrowser_7->hide();
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(pendulo()));
    connect(timer3,SIGNAL(timeout()),this,SLOT(crono()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(senoidal()));
    }
}

void MainWindow::on_pushButton_2_clicked() //sig in
{
    ui->lineEdit->show();
    ui->pushButton->show();
    ui->pushButton_2->hide();
    ui->pushButton_9->show();
    ui->textBrowser_6->show();
}

void MainWindow::on_pushButton_3_clicked() //save
{
    mete * b = bars.at(0)->getEsf();
    string nomo2=name.toStdString();
    string nomo="C:/Users/GABRIEL/Documents/QT/Labs QT/ProyectoFinal/Proyecto_final-master/partidas/";
    nomo.append(nomo2);
    nomo.append(".txt");

       fstream Fichero(nomo);
        Fichero<<name.toStdString()<<" "<<b->getPX()<<" "<<b->getPY()<<" "<<cronometro<<endl;

        Fichero.close();


}

void MainWindow::on_pushButton_4_clicked() //load
{

}

void MainWindow::on_pushButton_5_clicked()
{

}

void MainWindow::on_pushButton_6_clicked() //play
{
    timer->start(15);
    timer2->start(10);
    timer3->start(1000);
    ui->pushButton_6->hide();
    ui->pushButton_7->show();

}

void MainWindow::on_pushButton_7_clicked() //stop
{
    timer->stop();
    timer2->stop();
    timer3->stop();
    ui->pushButton_7->hide();
    ui->pushButton_6->show();
}

void MainWindow::on_pushButton_8_clicked()
{

}

void MainWindow::on_pushButton_9_clicked() //multiplayer
{
    ui->pushButton_10->show();
    ui->pushButton_9->hide();
    ui->textBrowser_7->show();
    ui->lineEdit_2->show();
}

void MainWindow::on_pushButton_10_clicked() //single
{
    ui->pushButton_10->hide();
    ui->pushButton_9->show();
    ui->textBrowser_7->hide();
    ui->lineEdit_2->hide();
}

void MainWindow::on_pushButton_11_clicked()
{   mete *b = bars.at(0)->getEsf();
    cronometro=60;
    b->set_vel(0,0,800,-10);
}
