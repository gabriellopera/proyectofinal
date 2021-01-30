#ifndef CUERPOGRAF_H
#define CUERPOGRAF_H

#include <QPainter>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "mete.h"
#include <stdlib.h>
#include <time.h>
#include <QTimer>
#include <QPixmap>

class meteor: public QGraphicsItem
{
public:
    QTimer * timer;
    QPixmap *pixmap;
    meteor(int x);
    ~meteor();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void setEscala(float s);
    void actualizar(float v_lim);
    mete *getEsf();

    float filas, columnas, ancho, alto;

private:
    mete * esf, *esf2;
    float escala;
    int play;

signals:

public slots:
    void Actualizacion();
};

#endif // CUERPOGRAF_H
