#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);

    //Limites para la escena
    h_limit = 800;
    v_limit = 450;

    //Configuración para la escena con los limites
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);
    scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());


    //Se agregan monedas a la lista de monedas, con su respectiva posición
    monedas.append(new moneda(-35,-35,525,360));
    monedas.append(new moneda(-35,-35,225,200));
    monedas.append(new moneda(-35,-35,500,140));
    monedas.append(new moneda(-35,-35,160,40));
    monedas.append(new moneda(-35,-35,30,360));
    for(auto it=monedas.begin();it!=monedas.end();it++){ //Ciclo para añadir cada una de las monedas a la escena
        scene->addItem(*it);
    }

    //Se agregan los muros a la lista de muro


    QBrush brush(Qt::yellow); //Propiedades de color para las elipses o circulos
    QBrush brush2(Qt::black); //Propiedades de color para las elipses o circulos
    QBrush brush3(Qt::red); //Propiedades de color para las elipses o circulos

    pend = scene->addEllipse(x1_pend,  y1_pend,radio1_pend, radio2_pend, pen, brush); //Se crea objeto con propiedades del péndulo
    pend2 = scene->addEllipse(x1_pend+300,  y1_pend+100,radio1_pend, radio2_pend, pen, brush); //Se crea segundo péndulo
    negro = scene->addEllipse(10,10,40,40,pen,brush2);
    //negro = scene->addEllipse(690,10,40,40,pen,brush2); //Se crea objeto para definir cuando el jugador llega a su objetivo
    circle = scene->addEllipse(posicionX,posicionY,40,40,pen,brush3); //Se crea objeto con propiedades senoidales
    magnitud = sqrt(pow(x1_pend - x2_pend, 2)+ pow(y1_pend - y2_pend, 2)); //Magnitud para movimiento del péndulo

    //Se crean 5 timer para tener un mejor manejo de los movimientos de los objetos
    timer = new QTimer(this);
    timer->start(15);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    timer3->start(1000);
    timerCron2 = new QTimer(this);
    timerCron2->start(1000);
    timerP2 = new QTimer(this);
    timerP2->start(15);

    //Se ocultan todos los botones, menos los principales para crear el menú de bienvenida
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
    ui->pushButton_14->hide();
    ui->horizontalSlider->hide();
}

MainWindow::~MainWindow() //Destructor para eliminar escena y los timer
{
    delete timer;
    delete timer2;
    delete timer3;
    delete timerCron2;
    delete timerP2;
    delete scene;
    delete ui;
}

void MainWindow::actualizar()//Función para evaluar las condiciones de impacto de player1 definidas en bordercoliision
{
        player1->actualizar(v_limit);
        borderCollision(player1->getEsf());

}

void MainWindow::actualizar2()//Función para evaluar las condiciones de impacto de player1 y player2 definidas en bordercoliision2
{
    if(multijugador==1){
        player2->actualizar(v_limit);
        borderCollision2(player1->getEsf(),player2->getEsf());
    }

}

void MainWindow::crono() //Función para llevar control del tiempo de Player1 y asignarlo al display
{
    cronometro-=1; //Se disminuye el tiempo a medida que el Timer completa los 1000 ms
    ui->lcdNumber->display(cronometro);
    ui->lcdNumber_2->display(level+1);
}

void MainWindow::crono2() //Función para llevar control del tiempo de Player2 y asignarlo al display
{
    cronometro2-=1; //Se disminuye el tiempo a medida que el Timer completa los 1000 ms
    ui->lcdNumber_3->display(cronometro2);
}

void MainWindow::borderCollision(mete *b) //Condiciones de impacto para player1
{   int z=5;QBrush brush4(Qt::red);//Propiedades de la Elipse
    if(b->getPX()<b->getR()){ //Condicion para no sobrepasar el eje X negativo
        b->set_vel(-1*(0+(rand()%z))*b->getVX(),b->getVY(),b->getR(),b->getPY());//Se cambia la dirección y se le asigna un coeficiente de restitución aleatorio
    }
    if(b->getPX()>h_limit-b->getR()){ //Condicion para no sobrepasar el eje X positivo
        b->set_vel(-1*(0+(rand()%z))*b->getVX(),b->getVY(),h_limit-b->getR(),b->getPY());
    }
    if(b->getPY()<b->getR()){ //Condicion para no sobrepasar el eje Y positivo
        b->set_vel(b->getVX(),-1*(0+(rand()%z))*b->getVY(),b->getPX(),b->getR());
    }
    if(b->getPY()>v_limit-b->getR()){//Condicion para no sobrepasar el eje Y negativo
        b->set_vel(b->getVX(),-1*(0+(rand()%z))*b->getVY(),b->getPX(),v_limit-b->getR());
    }

    if(posicionX>h_limit-190){ //Condición para límites del circulo senoidal
        velocidadX=7;
    }
    if(posicionX<-150){ //Condición para límites del circulo senoidal
        velocidadX=-7;
    }
    if(posicion2X>h_limit-190){ //Condición para límites del segundo circulo senoidal
        velocidad2X=(7+(rand()%12));
    }
    if(posicion2X<-150){ //Condición para límites del segundo circulo senoidal
        velocidad2X=-(5+(rand()%11));
    }
    if(player1->collidesWithItem(pend)){ //Si se colisiona con el pendulo regresa a la posición inicial
        b->set_vel(0,0,800,-10);
    }
    if(player1->collidesWithItem(pend2)){ //Si se colisiona con el pendulo2 regresa a la posición inicial
        b->set_vel(0,0,800,-10);
    }
    if(player1->collidesWithItem(circle)){ //Si se colisiona con el circulo regresa a la posición inicial
        b->set_vel(0,0,800,-10);
    }
    for(int i=0;i<monedas.size();i++)// Ciclo para remover las monedas en caso de colisión
    {
        if(player1->collidesWithItem(monedas.at(i))){ //si hay colisiones, elimina el objeto de la lista
            scene->removeItem(monedas.at(i));
            monedas.removeAt(i);
            cronometro+=xTT;
        }
    }
    if(bandera==2){ //Si la bandera se activa, es decir que se está en el nivel 2, entonces se evalua la colision con el circutio senoidal2
        if(player1->collidesWithItem(circle2)){
            b->set_vel(0,0,800,-10);
        }
    }
    if(bandera==3){ //si la bandera se activa, se agrega colision con el senoidal2 y adicional con los muros, regresando a la posicion inicial
        if(player1->collidesWithItem(circle2)){
            b->set_vel(0,0,800,-10);
        }
        for(auto it=muro.begin();it!=muro.end();it++)
        {
            if(player1->collidesWithItem(*it)){ //si hay colisiones, asigna nueva posición al objeto
                b->set_vel(0,0,800,-10);
            }
        }
    }
    if(multijugador==0){ //bandera para saber el modo de jugador
        if(player1->collidesWithItem(negro) || player1->collidesWithItem(negro2)){ //Se evaluan las condiciones de en que el objeto logra llegar al objetivo para así avanzar de nivel
            level+=1; //aumentamos de nivel
            b->set_vel(0,0,800,400); //regresamos a la posición inicial
            for(int i=0;i<muro.size();i++) //Remover todos los muros
            {
                scene->removeItem(muro.at(i));
                muro.removeAt(i);
            }
            timer->stop();//detenemos los timers
            timer2->stop();
            timer3->stop();
            if(level==1){
                message.setText("PASASTE A LA SEGUNDA GALAXIA!!"); //mensaje alertando del siguiente nivel
                message.setInformativeText("");
                message.exec();
                scene->setBackgroundBrush(QBrush(QImage(":/images/universo3.jpg")));//cambiamos fondos para diferenciar galaxias
                bandera=2;
                circle2 = scene->addEllipse(posicion2X,posicion2Y+250,40,40,pen,brush4);//se agrega el segundo circulo senoidal
                for(int i=0;i<muro.size();i++) //Remover todos los muros
                {
                    scene->removeItem(muro.at(i)); //si hay colisiones, elimina el objeto de la lista
                    muro.removeAt(i);
                }
                for(int i=0;i<muro.size();i++) //Remover todos los muros
                {
                    scene->removeItem(muro.at(i)); //si hay colisiones, elimina el objeto de la lista
                    muro.removeAt(i);
                }
                muro.append(new muros(60,60,-470,-180)); //luego los volvemos agregar pero con uno adicional y en diferente posición
                muro.append(new muros(60,60,-120,-280));
                muro.append(new muros(60,60,-290,-340));
                muro.append(new muros(60,60,-290,-50));

                for(auto it=muro.begin();it!=muro.end();it++) //ciclo para añadir cada elemento de la lista a la escena
                {
                    scene->addItem(*it);
                }

                timer->start(15);//Comendzamos los timer
                timer2->start(difficulty-1); //este timer maneja todos los enemigos, de esta forma al inicio de la partida difficulty recibe un valor que el usuario escoja, asi se varia la dificultad
                timer3->start(1000);
                delete negro;
                QBrush brush2(Qt::black);
                negro = scene->addEllipse(10,400,40,40,pen,brush2);
                //negro = scene->addEllipse(690,10,40,40,pen,brush2);

            }
            if(level==2){
                message.setText("PASASTE A LA TERCERA GALAXIA!!");
                message.setInformativeText("");
                message.exec();
                bandera+=1;
                scene->setBackgroundBrush(QBrush(QImage(":/images/universo4.jpg"))); //Cambiamos fondo de pantalla
                for(int i=0;i<muro.size();i++) //Remover todos los muros
                {
                    scene->removeItem(muro.at(i));
                    muro.removeAt(i);
                }
                for(int i=0;i<muro.size();i++) //Remover todos los muros
                {
                    scene->removeItem(muro.at(i));
                    muro.removeAt(i);
                }
                muro.append(new muros(20,170,-70,-60)); //luego los volvemos agregar pero con uno adicional y en diferente posición
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
                timer2->start(difficulty-2);
                timer3->start(1000);
                delete negro;
                QBrush brush2(Qt::black);
                negro2 = scene->addEllipse(10,10,40,40,pen,brush2);
                negro = scene->addEllipse(10,400,40,40,pen,brush2);
            }
            if(level==3){
                message.setText("FELICITACIONES, LOGRASTE ESCAPAR DE LAS GALAXIA!!");//finaliza partida
                message.setInformativeText("");
                message.exec();
                scene->removeItem(player1); //se remueve el player1


            }
        }
    }
    for(auto it=muro.begin();it!=muro.end();it++) //Ciclo para colisiones con muros
    {

        if(player1->collidesWithItem(*it)){ //Si colisiona se le multiplica -1 a la velocidad actual, así se cambia sentido de movimiento
            b->set_vel(-1*b->getVX(),-1*b->getVY(),b->getPX(),b->getPY());
        }
    }

    if(cronometro==0){ //Se evalua si finaliza el tiempo del player1 para acabar la partida
        scene->removeItem(player1);
        timer->stop();
        timer2->stop();
        timer3->stop();
        timerCron2->stop();
        timerP2->stop();
        message.setText("PERDISTE!! EL TIEMPO HA FINALIZADO PARA "+name);
        message.setInformativeText("");
        message.exec();
        cronometro=TT;
    }
    if(cronometro2==0){ //Se evalua si finaliza el tiempo del player2 para acabar la partida
        scene->removeItem(player2);
        timer->stop();
        timer2->stop();
        timer3->stop();
        timerCron2->stop();
        timerP2->stop();
        message.setText("PERDISTE!! EL TIEMPO HA FINALIZADO PARA "+name2);
        message.setInformativeText("");
        message.exec();
        cronometro2=TT;

    }
}

void MainWindow::borderCollision2(mete *b, mete *c) //Función para condiciones de colisión en caso de multiplayer, semejantes a las anteriores
{   int z=5;QBrush brush4(Qt::red);
    //player1
    if(multijugador==1){
    if(b->getPX()<b->getR()){ //Condiciones de impacto player1
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
    if(c->getPX()<c->getR()){ //Condiciones de impacto player2
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

    for(int i=0;i<monedas.size();i++)
    {
        if(player1->collidesWithItem(monedas.at(i))){
            scene->removeItem(monedas.at(i));
            monedas.removeAt(i);
            contmon+=1;
            cronometro+=xTT;
        }
    }

    for(int i=0;i<monedas.size();i++)
    {
        if(player2->collidesWithItem(monedas.at(i))){
            scene->removeItem(monedas.at(i));
            monedas.removeAt(i);
            contmon+=1;
            cronometro2+=xTT;
        }
    }

//    if(multijugador==0){
//        if(player1->collidesWithItem(negro)){
//            level+=1;
//            b->set_vel(-1*b->getVX(),-1*b->getVY(),800,400);
//            timer->stop();
//            timer2->stop();
//            timer3->stop();
//            if(level==1){
//                message.setText("PASASTE A LA SEGUNDA GALAXIA!!");
//                message.setInformativeText("");
//                message.exec();
//                bandera=2;
//                circle2 = scene->addEllipse(posicion2X,posicion2Y+250,40,40,pen,brush4);
//                timer->start(15);
//                timer2->start(difficulty-1);
//                timer3->start(1000);
//            }
//            if(level==2){
//                message.setText("PASASTE A LA TERCERA GALAXIA!!");
//                message.setInformativeText("");
//                message.exec();
//                bandera+=1;
//                for(int i=0;i<muro.size();i++)
//                {
//                    scene->removeItem(muro.at(i));
//                    muro.removeAt(i);
//                }
//                muro.append(new muros(20,170,-70,-60));
//                muro.append(new muros(220,20,-180,-60));
//                muro.append(new muros(220,20,-70,-340));
//                muro.append(new muros(20,170,-600,-120));
//                muro.append(new muros(220,20,-460,-390));
//                muro.append(new muros(220,20,-200,-240));
//                for(auto it=muro.begin();it!=muro.end();it++)
//                {
//                    scene->addItem(*it);
//                }
//                timer->start(15);
//                timer2->start(difficulty-2);
//                timer3->start(1000);
//            }
//            if(level==3){
//                message.setText("FELICITACIONES, LOGRASTE ESCAPAR DE LAS GALAXIA!!");
//                message.setInformativeText("");
//                message.exec();

//            }
//        }
//    }

    if(multijugador==1){ //Condicional en caso de alcanzar el agujero negro para player1
        if(player1->collidesWithItem(negro) || player1->collidesWithItem(negro2)){
            b->set_vel(-1*b->getVX(),-1*b->getVY(),800,400);
            timer->stop();
            timer3->stop();
            bandP1=true;
        }
        if(player2->collidesWithItem(negro) || player2->collidesWithItem(negro2)){//Condicional en caso de alcanzar el agujero negro para player1
            c->set_vel(-1*c->getVX(),-1*c->getVY(),800,400);
            timerP2->stop();
            timerCron2->stop();
            bandP2=true;
        }

        if(bandP1==true && bandP2==true){ //Si ambos alcanzan el agujero negro, continua el siguiente nivel
            timer2->stop();
            level+=1;

                    message.setText("CONTINUA LA SEGUNDA GALAXIA!!");
                    message.setInformativeText("");
                    message.exec();
                    bandera=2;
                    scene->setBackgroundBrush(QBrush(QImage(":/images/universo3.jpg")));
                    circle2 = scene->addEllipse(posicion2X,posicion2Y+250,40,40,pen,brush4);
                    timer->start(15);
                    timer2->start(difficulty-2);
                    timer3->start(1000);
                    timerP2->start(15);
                    timerCron2->start(1000);
                    bandP1=false;
                    bandP2=false;

        }

    }

    }
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    mete * b = player1->getEsf();


    if(multijugador==0){ //Teclas para movimiento player1
        if(event->key() == Qt::Key_D){
            b->set_vel(30,b->getVY(),b->getPX(),b->getPY());
        }
        if(event->key() == Qt::Key_A){
            b->set_vel(-30,b->getVY(),b->getPX(),b->getPY());
        }
        if(event->key() == Qt::Key_W){
            b->set_vel(b->getVX(),35,b->getPX(),b->getPY());
        }
    }
    else if(multijugador==1){ //Teclas para movimiento player1 y player2
        mete * c = player2->getEsf();

        if(event->key() == Qt::Key_D){
            b->set_vel(30,b->getVY(),b->getPX(),b->getPY());
        }
        if(event->key() == Qt::Key_A){
            b->set_vel(-30,b->getVY(),b->getPX(),b->getPY());
        }
        if(event->key() == Qt::Key_W){
            b->set_vel(b->getVX(),35,b->getPX(),b->getPY());
        }
        if(event->key() == Qt::Key_K){
            c->set_vel(30,c->getVY(),c->getPX(),c->getPY());
        }
        if(event->key() == Qt::Key_H){
            c->set_vel(-30,c->getVY(),c->getPX(),c->getPY());
        }
        if(event->key() == Qt::Key_U){
            c->set_vel(c->getVX(),35,c->getPX(),c->getPY());
        }
    }

}

void MainWindow::pendulo() //Función para el pendulo
{

    double angulo = asin((x1_pend ) / magnitud); //Angulo en radianes para
    double a_x = -G * sin(angulo); //Aceleración eje x
    static double vx = 0; //Velocidad eje x
    vx += a_x * tiempo; //Velocidad eje x en función del tiempo
    static double w = 0;
    w = vx / magnitud; //
    double ace_angulo = w / tiempo; //Cambio de angulo en funcion del tiepmpo
    angulo = angulo + w * tiempo  + (ace_angulo / 2 ) * tiempo * tiempo; //Angulo en función del tiempo
    x1_pend = magnitud * sin(angulo); //Posicion x
    y1_pend = magnitud * cos(angulo); //Posición Y
    pend->setPos(x1_pend, y1_pend); //Se asignan valores de posición al pendulo1
    pend2->setPos(x1_pend, y1_pend); //Se asignan valores de posición al pendulo2

}

void MainWindow::senoidal()
{
    acum+=0.01; //Sumatoria de todo el tiempo
    posicionX = posicionX - velocidadX*tiempo; //Velocidad en X en función del tiempo
    posicionY= 5*sin(2*3.1415*acum/2)+posicionY; //Posición en Y dada una amplitud
    circle->setPos(posicionX+150,posicionY+70); //Posiciones iniciales para el circulo


    if(bandera==2 || bandera==3){ //Al activarse la bandera, se agrega el circulo2
        acum2+=0.01;
        posicion2X = posicion2X - velocidad2X*tiempo;
        posicion2Y= -5*sin(2*3.1415*acum2/2)+posicion2Y;
        circle2->setPos(posicion2X+150,posicion2Y+80);}

}

void MainWindow::on_pushButton_clicked() //start
{
    if(multijugador==0){
        name=ui->lineEdit->text(); //A la variable name, llevamos lo ingresado por el player 1
        if(name==""){ //Si es vacio, le solicita que ingrese un usuario
            message.setText("INGRESE USUARIO PARA PLAYER 1");
            message.setInformativeText("");
            message.exec();
        }


        else{ //Se Oculta el menú principal
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
            ui->pushButton_14->hide();
            ui->horizontalSlider->hide();
            muro.append(new muros(20,170,-70,-60)); //Se define tamanio y posición de los rectangulos
            muro.append(new muros(220,20,-180,-60));
            muro.append(new muros(220,20,-70,-340));
            muro.append(new muros(20,170,-600,-120));
            muro.append(new muros(220,20,-460,-390));
            for(auto it=muro.begin();it!=muro.end();it++) //Ciclo para añadir cada uno de los muros a la escena
            {
                scene->addItem(*it);
            }
            player1 = new meteor(1); //Se crea nuestro personaje
            scene->addItem(player1); //Se agrega nuestro personaje a la escena
            timer2->start(difficulty); //Se asigna la dificultad seleccionada por el usuario

            connect(timer,SIGNAL(timeout()),this,SLOT(actualizar())); //Se conectan todos los timers
            connect(timer2,SIGNAL(timeout()),this,SLOT(pendulo()));
            connect(timer3,SIGNAL(timeout()),this,SLOT(crono()));
            connect(timer2,SIGNAL(timeout()),this,SLOT(senoidal()));
        }
    }
    if(multijugador==1){ //Funciona igual que la parte anterior, a diferencia que aquí se agrega el player2
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
            ui->pushButton_14->hide();
            ui->horizontalSlider->hide();
            player1 = new meteor(1); //Se crea y se añade ambos personajes a la escena
            scene->addItem(player1);
            player2 = new meteor(2);
            scene->addItem(player2);
            timer2->start(difficulty);

            muro.append(new muros(20,170,-70,-60));
            muro.append(new muros(220,20,-180,-60));
            muro.append(new muros(220,20,-70,-340));
            muro.append(new muros(20,170,-600,-120));
            muro.append(new muros(220,20,-460,-390));
            for(auto it=muro.begin();it!=muro.end();it++) //Ciclo para añadir cada uno de los muros a la escena
            {
                scene->addItem(*it);
            }

            connect(timer,SIGNAL(timeout()),this,SLOT(actualizar())); //Se inicializan todos los timers
            connect(timerP2,SIGNAL(timeout()),this,SLOT(actualizar2()));
            connect(timerCron2,SIGNAL(timeout()),this,SLOT(crono2()));
            connect(timer2,SIGNAL(timeout()),this,SLOT(pendulo()));
            connect(timer3,SIGNAL(timeout()),this,SLOT(crono()));
            connect(timer2,SIGNAL(timeout()),this,SLOT(senoidal()));

        }
    }
}

void MainWindow::on_pushButton_2_clicked() //sig in
{   //Se oculta y se muestran los botones de forma que permita registrar al usuario
    ui->lineEdit->show();
    ui->pushButton->show();
    ui->pushButton_2->hide();
    ui->pushButton_9->show();
    ui->textBrowser_6->show();
    ui->pushButton_14->show();
    ui->horizontalSlider->show();
}

void MainWindow::on_pushButton_3_clicked() //save
{
    mete * b = player1->getEsf(); //Se crea un puntero para manipular al objeto
    name = ui->lineEdit->text(); //Se obtiene el nombre del usuario registrado

    if(multijugador==0){

        string Nnames, posx, posy,cron,galaxy,difil,banderr; //Creamos String para guardar los datos leídos del archivo de texto

        ifstream Leer; //Variable para leer archivos de entrada
        ofstream Temp, Guardar; //Varibles para manejar archivos de salida
        Guardar.open("guardar.txt",ios::app);
        Leer.open("guardar.txt");
        Temp.open("temp.txt");

        bool encontrado=false;
        Leer>>Nnames;
        while(!Leer.eof()){ //Leemos la primera linea de texto
            Leer>>posx;
            Leer>>posy;
            Leer>>cron;
            Leer>>galaxy;
            Leer>>difil;
            Leer>>banderr;
            if(Nnames==name.toStdString()){ //Si el usuario encontrado es igual al registrado, procede a tomar los nuevos datos
                encontrado=true;
                Temp<<Nnames<<"    "<<b->getPX()<<"    "<<b->getPY()<<"    "<<cronometro<<"    "<<level+1<<"    "<<difficulty<<"    "<<bandera<<endl;
            }
            else{ //En caso de que no, guardar los datos actuales
                Temp<<Nnames<<"    "<<posx<<"    "<<posy<<"    "<<cron<<"    "<<galaxy<<"    "<<difil<<"    "<<banderr<<endl;
            }
            Leer>>Nnames;
        }
        if(!encontrado){ //Si el booleano es false, no hay registros guardados, por lo cual agrega el usuario nuevo con sus datos0.
            Temp<<name.toStdString()<<"    "<<b->getPX()<<"    "<<b->getPY()<<"    "<<cronometro<<"    "<<level+1<<"    "<<difficulty<<"    "<<bandera<<endl;
        }
        Leer.close();
        Temp.close();
        Guardar.close();

        remove("guardar.txt");
        rename("temp.txt","guardar.txt");
    }
    if(multijugador==1){
        mete * c = player2->getEsf();
    }
}

void MainWindow::on_pushButton_4_clicked() //load
{
    mete * b = player1->getEsf(); //Se crea un puntero para manejar el objeto
    name = ui->lineEdit->text(); //Se obtiene datos del nombre del registro del usuario
    QBrush brush4(Qt::red); //Color para una Elipse

    if(multijugador==0){ //Se evalua si es single o multiplayer

        string Nnames, posx, posy,cron,galaxy,difil,banderr; //Creamos String para guardar los datos leídos del archivo de texto

        ifstream Leer; //Para manipular el archivo en modo lectura
        ofstream Guardar;
        Guardar.open("guardar.txt",ios::app);
        Leer.open("guardar.txt");


        bool encontrado=false;
        Leer>>Nnames;
        while(!Leer.eof()){ //Si e nombre coincide, guardamos todos los datos en cada variable
            Leer>>posx;
            Leer>>posy;
            Leer>>cron;
            Leer>>galaxy;
            Leer>>difil;
            Leer>>banderr;
            if(Nnames==name.toStdString()){
                encontrado=true;
                if((level+1)==1){
                    if(stoi(galaxy)==1){ //Asignamos cada una de las variables al objeto y a la configuración de la partida
                        b->set_vel(0,0,stof(posx),stof(posy));
                        cronometro=stoi(cron); //Asignamos el tiempo
                        difficulty=stoi(difil); //Asignamos dificultad
                        level=stoi(galaxy)-1; //Asignamos nivel
                        bandera=stoi(banderr);
                        scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
                        message.setText("PAARTIDA CARGADA CORRECTAMENTE CON USUARIO "+name);
                        message.setInformativeText("");
                        message.exec();
                    }
                    if(stoi(galaxy)==2){
                        b->set_vel(0,0,stof(posx),stof(posy));
                        cronometro=stoi(cron);
                        difficulty=stoi(difil);
                        level=stoi(galaxy)-1;
                        bandera=stoi(banderr);
                        timer2->start(difficulty-1);
                        for(int i=0;i<muro.size();i++)
                        {
                            scene->removeItem(muro.at(i));
                            muro.removeAt(i);
                        }
                        for(int i=0;i<muro.size();i++)
                        {
                            scene->removeItem(muro.at(i));
                            muro.removeAt(i);
                        }
                        for(int i=0;i<muro.size();i++)
                        {
                            scene->removeItem(muro.at(i));
                            muro.removeAt(i);
                        }
                        muro.append(new muros(60,60,-470,-180)); //luego los volvemos agregar pero con uno adicional y en diferente posición
                        muro.append(new muros(60,60,-120,-280));
                        muro.append(new muros(60,60,-290,-340));
                        muro.append(new muros(60,60,-290,-50));
                        for(auto it=muro.begin();it!=muro.end();it++)
                        {
                            scene->addItem(*it);
                        }
                        scene->setBackgroundBrush(QBrush(QImage(":/images/universo3.jpg")));
                        circle2 = scene->addEllipse(posicion2X,posicion2Y+250,40,40,pen,brush4);
                        message.setText("PAARTIDA CARGADA CORRECTAMENTE CON USUARIO "+name);
                        message.setInformativeText("");
                        message.exec();

                    }
                    if(stoi(galaxy)==3){
                        b->set_vel(0,0,stof(posx),stof(posy));
                        cronometro=stoi(cron);
                        difficulty=stoi(difil);
                        level=stoi(galaxy)-1;
                        bandera=stoi(banderr);
                        timer2->start(difficulty-2);
                        scene->setBackgroundBrush(QBrush(QImage(":/images/universo4.jpg")));
                        circle2 = scene->addEllipse(posicion2X,posicion2Y+250,40,40,pen,brush4);
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
                        QBrush brush2(Qt::black);
                        negro2 = scene->addEllipse(10,10,40,40,pen,brush2);
                        message.setText("PAARTIDA CARGADA CORRECTAMENTE CON USUARIO "+name);
                        message.setInformativeText("");
                        message.exec();
                    }
                }
                else if((level+1)==2){
                    if(stoi(galaxy)==1){
                        b->set_vel(0,0,stof(posx),stof(posy));
                        cronometro=stoi(cron);
                        difficulty=stoi(difil);
                        level=stoi(galaxy)-1;
                        bandera=stoi(banderr);
                        scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
                        delete circle2;
                        message.setText("PAARTIDA CARGADA CORRECTAMENTE CON USUARIO "+name);
                        message.setInformativeText("");
                        message.exec();
                    }
                    if(stoi(galaxy)==2){
                        b->set_vel(0,0,stof(posx),stof(posy));
                        cronometro=stoi(cron);
                        difficulty=stoi(difil);
                        level=stoi(galaxy)-1;
                        bandera=stoi(banderr);
                        for(int i=0;i<muro.size();i++)
                        {
                            scene->removeItem(muro.at(i));
                            muro.removeAt(i);
                        }
                        for(int i=0;i<muro.size();i++)
                        {
                            scene->removeItem(muro.at(i));
                            muro.removeAt(i);
                        }
                        for(int i=0;i<muro.size();i++)
                        {
                            scene->removeItem(muro.at(i));
                            muro.removeAt(i);
                        }
                        muro.append(new muros(60,60,-470,-180)); //luego los volvemos agregar pero con uno adicional y en diferente posición
                        muro.append(new muros(60,60,-120,-280));
                        muro.append(new muros(60,60,-290,-340));
                        muro.append(new muros(60,60,-290,-50));
                        for(auto it=muro.begin();it!=muro.end();it++)
                        {
                            scene->addItem(*it);
                        }
                        scene->setBackgroundBrush(QBrush(QImage(":/images/universo3.jpg")));
                        timer2->start(difficulty-1);
                        message.setText("PAARTIDA CARGADA CORRECTAMENTE CON USUARIO "+name);
                        message.setInformativeText("");
                        message.exec();
                    }
                    if(stoi(galaxy)==3){
                        b->set_vel(0,0,stof(posx),stof(posy));
                        cronometro=stoi(cron);
                        difficulty=stoi(difil);
                        level=stoi(galaxy)-1;
                        bandera=stoi(banderr);
                        scene->setBackgroundBrush(QBrush(QImage(":/images/universo4.jpg")));
                        timer2->start(difficulty-2);
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
                        QBrush brush2(Qt::black);
                        negro2 = scene->addEllipse(10,10,40,40,pen,brush2);
                        message.setText("PAARTIDA CARGADA CORRECTAMENTE CON USUARIO "+name);
                        message.setInformativeText("");
                        message.exec();
                    }

                }
                else{
                    if(stoi(galaxy)==1){
                        b->set_vel(0,0,stof(posx),stof(posy));
                        cronometro=stoi(cron);
                        difficulty=stoi(difil);
                        level=stoi(galaxy)-1;
                        bandera=stoi(banderr);
                        scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
                        delete circle2;
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
                        QBrush brush2(Qt::black);
                        negro2 = scene->addEllipse(10,10,40,40,pen,brush2);
                        negro = scene->addEllipse(10,10,40,40,pen,brush2);
                        message.setText("PAARTIDA CARGADA CORRECTAMENTE CON USUARIO "+name);
                        message.setInformativeText("");
                        message.exec();
                    }
                    if(stoi(galaxy)==2){
                        b->set_vel(0,0,stof(posx),stof(posy));
                        cronometro=stoi(cron);
                        difficulty=stoi(difil);
                        level=stoi(galaxy)-1;
                        bandera=stoi(banderr);
                        scene->setBackgroundBrush(QBrush(QImage(":/images/universo3.jpg")));
                        timer2->start(difficulty-1);
                        for(int i=0;i<muro.size();i++)
                        {
                            scene->removeItem(muro.at(i));
                            muro.removeAt(i);
                        }
                        for(int i=0;i<muro.size();i++)
                        {
                            scene->removeItem(muro.at(i));
                            muro.removeAt(i);
                        }
                        for(int i=0;i<muro.size();i++)
                        {
                            scene->removeItem(muro.at(i));
                            muro.removeAt(i);
                        }
                        muro.append(new muros(60,60,-470,-180)); //luego los volvemos agregar pero con uno adicional y en diferente posición
                        muro.append(new muros(60,60,-120,-280));
                        muro.append(new muros(60,60,-290,-340));
                        muro.append(new muros(60,60,-290,-50));
                        for(auto it=muro.begin();it!=muro.end();it++)
                        {
                            scene->addItem(*it);
                        }
                        scene->removeItem(negro2);

                        message.setText("PAARTIDA CARGADA CORRECTAMENTE CON USUARIO "+name);
                        message.setInformativeText("");
                        message.exec();
                    }
                    if(stoi(galaxy)==3){
                        b->set_vel(0,0,stof(posx),stof(posy));
                        cronometro=stoi(cron);
                        difficulty=stoi(difil);
                        level=stoi(galaxy)-1;
                        bandera=stoi(banderr);
                        QBrush brush2(Qt::black);
                        negro2 = scene->addEllipse(10,10,40,40,pen,brush2);
                        scene->setBackgroundBrush(QBrush(QImage(":/images/universo4.jpg")));
                        timer2->start(difficulty-2);
                        message.setText("PAARTIDA CARGADA CORRECTAMENTE CON USUARIO "+name);
                        message.setInformativeText("");
                        message.exec();
                    }
                }
            }
            Leer>>Nnames;
        }
        if(!encontrado){
            message.setText("NO SE TIENE PARTIDA GUARDADA CON EL USUARIO "+name);
            message.setInformativeText("");
            message.exec();
        }
        Leer.close();

        Guardar.close();
    }


    if(multijugador==1){


    }
}

void MainWindow::on_pushButton_5_clicked()
{

}

void MainWindow::on_pushButton_6_clicked() //play
{
    //Iniciamos timers y ocultamos botones
    timer->start(15);
    timer2->start(difficulty);
    timer3->start(1000);
    timerCron2->start(1000);
    timerP2->start(15);
    ui->pushButton_6->hide();
    ui->pushButton_7->show();

}

void MainWindow::on_pushButton_7_clicked() //stop
{
    //Pausamos timers y ocultamos botones
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
    //Se activan opciones para multijugador
    ui->pushButton_10->show();
    ui->pushButton_9->hide();
    ui->textBrowser_7->show();
    ui->lineEdit_2->show();
    multijugador=1;
}

void MainWindow::on_pushButton_10_clicked() //single
{
    //Se activan opciones para un jugador
    ui->pushButton_10->hide();
    ui->pushButton_9->show();
    ui->textBrowser_7->hide();
    ui->lineEdit_2->hide();
    multijugador=0;
}

void MainWindow::on_pushButton_11_clicked()//restart
{
    //Según en el nivel en que se esté ubicado, asignamos las respectivas variables para comenzar de nuevo desde el nivel 1
    mete *b = player1->getEsf();
    if(level==0){
        scene->addItem(player1);
        cronometro=TT;
        b->set_vel(0,0,800,-10);
        posicionX=0;
        posicionY=0;
        acum=0;

        timer->start(15);
        timer2->start(difficulty);
        timer3->start(1000);
        timerCron2->start(1000);
        timerP2->start(15);

        for(int i=0;i<monedas.size();i++)// Ciclo para remover las monedas en caso de colisión
        {
            scene->removeItem(monedas.at(i));
            monedas.removeAt(i);
        }
        monedas.append(new moneda(-35,-35,525,360));
        monedas.append(new moneda(-35,-35,225,200));
        monedas.append(new moneda(-35,-35,500,140));
        monedas.append(new moneda(-35,-35,160,40));
        monedas.append(new moneda(-35,-35,30,360));
        for(auto it=monedas.begin();it!=monedas.end();it++){ //Ciclo para añadir cada una de las monedas a la escena
            scene->addItem(*it);
        }
        scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));



    }
    if(level==1){
        scene->addItem(player1);
        bandera=0;
        delete circle2;
        cronometro=TT;
        b->set_vel(0,0,800,-10);

        timer->start(15);
        timer2->start(difficulty);
        timer3->start(1000);
        timerCron2->start(1000);
        timerP2->start(15);

        posicionX=0;velocidadX=-7;
        posicionY=0;
        posicion2X=0;
        posicion2Y=0;
        for(int i=0;i<muro.size();i++) //Remover todos los muros
        {
            scene->removeItem(muro.at(i));
            muro.removeAt(i);
        }
        for(int i=0;i<muro.size();i++) //Remover todos los muros
        {
            scene->removeItem(muro.at(i));
            muro.removeAt(i);
        }
        for(int i=0;i<muro.size();i++) //Remover todos los muros
        {
            scene->removeItem(muro.at(i));
            muro.removeAt(i);
        }

        for(int i=0;i<monedas.size();i++)// Ciclo para remover las monedas en caso de colisión
        {
            scene->removeItem(monedas.at(i));
            monedas.removeAt(i);
        }
        muro.append(new muros(20,170,-70,-60));
        muro.append(new muros(220,20,-180,-60));
        muro.append(new muros(220,20,-70,-340));
        muro.append(new muros(20,170,-600,-120));
        muro.append(new muros(220,20,-460,-390));
        for(auto it=muro.begin();it!=muro.end();it++) //Ciclo para añadir cada uno de los muros a la escena
        {
            scene->addItem(*it);
        }
        monedas.append(new moneda(-35,-35,525,360));
        monedas.append(new moneda(-35,-35,225,200));
        monedas.append(new moneda(-35,-35,500,140));
        monedas.append(new moneda(-35,-35,160,40));
        monedas.append(new moneda(-35,-35,30,360));
        for(auto it=monedas.begin();it!=monedas.end();it++){ //Ciclo para añadir cada una de las monedas a la escena
            scene->addItem(*it);
        }
        scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
        acum=0;acum2=0;level=0;

        delete negro;
        QBrush brush2(Qt::black);
        negro = scene->addEllipse(10,10,40,40,pen,brush2);
    }
    if(level==2 || level==3 || level ==4){
        bandera=0;
        delete circle2;
        cronometro=TT;

        posicionX=0;velocidadX=-7;
        posicionY=0;
        posicion2X=0;
        posicion2Y=0;

        timer->start(15);
        timer2->start(difficulty);
        timer3->start(1000);
        timerCron2->start(1000);
        timerP2->start(15);
        scene->addItem(player1);

        scene->setBackgroundBrush(QBrush(QImage(":/images/universo2.jpg")));
        acum=0;acum2=0;level=0;
        for(int i=0;i<muro.size();i++) //Remover todos los muros
        {
            scene->removeItem(muro.at(i));
            muro.removeAt(i);
        }
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
        for(auto it=muro.begin();it!=muro.end();it++)
        {
            scene->addItem(*it);
        }
        for(auto it=muro.begin();it!=muro.end();it++)
        {
            scene->addItem(*it);
        }
        for(int i=0;i<monedas.size();i++)// Ciclo para remover las monedas en caso de colisión
        {
            scene->removeItem(monedas.at(i));
            monedas.removeAt(i);
        }
        monedas.append(new moneda(-35,-35,525,360));
        monedas.append(new moneda(-35,-35,225,200));
        monedas.append(new moneda(-35,-35,500,140));
        monedas.append(new moneda(-35,-35,160,40));
        monedas.append(new moneda(-35,-35,30,360));
        for(auto it=monedas.begin();it!=monedas.end();it++){ //Ciclo para añadir cada una de las monedas a la escena
            scene->addItem(*it);
        }

        b->set_vel(0,0,800,-10);
        delete negro;
        delete negro2;
        QBrush brush2(Qt::black);
        negro = scene->addEllipse(10,10,40,40,pen,brush2);
        negro2 = scene->addEllipse(10,10,40,40,pen,brush2);
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //Recibimos el valor variable de la dificultad para luego llevarlo al constructor
    difficulty=value;
}


