#include "enemiespreset2.h"

EnemiesPreset2::EnemiesPreset2(QObject *parent)
       :QObject(parent), QGraphicsItem()
{
     FirstPingIndex = 1;
     BeginEnemies = 1;
     PaintAllowIndex = false;
     SpawnTimer = new QTimer();
     BaseEnemyHeight2 = -30;

     KillIndicator = 1;

     EnemyHeight2 = 0;
     RectX = 400;
     RectY = -100;
     OutScreenIndicator = true;

}

EnemiesPreset2::~EnemiesPreset2()
{
    delete EnemyPixmapItem2;
    delete enemy2;
}





void EnemiesPreset2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF EnemiesPreset2::boundingRect() const
{
    return QRectF(RectX,RectY+50,50,30); // вся проблема

}



void EnemiesPreset2::paintEnemy2()
{

    EnemyHeight2 = BaseEnemyHeight2;
    enemy2 = scene()->addRect(RectX - 6,BaseEnemyHeight2,50,30,QPen(Qt::white),QBrush(Qt::white));
    EnemyPixmapItem2 = scene()->addPixmap(EnemyPixmapScaled);
    EnemyPixmapItem2->setOffset(RectX - 70,BaseEnemyHeight2-30);


}

//void EnemiesPreset1::paintEnemy2()
//{
//    EnemyWidth2 = BaseEnemyWidth2;
//    enemy2 = scene()->addRect(BaseEnemyWidth2,200,40,30,QPen(Qt::white),QBrush(Qt::gray));

//}

void EnemiesPreset2::slotEnemiesTimer()
{

    if(KillIndicator){

        if(FirstPingIndex){
              paintEnemy2();
            FirstPingIndex = 0;
        }


    else{
        if(BeginEnemies){
            if(EnemyHeight2 > -4500){
                prepareGeometryChange();
                Form = boundingRect();
                EnemyHeight2 -= 10;
                RectY += 10;
                enemy2->setY(BaseEnemyHeight2 - EnemyHeight2);
                EnemyPixmapItem2->setY(BaseEnemyHeight2-EnemyHeight2);
                }
            else{
                FirstPingIndex = 1;
                if(FirstPingIndex){
                emit signalOutOfScreen();
                FirstPingIndex = 0;
                //emit signalLevelEnd();
                }
            }
         }



       }
    }
}





void EnemiesPreset2::slotFreezeEnemies()
{
    BeginEnemies = 0;
}

void EnemiesPreset2::slotRunEnemies()
{
    BeginEnemies = 1;
}

void EnemiesPreset2::slotDeleteEnemy()
{
    KillIndicator = 0;
    delete EnemyPixmapItem2;
    delete enemy2;
}
