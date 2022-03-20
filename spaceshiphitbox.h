#ifndef SPACESHIPHITBOX_H
#define SPACESHIPHITBOX_H

#include "startmenu.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

class SpaceShipHitbox: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit SpaceShipHitbox(QObject*parent = 0);
    ~SpaceShipHitbox();

public slots:
    void slotSpaceship();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;
};

#endif
