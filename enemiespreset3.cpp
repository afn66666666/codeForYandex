#include "enemiespreset3.h"

EnemiesPreset3::EnemiesPreset3(QObject *parent)
       :QObject(parent), QGraphicsItem()
{
     FirstPingIndex = 1;
     BeginEnemies = 1;
     PaintAllowIndex = false;
     SpawnTimer = new QTimer();
     BaseEnemyHeight3 = -30;
     BaseEnemyWidth3 = - 30;

     www = 0;
     hhh = 0;

     KillIndicator = 1;

     EnemyHeight3 = 0;
     EnemyWidth3 = 0;
     RectX = -30;
     RectY = -30;
     OutScreenIndicator = true;

}

EnemiesPreset3::~EnemiesPreset3()
{
    delete EnemyPixmapItem3;
    delete enemy3;
}





void EnemiesPreset3::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF EnemiesPreset3::boundingRect() const
{
    return QRectF(RectX - www,RectY - hhh,55,30);

}



void EnemiesPreset3::paintEnemy3()
{

    EnemyHeight3 = BaseEnemyHeight3;
    enemy3 = scene()->addRect(RectX - 6,BaseEnemyHeight3,0,30,QPen(Qt::white),QBrush(Qt::white));
    EnemyPixmapItem3 = scene()->addPixmap(EnemyPixmapScaled);
    EnemyPixmapItem3->setOffset(RectX - 70,BaseEnemyHeight3-30);


}

//void EnemiesPreset1::paintEnemy2()
//{
//    EnemyWidth2 = BaseEnemyWidth2;
//    enemy2 = scene()->addRect(BaseEnemyWidth2,200,40,30,QPen(Qt::white),QBrush(Qt::gray));

//}

void EnemiesPreset3::slotEnemiesTimer()
{

    if(KillIndicator){

        if(FirstPingIndex){
              paintEnemy3();
            FirstPingIndex = 0;
        }


    else{
        if(BeginEnemies){
            if(EnemyHeight3 > -2500){
                prepareGeometryChange();
                Form = boundingRect();
                EnemyHeight3 -= 4;
                EnemyWidth3 -= 7;
                RectY += 4;
                RectX += 7;
                enemy3->setY(BaseEnemyHeight3 - EnemyHeight3);
                EnemyPixmapItem3->setY(BaseEnemyHeight3-EnemyHeight3);
                enemy3->setX(BaseEnemyWidth3 - EnemyWidth3);
                EnemyPixmapItem3->setX(BaseEnemyWidth3 - EnemyWidth3);
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





void EnemiesPreset3::slotFreezeEnemies()
{
    BeginEnemies = 0;
}

void EnemiesPreset3::slotRunEnemies()
{
    BeginEnemies = 1;
}

void EnemiesPreset3::slotDeleteEnemy()
{
    KillIndicator = 0;
    delete EnemyPixmapItem3;
    delete enemy3;
}
