#include "enemiespreset1.h"

EnemiesPreset1::EnemiesPreset1(QObject *parent)
       :QObject(parent), QGraphicsItem()
{
     FirstPingIndex = 120;
     BeginEnemies = 1;
     PaintAllowIndex = false;
     SpawnTimer = new QTimer();
     BaseEnemyWidth1 = 2100;

     KillIndicator = 1;

     EnemyWidth1 = 0;
     RectX = 2100;
     RectY = 200;

}

EnemiesPreset1::~EnemiesPreset1()
{
    delete EnemyPixmapItem1;
    delete enemy1;
}



void EnemiesPreset1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF EnemiesPreset1::boundingRect() const
{
    return QRectF(RectX,RectY,50,30); // вся проблема

}



void EnemiesPreset1::paintEnemy1()
{
    EnemyWidth1 = BaseEnemyWidth1;
    enemy1 = scene()->addRect(BaseEnemyWidth1 - 6,200,50,30,QPen(Qt::white),QBrush(Qt::white));
    EnemyPixmapItem1 = scene()->addPixmap(EnemyPixmapScaled);
    EnemyPixmapItem1->setOffset(BaseEnemyWidth1,170);

}

//void EnemiesPreset1::paintEnemy2()
//{
//    EnemyWidth2 = BaseEnemyWidth2;
//    enemy2 = scene()->addRect(BaseEnemyWidth2,200,40,30,QPen(Qt::white),QBrush(Qt::gray));

//}

void EnemiesPreset1::slotEnemiesTimer()
{
    if(KillIndicator){
    if(FirstPingIndex){
        FirstPingIndex --;
        if(FirstPingIndex == 1){
              paintEnemy1();
            FirstPingIndex = 0;
        }
    }

    else{
        if(BeginEnemies){
            if(EnemyWidth1 < 4000){
                prepareGeometryChange();
                Form = boundingRect();
                EnemyWidth1 += 10;
                RectX -= 10;
                enemy1->setX(BaseEnemyWidth1 - EnemyWidth1);
                EnemyPixmapItem1->setX(BaseEnemyWidth1 - EnemyWidth1 - 70);
            }
        }

//        else{
//            if(BeginEnemies){
//            enemy1->setX(BaseEnemyWidth1 - EnemyWidth1);
//            RectX = BaseEnemyWidth1 - EnemyWidth1;
//            prepareGeometryChange();
//            Form =  boundingRect();

//            }
//        }

//        if(EnemyWidth2 < 4150){
//        EnemyWidth2 += 10;
//        enemy2->setX(BaseEnemyWidth2 - EnemyWidth2);

//        }
//        else{
//            enemy2->setX(BaseEnemyWidth2 - EnemyWidth2);

             }
        }
    }



void EnemiesPreset1::slotFreezeEnemies()
{
    BeginEnemies = 0;
}

void EnemiesPreset1::slotRunEnemies()
{
    BeginEnemies = 1;
}

void EnemiesPreset1::slotDeleteEnemy()
{
    KillIndicator = 0;
    delete EnemyPixmapItem1;
    delete enemy1;
}
