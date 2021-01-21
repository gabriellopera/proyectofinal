#include "meteor.h"

#include <QDebug>

meteor::meteor(int r_, int x, int y)
{
    r = r_;
    posx = x;
    posy = y;
    setPos(posx,posy);
}
meteor::meteor(QObject *parent) : QObject(parent)
{
    timer =new QTimer();
    filas =25;
    columnas =0;
    pixmap = new QPixmap(":/images/fuego.png");
    //dimensiones imagen
    ancho = 66.33;
    alto = 30;
    timer->start(100);
    connect(timer,&QTimer::timeout, this,&meteor::Actualizacion);
    setPos(250,250);

}

void meteor::Actualizacion()
{
    columnas += 66.33;
    if(columnas >=132.66){
        columnas =0;
    }
    filas += 30;
    if(filas >=145){
        filas =25;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}

QRectF meteor::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void meteor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2, -alto/2,*pixmap,columnas,filas,ancho,alto);
    //setScale(1);
}

int meteor::getR() const
{
    return r;
}

void meteor::setR(int value)
{
    r = value;
}

int meteor::getPosx() const
{
    return posx;
}

void meteor::setPosx(int value)
{
    posx = value;
}

int meteor::getPosy() const
{
    return posy;
}

void meteor::setPosy(int value)
{
    posy = value;
}

void meteor::up()
{
    posy -= 1*velocidad;
    setPos(posx, posy);
}

void meteor::down()
{
    posy += 1*velocidad;
    setPos(posx, posy);
}

void meteor::left()
{
    posx -= 1*velocidad;
    setPos(posx, posy);
}

void meteor::right()
{
    posx += 1*velocidad;
    setPos(posx, posy);
}


