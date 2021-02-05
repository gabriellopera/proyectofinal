#include "meteor.h"

meteor::meteor(int x):escala(0.8)
{   play = x; //bandera para la funcion paint saber que color asignarle
    float posx,posy,velx,vely,mass,r,K,e; //variables

    //Variables iniciales bajo las cuales iniciará el objeto
    posx = 800;//posicion en x inicial
    posy = 400;//posicion en y inicial
    r = 15;//radio
    mass = 50;//masa
    velx = 0;//velocidad en x inicial
    vely = 0;//velocidad en y inicial
    K = 0.2;//coeficiente de fricción
    e = (0+(rand()%4)); //Coeficiente de restitución es aleatorio, de esta forma se hace el juego dinámico
    esf = new mete(posx,posy,velx,vely,mass,r,K,e); //Se crea el objeto


}

meteor::~meteor() //eliminar nuestro objeto
{
    delete esf;

}

QRectF meteor::boundingRect() const
{
    return QRectF(-1*escala*esf->getR(),-1*escala*esf->getR(),2*escala*esf->getR(),2*escala*esf->getR()); //Tamano para nuestro circulo de acuerdo a la escala

}

void meteor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Dependiendo de los jugadores,se crearan los objeto con diferente color
    if(play==1){
        painter->setBrush(Qt::green);
        painter->drawEllipse(boundingRect());
    }
    if(play==2){
        painter->setBrush(Qt::white);
        painter->drawEllipse(boundingRect());
    }
}

void meteor::setEscala(float s) //escala para acoplarse a la escena
{
    escala = s;
}

void meteor::actualizar(float v_lim)
{
    //Actualizamos la posición del objeto

    esf->actualizar();
    setPos(esf->getPX(),v_lim-esf->getPY());
}


mete *meteor::getEsf() //obtener valores de nuestro objeto
{
    return esf;
}


