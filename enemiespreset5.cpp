#include "enemiespreset5.h"

EnemiesPreset5::EnemiesPreset5(QObject *parent)
       :QObject(parent), QGraphicsItem()
{
     FirstPingIndex = 1;
     BeginEnemies = 1;
     PaintAllowIndex = false;
     SpawnTimer = new QTimer();

     BaseEnemyWidth5 = 1500;
     BaseEnemyHeight5 = 850;

     KillIndicator = 1;

     EnemyHeight5 = 0;
     EnemyWidth5 = 0;

     www = 0;
     hhh = 0;

     RectX = 1500;
     RectY = 850;
     OutScreenIndicator = true;

}

EnemiesPreset5::~EnemiesPreset5()
{
    delete EnemyPixmapItem5;
    delete enemy5;
}





void EnemiesPreset5::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF EnemiesPreset5::boundingRect() const
{
    return QRectF(RectX - www,RectY-hhh,50,30); // вся проблема

}



void EnemiesPreset5::paintEnemy5()
{

    EnemyHeight5 = BaseEnemyHeight5;
    enemy5 = scene()->addRect(RectX - 6,BaseEnemyHeight5,50,30,QPen(Qt::white),QBrush(Qt::white));
    EnemyPixmapItem5 = scene()->addPixmap(EnemyPixmapScaled);
    EnemyPixmapItem5->setOffset(RectX - 70,BaseEnemyHeight5-30);


}

//void EnemiesPreset1::paintEnemy2()
//{
//    EnemyWidth2 = BaseEnemyWidth2;
//    enemy2 = scene()->addRect(BaseEnemyWidth2,200,40,30,QPen(Qt::white),QBrush(Qt::gray));

//}

void EnemiesPreset5::slotEnemiesTimer()
{

    if(KillIndicator){

        if(FirstPingIndex){
              paintEnemy5();
            FirstPingIndex = 0;
        }


    else{
        if(BeginEnemies){
            if(EnemyWidth5 < 4700){
                prepareGeometryChange();
                Form = boundingRect();
                EnemyWidth5 += 16;
                RectX -= 16;
                enemy5->setX(BaseEnemyWidth5 - EnemyWidth5);
                EnemyPixmapItem5->setX(BaseEnemyWidth5 - EnemyWidth5);
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





void EnemiesPreset5::slotFreezeEnemies()
{
    BeginEnemies = 0;
}

void EnemiesPreset5::slotRunEnemies()
{
    BeginEnemies = 1;
}

void EnemiesPreset5::slotDeleteEnemy()
{
    KillIndicator = 0;
    delete EnemyPixmapItem5;
    delete enemy5;
}
