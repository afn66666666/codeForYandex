#ifndef BULLET2_H
#define BULLET2_H

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

class Bullet2 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet2(QObject *parent = 0);
    ~Bullet2();

signals:
    void signalKill(QGraphicsItem*item);
    void signalBossHit();

public slots:
    void slotBulletCreate(int BaseBulletWidth,int BaseBulletHeight,int BulletHeight);
private slots:
    void slotBulletFly();

private:

    void DeleteBullet();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void  paintBullet();
    int BaseBulletWidth;
    int BaseBulletHeight;
    int BulletHeight;
    int gr = 0;
    int BulletHitIndicator;
    int DeleteLimiter;

    bool CreateBullet;
    bool CreateLock;

    QTimer * BulletTimer;

    QGraphicsItem * BulletItem;
};
#endif
