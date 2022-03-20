#include "enemiespreset4.h"

EnemiesPreset4::EnemiesPreset4(QObject *parent)
       :QObject(parent), QGraphicsItem()
{
     FirstPingIndex = 1;
     BeginEnemies = 1;
     PaintAllowIndex = false;
     SpawnTimer = new QTimer();
     BaseEnemyHeight4 = -30;
     BaseEnemyWidth4 = 1000;

     www = 0;
     hhh = 0;

     KillIndicator = 1;

     EnemyHeight4 = 0;
     EnemyWidth4 = 0;
     RectX = 1000;
     RectY = -30;
     OutScreenIndicator = true;

}

EnemiesPreset4::~EnemiesPreset4()
{
    delete EnemyPixmapItem4;
    delete enemy4;
}





void EnemiesPreset4::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF EnemiesPreset4::boundingRect() const
{
    return QRectF(RectX - www,RectY - hhh,55,30);

}



void EnemiesPreset4::paintEnemy3()
{

    EnemyHeight4 = BaseEnemyHeight4;
    enemy4 = scene()->addRect(RectX - 6,BaseEnemyHeight4,0,30,QPen(Qt::white),QBrush(Qt::white));
    EnemyPixmapItem4 = scene()->addPixmap(EnemyPixmapScaled);
    EnemyPixmapItem4->setOffset(RectX - 70,BaseEnemyHeight4-30);


}

//void EnemiesPreset1::paintEnemy2()
//{
//    EnemyWidth2 = BaseEnemyWidth2;
//    enemy2 = scene()->addRect(BaseEnemyWidth2,200,40,30,QPen(Qt::white),QBrush(Qt::gray));

//}

void EnemiesPreset4::slotEnemiesTimer()
{

    if(KillIndicator){

        if(FirstPingIndex){
              paintEnemy3();
            FirstPingIndex = 0;
        }


    else{
        if(BeginEnemies){
            if(EnemyHeight4 > -2500){
                prepareGeometryChange();
                Form = boundingRect();
                EnemyHeight4 -= 4;
                EnemyWidth4 += 7;
                RectY += 4;
                RectX -= 7;
                enemy4->setY(BaseEnemyHeight4 - EnemyHeight4);
                EnemyPixmapItem4->setY(BaseEnemyHeight4 - EnemyHeight4);
                enemy4->setX(BaseEnemyWidth4 - EnemyWidth4);
                EnemyPixmapItem4->setX(BaseEnemyWidth4 - EnemyWidth4);
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


void EnemiesPreset4::slotFreezeEnemies()
{
    BeginEnemies = 0;
}

void EnemiesPreset4::slotRunEnemies()
{
    BeginEnemies = 1;
}

void EnemiesPreset4::slotDeleteEnemy()
{
    KillIndicator = 0;
    delete EnemyPixmapItem4;
    delete enemy4;
}
