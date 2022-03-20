#ifndef BULLET1_H
#define BULLET1_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>
#include <QDebug>

#include "enemiespreset1.h"
#include "enemiespreset2.h"
#include "enemiespreset3.h"
#include "enemiespreset4.h"
#include "enemiespreset5.h"
#include "boss.h"


class Bullet1 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet1(QObject *parent = 0);
    ~Bullet1();

signals:
    void signalKill(QGraphicsItem*item);
    void signalBossHit();
//    void signalKill4();

public slots:
    void slotBulletCreate(int BaseBulletWidth,int BaseBulletHeight,int BulletHeight);
private slots:
    void slotBulletFly();

private:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void DeleteBullet();
    QRectF boundingRect() const;
    void  paintBullet();
    int BaseBulletWidth;
    int BaseBulletHeight;
    int BulletHeight;
    int gr = 0;
    int DeleteLimiter = 1;


    int BulletHitIndicator;

    bool CreateBullet;
    bool CreateLock;

    QTimer * BulletTimer;

    QGraphicsItem * BulletItem;
};

#endif
