#include "bullet2.h"

Bullet2::Bullet2(QObject*parent)
    :QObject(parent),QGraphicsItem()
{
     BaseBulletWidth = 0;
     BaseBulletHeight = 0;
     BulletHeight = 0;

     CreateBullet = true;
     CreateLock  = false;
     BulletTimer = new QTimer();
     connect(BulletTimer,&QTimer::timeout,this,&Bullet2::slotBulletFly);
     BulletHitIndicator = 0;
}

Bullet2::~Bullet2()
{

}

QRectF Bullet2::boundingRect() const
{
    return QRectF(0,0,1920,1080);
}

void Bullet2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Bullet2::DeleteBullet()
{
    BulletHitIndicator = 1;
    delete BulletItem;
    CreateBullet = true;
}

void Bullet2::paintBullet()
{
    BulletItem = scene()->addRect(BaseBulletWidth,BaseBulletHeight,10,50,QPen(Qt::white),QBrush(Qt::green));
    BulletItem->setY(0);
//    im = scene()->addRect(BaseBulletWidth,BaseBulletHeight,
//                                         10,50,QPen(Qt::white),QBrush(Qt::white));
}

void Bullet2::slotBulletCreate(int OutsideBaseBulletWidth,int OutsideBaseBulletHeight,int OutsideBulletHeight)
{
    BulletHitIndicator = 0;
    BaseBulletWidth = OutsideBaseBulletWidth;
    BaseBulletHeight = OutsideBaseBulletHeight;
    DeleteLimiter = 1;
    BulletHeight = OutsideBulletHeight;
    if(CreateBullet){
        paintBullet();
        gr = 0;
        BulletTimer->start(1000/100);
        CreateBullet = false;
    }
}

void Bullet2::slotBulletFly()
{
    if(!BulletHitIndicator){
    if(gr > - 900){ // пока пуля летит
        BulletHeight += 15;
        BulletItem->setY(BaseBulletHeight - BulletHeight - 20);
         gr -= 15;

         int OAO = BulletItem->y() - BulletItem->y()
                 + BaseBulletHeight + gr;

         QList<QGraphicsItem*> foundItems = scene()->items(BulletItem->x()+BaseBulletWidth,OAO,
                                                           13,50,Qt::ItemSelectionMode::IntersectsItemBoundingRect,
                                                           Qt::SortOrder::AscendingOrder);

         foreach (QGraphicsItem *item, foundItems){
             if(DeleteLimiter){
                 if (item == this)
                 continue;
             if (dynamic_cast<EnemiesPreset1*>(item) != nullptr){ // check if item is enemy item
             emit signalKill(item);
             DeleteBullet();
             DeleteLimiter = 0;
             continue;
             }
             if(dynamic_cast<EnemiesPreset2*>(item) != nullptr){
                 emit signalKill(item);
                 DeleteBullet();
                 DeleteLimiter = 0;
                 continue;
             }
             if(dynamic_cast<EnemiesPreset3*>(item) != nullptr){
                 emit signalKill(item);
                 DeleteBullet();
                 DeleteLimiter = 0;
             }
             if(dynamic_cast<EnemiesPreset4*>(item) != nullptr){
                 emit signalKill(item);
                 DeleteBullet();
                 DeleteLimiter = 0;
             }
             if(dynamic_cast<EnemiesPreset5*>(item) != nullptr){
                 emit signalKill(item);
                 DeleteBullet();
                 DeleteLimiter = 0;
             }
             if(dynamic_cast<Boss*>(item) != nullptr){
                 emit signalBossHit();
                 DeleteBullet();
                 DeleteLimiter = 0;
             }
             }
         }
     }
     else{
            if(!CreateBullet){
         delete BulletItem;
           CreateBullet = true;
            }
     }
    }
}

