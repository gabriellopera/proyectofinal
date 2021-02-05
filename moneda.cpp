#include "moneda.h"

moneda::moneda(int w_, int h_, int x, int y)
{
    //se reciben valores para el objeto y se definen valoes
    w = w_;
    h = h_;
    posx = x;
    posy = y;
    timer2 =new QTimer();
    filas =0;
    columnas =0;
    pixmap2 = new QPixmap(":/images/PC Computer.png"); // Ruta de imagen
    //dimensiones imagen
    ancho = 70;
    alto = 100;
    //Conectamos los timers
    timer2->start(100);
    connect(timer2,&QTimer::timeout, this,&moneda::Actualizacion2);
    setPos(posx,posy);
}

QRectF moneda::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto); //tamano de nuestro sprite
}

void moneda::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2, -alto/2,*pixmap2,columnas,filas,ancho,alto);//Se define las dimensiones a tomar del sprite
    setScale(0.32);//escala para acoplar a la escena
}



void moneda::Actualizacion2()
{
    //Se actualiza para ir variando la imagen para el Sprite de acuerdo a las dimensiones en pixeles de la imagen
    columnas += 70;
    if(columnas >=280){
        columnas =0;
    }
    filas += 100;
    if(filas >=400){
        filas =0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto); //actualizamos, de esta forma se ve fluido el movimiento del Sprite
}
