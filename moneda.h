#ifndef MONEDA_H
#define MONEDA_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class moneda: public QObject, public QGraphicsItem
{
    int w,h;
    int posx, posy;
public:
    moneda(int w_, int h_, int x, int y);
    explicit moneda(QObject *parent2 = nullptr);
    //moneda(int r_, int x, int y);//

    QTimer * timer2;
    QPixmap *pixmap2;

    float filas, columnas, ancho, alto;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

signals:

public slots:
    void Actualizacion2();

};

#endif // MONEDA_H
