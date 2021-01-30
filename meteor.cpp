#include "meteor.h"

meteor::meteor(int x):escala(0.8)
{   play =x;
    float posx,posy,velx,vely,mass,r,K,e;

    posx = 800;// 32;
    posy = 400;//150;
    r = 15;
    mass = 50;
    velx = 0;
    vely = 0;
    K = 0;
    e = 0+(rand()%3);


    esf = new mete(posx,posy,velx,vely,mass,r,K,e);


}

meteor::~meteor()
{
    delete esf;

}

QRectF meteor::boundingRect() const
{
    return QRectF(-1*escala*esf->getR(),-1*escala*esf->getR(),2*escala*esf->getR(),2*escala*esf->getR());

}

void meteor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(play==1){
        painter->setBrush(Qt::green);
        painter->drawEllipse(boundingRect());
    }
    if(play==2){
        painter->setBrush(Qt::white);
        painter->drawEllipse(boundingRect());
    }
}

void meteor::setEscala(float s)
{
    escala = s;
}

void meteor::actualizar(float v_lim)
{
    esf->actualizar();
    setPos(esf->getPX(),v_lim-esf->getPY());
}


mete *meteor::getEsf()
{
    return esf;
}


