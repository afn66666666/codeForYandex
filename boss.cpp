#include "boss.h"

Boss::Boss(QObject *parent)
       :QObject(parent), QGraphicsItem()
{
    BossLifes = 20;
    PaintIndicator = true;
    ShootTimer = new QTimer();
    PrepareTimer = new QTimer();
    ShootIndicator = 0;
    connect(PrepareTimer,&QTimer::timeout,this,&Boss::slotShooting);
    PrepareTimer->start(2000);

}

Boss::~Boss()
{
    delete BossPixmapItem;
}

void Boss::slotBossDamage()
{
    BossLifes--;
    if(BossLifes == 0){
        delete LaserPixmapItem;
        emit signalGameWin();
    }
}





void Boss::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(PaintIndicator){
        PaintIndicator = false;
        BossPixmapItem = scene()->addPixmap(BossPixmapScaled);
        BossPixmapItem->setOffset(540,20);
        Q_UNUSED(painter)
        Q_UNUSED(option)
        Q_UNUSED(widget)
    }
}

QRectF Boss::boundingRect() const
{
    return QRectF(840,100,190,350); // вся проблема

}




//void EnemiesPreset1::paintEnemy2()
//{
//    EnemyWidth2 = BaseEnemyWidth2;
//    enemy2 = scene()->addRect(BaseEnemyWidth2,200,40,30,QPen(Qt::white),QBrush(Qt::gray));

//}

void Boss::slotShooting()
{
    if(ShootIndicator == 2){ // лазер стреляет
        LaserPixmapItem = scene()->addPixmap(LaserPixmapScaled);
        LaserPixmapItem->setOffset(840,450);
        ShootIndicator --;
        emit signalDamageOn(1);
    }
    else{
        if(ShootIndicator == 0){
            ShootIndicator += 2;
        }
        if(ShootIndicator == 1){ // не стреляет
            ShootIndicator++;
            delete LaserPixmapItem;
            emit signalDamageOn(0);
        }
    }
}





void Boss::slotFreezeEnemies()
{
    BeginEnemies = 0;
}

void Boss::slotRunEnemies()
{
    BeginEnemies = 1;
}


