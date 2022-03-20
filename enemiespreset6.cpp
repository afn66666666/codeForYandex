#include "enemiespreset6.h"

EnemiesPreset6::EnemiesPreset6(QObject *parent)
       :QObject(parent), QGraphicsItem()
{
    FirstPingIndex = 120;
     BeginEnemies = 1;
     PaintAllowIndex = false;
     SpawnTimer = new QTimer();

     BaseEnemyWidth6 = 3100;

     KillIndicator = 1;

     EnemyWidth6 = 0;
     RectX = 3100;
     RectY = 200;

}

EnemiesPreset6::~EnemiesPreset6()
{
    delete EnemyPixmapItem6;
    delete enemy6;
}



void EnemiesPreset6::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF EnemiesPreset6::boundingRect() const
{
    return QRectF(RectX,RectY,50,30); // вся проблема

}



void EnemiesPreset6::paintEnemy2()
{
    EnemyWidth6 = BaseEnemyWidth6;
    enemy6 = scene()->addRect(BaseEnemyWidth6 - 6,200,50,30,QPen(Qt::white),QBrush(Qt::white));
    EnemyPixmapItem6 = scene()->addPixmap(EnemyPixmapScaled);
    EnemyPixmapItem6->setOffset(BaseEnemyWidth6,170);

}

//void EnemiesPreset1::paintEnemy2()
//{
//    EnemyWidth2 = BaseEnemyWidth2;
//    enemy2 = scene()->addRect(BaseEnemyWidth2,200,40,30,QPen(Qt::white),QBrush(Qt::gray));

//}

void EnemiesPreset6::slotEnemiesTimer()
{
    if(KillIndicator){
    if(FirstPingIndex){
        FirstPingIndex --;
        if(FirstPingIndex == 1){
              paintEnemy2();
            FirstPingIndex = 0;
        }
    }

    else{
        if(BeginEnemies){
            if(EnemyWidth6 < 4500){
                prepareGeometryChange();
                Form = boundingRect();
                EnemyWidth6 += 10;
                RectX -= 10;
                enemy6->setX(BaseEnemyWidth6 - EnemyWidth6);
                EnemyPixmapItem6->setX(BaseEnemyWidth6 - EnemyWidth6 - 70);
            }
        }

            else{

                enemy6->setX(BaseEnemyWidth6 - EnemyWidth6);
                RectX = BaseEnemyWidth6 - EnemyWidth6;
                prepareGeometryChange();
                Form =  boundingRect();


            }


     }
    }
}



void EnemiesPreset6::slotFreezeEnemies()
{
    BeginEnemies = 0;
}

void EnemiesPreset6::slotRunEnemies()
{
    BeginEnemies = 1;
}

void EnemiesPreset6::slotDeleteEnemy()
{
    KillIndicator = 0;
    delete EnemyPixmapItem6;
    delete enemy6;
}
