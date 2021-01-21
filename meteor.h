#ifndef METEOR_H
#define METEOR_H


#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>

class meteor : public QObject, public QGraphicsItem
{
    Q_OBJECT
    int r;//
    int posx=20, posy=20;//
    int velocidad = 10;//

public:
    explicit meteor(QObject *parent = nullptr);
    meteor(int r_, int x, int y);//
    QTimer * timer;
    QPixmap *pixmap;
    int getR() const;
    void setR(int radio);
    int getPosx() const;
    void setPosx(int px);
    int getPosy() const;
    void setPosy(int py);

    float filas, columnas, ancho, alto;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void up();
    void down();
    void left();
    void right();
    void move();


signals:

public slots:
    void Actualizacion();

};

#endif // METEOR_H
