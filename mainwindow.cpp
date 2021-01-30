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

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);
    scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
    ui->graphicsView->setScene(scene);

    scene->addRect(scene->sceneRect());






    muro.append(new muros(20,170,-70,-60));
    muro.append(new muros(220,20,-180,-60));
    muro.append(new muros(220,20,-70,-340));
    muro.append(new muros(20,170,-600,-120));
    muro.append(new muros(220,20,-460,-390));
    for(auto it=muro.begin();it!=muro.end();it++)
    {
        scene->addItem(*it);
    }


    QBrush brush(Qt::yellow);
    QBrush brush2(Qt::black);
    QBrush brush3(Qt::red);

    pend2 = scene->addEllipse(x1_pend+300,  y1_pend+100,radio1_pend, radio2_pend, pen, brush);
    pend = scene->addEllipse(x1_pend,  y1_pend,radio1_pend, radio2_pend, pen, brush);
    //negro = scene->addEllipse(10,10,40,40,pen,brush2);
    negro = scene->addEllipse(690,10,40,40,pen,brush2);
    circle = scene->addEllipse(posicionX,posicionY,40,40,pen,brush3);
    magnitud = sqrt(pow(x1_pend - x2_pend, 2)+ pow(y1_pend - y2_pend, 2));

    timer = new QTimer(this);
    timer->start(15);
    timer2 = new QTimer(this);
    timer2->start(10);
    timer3 = new QTimer(this);
    timer3->start(1000);
    timerCron2 = new QTimer(this);
    timerCron2->start(1000);
    timerP2 = new QTimer(this);
    timerP2->start(15);


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
    ui->pushButton_12->hide();
    ui->lcdNumber_2->hide();
    ui->pushButton_13->hide();
    ui->lcdNumber_3->hide();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete timer2;
    delete timer3;
    delete timerCron2;
    delete timerP2;
    delete scene;
    delete ui;
}

void MainWindow::actualizar()
{
        player1->actualizar(v_limit);
        borderCollision(player1->getEsf());
}

void MainWindow::actualizar2()
{
    if(multijugador==1){
        player2->actualizar(v_limit);
        borderCollision2(player1->getEsf(),player2->getEsf());
    }

}

void MainWindow::crono()
{
    cronometro-=1;
    ui->lcdNumber->display(cronometro);
    ui->lcdNumber_2->display(level+1);
}

void MainWindow::crono2()
{
    cronometro2-=1;
    ui->lcdNumber_3->display(cronometro2);
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
    if(player1->collidesWithItem(pend)){
        b->set_vel(0,0,800,-10);
    }
    if(player1->collidesWithItem(pend2)){
        b->set_vel(0,0,800,-10);
    }
    if(player1->collidesWithItem(circle)){
        b->set_vel(0,0,800,-10);
    }
    if(bandera==2){
        if(player1->collidesWithItem(circle2)){
        b->set_vel(0,0,800,-10);
        }
    }
    if(bandera==3){
        for(auto it=muro.begin();it!=muro.end();it++)
        {
            if(player1->collidesWithItem(*it)){
                b->set_vel(0,0,800,-10);
            }
        }
    }
    if(multijugador==0){
        if(player1->collidesWithItem(negro)){
            level+=1;
            b->set_vel(0,0,800,400);
            timer->stop();
            timer2->stop();
            timer3->stop();
            if(level==1){
                message.setText("PASASTE A LA SEGUNDA GALAXIA!!");
                message.setInformativeText("");
                message.exec();
                bandera=2;
                circle2 = scene->addEllipse(posicion2X,posicion2Y+250,40,40,pen,brush4);
                timer->start(15);
                timer2->start(10);
                timer3->start(1000);
            }
            if(level==2){
                message.setText("PASASTE A LA TERCERA GALAXIA!!");
                message.setInformativeText("");
                message.exec();
                bandera+=1;
                for(int i=0;i<muro.size();i++)
                {
                    scene->removeItem(muro.at(i));
                    muro.removeAt(i);
                }
                muro.append(new muros(20,170,-70,-60));
                muro.append(new muros(220,20,-180,-60));
                muro.append(new muros(220,20,-70,-340));
                muro.append(new muros(20,170,-600,-120));
                muro.append(new muros(220,20,-460,-390));
                muro.append(new muros(220,20,-200,-240));
                for(auto it=muro.begin();it!=muro.end();it++)
                {
                    scene->addItem(*it);
                }
                timer->start(15);
                timer2->start(12);
                timer3->start(1000);
            }
            if(level==3){
                message.setText("FELICITACIONES, LOGRASTE ESCAPAR DE LAS GALAXIA!!");
                message.setInformativeText("");
                message.exec();

            }
        }
    }
    for(auto it=muro.begin();it!=muro.end();it++)
    {

        if(player1->collidesWithItem(*it)){
            b->set_vel(-1*b->getVX(),-1*b->getVY(),b->getPX(),b->getPY());
        }
    }


}

void MainWindow::borderCollision2(mete *b, mete *c)
{   int z=5;QBrush brush4(Qt::red);
    //player1
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
    //player2
    if(c->getPX()<c->getR()){
            c->set_vel(-1*(0+(rand()%z))*c->getVX(),c->getVY(),c->getR(),c->getPY());
    }
    if(c->getPX()>h_limit-c->getR()){
        c->set_vel(-1*(0+(rand()%z))*c->getVX(),c->getVY(),h_limit-c->getR(),c->getPY());
    }
    if(c->getPY()<c->getR()){
        c->set_vel(c->getVX(),-1*(0+(rand()%z))*c->getVY(),c->getPX(),c->getR());
    }
    if(c->getPY()>v_limit-c->getR()){
        c->set_vel(c->getVX(),-1*(0+(rand()%z))*c->getVY(),c->getPX(),v_limit-c->getR());
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
    if(player1->collidesWithItem(pend)){
        b->set_vel(0,0,800,-10);
    }
    if(player1->collidesWithItem(pend2)){
        b->set_vel(0,0,800,-10);
    }
    if(player1->collidesWithItem(circle)){
        b->set_vel(0,0,800,-10);
    }
    if(player2->collidesWithItem(pend)){
        c->set_vel(0,0,800,-10);
    }
    if(player2->collidesWithItem(pend2)){
        c->set_vel(0,0,800,-10);
    }
    if(player2->collidesWithItem(circle)){
        c->set_vel(0,0,800,-10);
    }
    if(bandera==2){
        if(player1->collidesWithItem(circle2)){
        b->set_vel(0,0,800,-10);
        }
        if(player2->collidesWithItem(circle2)){
        c->set_vel(0,0,800,-10);
        }
    }
    if(bandera==3){
        for(auto it=muro.begin();it!=muro.end();it++)
        {
            if(player1->collidesWithItem(*it)){
                b->set_vel(0,0,800,-10);
            }
        }
        for(auto it=muro.begin();it!=muro.end();it++)
        {
            if(player2->collidesWithItem(*it)){
                c->set_vel(0,0,800,-10);
            }
        }
    }

    for(auto it=muro.begin();it!=muro.end();it++)
    {

        if(player1->collidesWithItem(*it)){
            b->set_vel(-1*b->getVX(),-1*b->getVY(),b->getPX(),b->getPY());
        }
    }
    for(auto it=muro.begin();it!=muro.end();it++)
    {

        if(player2->collidesWithItem(*it)){
            c->set_vel(-1*c->getVX(),-1*c->getVY(),c->getPX(),c->getPY());
        }
    }


    if(multijugador==0){
        if(player1->collidesWithItem(negro)){
            level+=1;
            b->set_vel(-1*b->getVX(),-1*b->getVY(),800,400);
            timer->stop();
            timer2->stop();
            timer3->stop();
            if(level==1){
                message.setText("PASASTE A LA SEGUNDA GALAXIA!!");
                message.setInformativeText("");
                message.exec();
                bandera=2;
                circle2 = scene->addEllipse(posicion2X,posicion2Y+250,40,40,pen,brush4);
                timer->start(15);
                timer2->start(10);
                timer3->start(1000);
            }
            if(level==2){
                message.setText("PASASTE A LA TERCERA GALAXIA!!");
                message.setInformativeText("");
                message.exec();
                bandera+=1;
                for(int i=0;i<muro.size();i++)
                {
                    scene->removeItem(muro.at(i));
                    muro.removeAt(i);
                }
                muro.append(new muros(20,170,-70,-60));
                muro.append(new muros(220,20,-180,-60));
                muro.append(new muros(220,20,-70,-340));
                muro.append(new muros(20,170,-600,-120));
                muro.append(new muros(220,20,-460,-390));
                muro.append(new muros(220,20,-200,-240));
                for(auto it=muro.begin();it!=muro.end();it++)
                {
                    scene->addItem(*it);
                }
                timer->start(15);
                timer2->start(12);
                timer3->start(1000);
            }
            if(level==3){
                message.setText("FELICITACIONES, LOGRASTE ESCAPAR DE LAS GALAXIA!!");
                message.setInformativeText("");
                message.exec();

            }
        }
    }

    if(multijugador==1){
        if(player1->collidesWithItem(negro)){
            b->set_vel(-1*b->getVX(),-1*b->getVY(),800,400);
            timer->stop();
            timer3->stop();
            bandP1=true;
        }
        if(player2->collidesWithItem(negro)){
            c->set_vel(-1*c->getVX(),-1*c->getVY(),800,400);
            timerP2->stop();
            timerCron2->stop();
            bandP2=true;
        }

        if(bandP1==true && bandP2==true){
            timer2->stop();
            level+=1;

                    message.setText("CONTINUA LA SEGUNDA GALAXIA!!");
                    message.setInformativeText("");
                    message.exec();
                    bandera=2;
                    circle2 = scene->addEllipse(posicion2X,posicion2Y+250,40,40,pen,brush4);
                    timer->start(15);
                    timer2->start(10);
                    timer3->start(1000);
                    timerP2->start(15);
                    timerCron2->start(1000);
                    bandP1=false;
                    bandP2=false;

        }

    }


}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    mete * b = player1->getEsf();
    mete * c = player2->getEsf();

    if(multijugador==0){
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
    else if(multijugador==1){


        if(event->key() == Qt::Key_D){
            b->set_vel(10,b->getVY(),b->getPX(),b->getPY());
        }
        if(event->key() == Qt::Key_A){
            b->set_vel(-10,b->getVY(),b->getPX(),b->getPY());
        }
        if(event->key() == Qt::Key_W){
            b->set_vel(b->getVX(),25,b->getPX(),b->getPY());
        }
        if(event->key() == Qt::Key_K){
            c->set_vel(10,c->getVY(),c->getPX(),c->getPY());
        }
        if(event->key() == Qt::Key_H){
            c->set_vel(-10,c->getVY(),c->getPX(),c->getPY());
        }
        if(event->key() == Qt::Key_U){
            c->set_vel(c->getVX(),25,c->getPX(),c->getPY());
        }
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

    if(bandera==2 || bandera==3){
        acum2+=0.01;
        posicion2X = posicion2X - velocidad2X*tiempo;
        posicion2Y= -5*sin(2*3.1415*acum2/2)+posicion2Y;
        circle2->setPos(posicion2X+150,posicion2Y+80);}

}

void MainWindow::on_pushButton_clicked() //start
{
    if(multijugador==0){
        name=ui->lineEdit->text();
        if(name==""){
            message.setText("INGRESE USUARIO PARA PLAYER 1");
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
            ui->pushButton_12->show();
            ui->lcdNumber_2->show();
            player1 = new meteor(1);
            scene->addItem(player1);
            connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));//player1
            connect(timer2,SIGNAL(timeout()),this,SLOT(pendulo()));
            connect(timer3,SIGNAL(timeout()),this,SLOT(crono()));
            connect(timer2,SIGNAL(timeout()),this,SLOT(senoidal()));
        }
    }
    if(multijugador==1){
        name2=ui->lineEdit_2->text();
        if(name2==""){
            message.setText("INGRESE USUARIO PARA PLAYER 2");
            message.setInformativeText("");
            message.exec();
        }
        else{
            name2=ui->lineEdit_2->text();
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
            ui->pushButton_12->show();
            ui->lcdNumber_2->show();
            ui->pushButton_13->show();
            ui->lcdNumber_3->show();
            player1 = new meteor(1);
            scene->addItem(player1);
            player2 = new meteor(2);
            scene->addItem(player2);

            connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
            connect(timerP2,SIGNAL(timeout()),this,SLOT(actualizar2()));
            connect(timerCron2,SIGNAL(timeout()),this,SLOT(crono2()));
            connect(timer2,SIGNAL(timeout()),this,SLOT(pendulo()));
            connect(timer3,SIGNAL(timeout()),this,SLOT(crono()));
            connect(timer2,SIGNAL(timeout()),this,SLOT(senoidal()));

        }
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
    timerCron2->start(1000);
    timerP2->start(15);
    ui->pushButton_6->hide();
    ui->pushButton_7->show();

}

void MainWindow::on_pushButton_7_clicked() //stop
{
    timer->stop();
    timer2->stop();
    timer3->stop();
    timerCron2->stop();
    timerP2->stop();
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
    multijugador=1;
}

void MainWindow::on_pushButton_10_clicked() //single
{
    ui->pushButton_10->hide();
    ui->pushButton_9->show();
    ui->textBrowser_7->hide();
    ui->lineEdit_2->hide();
    multijugador=0;
}

void MainWindow::on_pushButton_11_clicked()//reiniciar
{
    mete *b = bars.at(0)->getEsf();
    if(level==0){
        cronometro=TT;
        b->set_vel(0,0,800,-10);
        posicionX=0;
        posicionY=0;
        acum=0;
    }
    if(level==1){
        bandera=0;
        delete circle2;
        cronometro=TT;
        b->set_vel(0,0,800,-10);
        posicionX=0;velocidadX=-7;
        posicionY=0;
        posicion2X=0;
        posicion2Y=0;
        acum=0;acum2=0;level=0;
    }
    if(level==2){
        bandera=0;
        delete circle2;
        cronometro=TT;
        b->set_vel(0,0,800,-10);
        posicionX=0;velocidadX=-7;
        posicionY=0;
        posicion2X=0;
        posicion2Y=0;
        acum=0;acum2=0;level=0;
        for(int i=0;i<muro.size();i++)
        {
            scene->removeItem(muro.at(i));
            muro.removeAt(i);
        }
        muro.append(new muros(20,170,-70,-60));
        muro.append(new muros(220,20,-180,-60));
        muro.append(new muros(220,20,-70,-340));
        muro.append(new muros(20,170,-600,-120));
        muro.append(new muros(220,20,-460,-390));
        for(auto it=muro.begin();it!=muro.end();it++)
        {
            scene->addItem(*it);
        }
    }
}
