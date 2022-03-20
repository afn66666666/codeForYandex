#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

#include "enemiespreset1.h"
#include "enemiespreset2.h"
#include "boss.h"

#include "windows.h"

class Spaceship : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Spaceship(QObject *parent = 0);
    ~Spaceship();

    int ShipWidthHitbox;
    int ShipHeightHitbox;

    int ShipWidth;
    int ShipHeight;


signals:
    void signalDeleteSpaceship();
    void ReloadSignal();
    void signalCheckItem(QGraphicsItem*item);
    void signalShoot1(int BaseBulletWidth, int BaseBulletHeight, int BulletHeight);
    void signalShoot2(int BaseBulletWidth, int BaseBulletHeight, int BulletHeight);

public slots:
    void slotSpaceshipMoveTimer();
    void slotForbidKeys();
    void slotAllowKeys();
    void slotChangeBossDamage(int i);
private slots:
    void ReloadSlot();
    void UnlockSlot();
    void DamageSlot(QGraphicsItem*item);
    void EndImmortalSlot();





private:
    QGraphicsItem* ImmortalCircle;
    bool CircleExist; // индикатор отрисовки кружка
    bool ImmortalCounter; // индикатор неуязвимости

    QPixmap* SpaceshipPixmap;
    QPixmap* SpaceshipScaledPixmap;
    QGraphicsPixmapItem* SpaceshipPixmapItem;



    QGraphicsItem* BulletItem1;
    QGraphicsItem* BulletItem2;



    int CreatePixmapLimiter = 1;
    int CreateHitboxIndicator = 0;
    int Shift = 25;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;

    void paintHitbox();
    void paintBullet1();
    void paintBullet2();
    void paintImmortalCircle();




    int CircleX;
    int CircleY;

    int BaseBulletWidth;

    int BaseBulletHeight;
    int BaseBulletHeight2;

    int BulletHeight1;
    int BulletHeight2;


    int BeginIndex;
    int ShootIndicator1;
    int ShootIndicator2;
    int ShotQueue;

    bool ChangeQueue;
    bool BossBeginAtackIndicator;

    QTimer* ShootTimer;
    QTimer* ImmortalTimer;

    int tmp;


};

#endif // SPACESHIP_H
