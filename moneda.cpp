#include "moneda.h"

moneda::moneda(int w_, int h_, int x, int y)
{
    w = w_;
    h = h_;
    posx = x;
    posy = y;

    timer2 =new QTimer();
    filas =0;
    columnas =0;

    pixmap2 = new QPixmap(":/images/PC Computer.png");

    //dimensiones imagen
    ancho = 70;
    alto = 100;

    timer2->start(100);
    connect(timer2,&QTimer::timeout, this,&moneda::Actualizacion2);
    setPos(posx,posy);
}

QRectF moneda::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void moneda::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2, -alto/2,*pixmap2,columnas,filas,ancho,alto);
    setScale(0.32);
}



void moneda::Actualizacion2()
{
    columnas += 70;
    if(columnas >=280){
        columnas =0;
    }
    filas += 100;
    if(filas >=400){
        filas =0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}
