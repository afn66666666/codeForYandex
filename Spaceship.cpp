#include "spaceship.h"
//#include "levelonegraphic.h"
#include "main.cpp"

Spaceship::Spaceship(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    ShipWidthHitbox = 950; // координаты для hitbox
    ShipHeightHitbox = 853;

    ShipWidth = 875; // координаты для картинки
    ShipHeight = 846;

    BaseBulletHeight = 0;
//    BaseBulletHeight2 = 0;

    BeginIndex = 0;
    ShootIndicator1 = 1;
    ShotQueue = 1;
    ChangeQueue = true;

    BulletHeight1 = ShipHeight;
//    BulletHeight2 = ShipHeight;

    ShootTimer = new QTimer();
    ImmortalTimer = new QTimer();
    ImmortalTimer->setSingleShot(true);
    ShootTimer->setSingleShot(true);

    connect(this,&Spaceship::ReloadSignal, this, &Spaceship::ReloadSlot);
    connect(ShootTimer,&QTimer::timeout, this, &Spaceship::UnlockSlot);
    connect(this, &Spaceship::signalCheckItem,this,&Spaceship::DamageSlot);
    connect(ImmortalTimer,&QTimer::timeout,this,&Spaceship::EndImmortalSlot);

    SpaceshipPixmap = new QPixmap(":/images/karablpro.png");
    auto spaceshipPixmapScaled = SpaceshipPixmap->scaled(QSize(150,100));
    SpaceshipScaledPixmap = new QPixmap(spaceshipPixmapScaled);

    CircleExist = false;
    ImmortalCounter = true;
    BossBeginAtackIndicator = false;
}

Spaceship::~Spaceship()
{
    delete SpaceshipPixmap;
    delete SpaceshipScaledPixmap;
    // TODO: delete smth else
}

void Spaceship::paintHitbox()
{
    SpaceshipPixmapItem  = scene()->addPixmap(*SpaceshipScaledPixmap);
//    scene()->addItem(SpaceshipPixmapItem);
    SpaceshipPixmapItem->setOffset(QPoint(875,846));


}

void Spaceship::paintImmortalCircle(){
    CircleX = ShipWidth;
    CircleY = ShipHeight - 25;
    ImmortalCircle = scene()->addEllipse(CircleX,CircleY,150,150,QPen(Qt::white),QBrush());
//    scene()->addItem(ImmortalCircle);
}

void Spaceship::paintBullet1()
{

    BulletHeight1 = ShipHeight;
    BaseBulletHeight = ShipHeight;
    BaseBulletWidth = ShipWidth + 94;
    BulletItem1 = scene()->addRect(BaseBulletWidth,BaseBulletHeight,10,50,QPen(Qt::white),QBrush(Qt::green));
}

//void Spaceship::paintBullet2()
//{
//    BulletHeight2 = ShipHeight;
//    BaseBulletHeight2 = ShipHeight;
//    BaseBulletWidth = ShipWidth + 94;
//    BulletItem2 = scene()->addRect(BaseBulletWidth,BaseBulletHeight2,10,50,QPen(Qt::white),QBrush(Qt::green));
//}



QRectF Spaceship::boundingRect() const
{
    return QRectF(0,0,100,100);//0,0,1920,1080   // Ограничиваем область, в которой лежит треугольник
}

void Spaceship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

        QPolygonF polygon;   // Используем класс полигона, чтобы отрисовать треугольник
        // Помещаем координаты точек в полигональную модель
        polygon << QPoint(ShipWidthHitbox, ShipHeightHitbox) << QPoint(ShipWidthHitbox+27,ShipHeightHitbox+37) << QPoint(ShipWidthHitbox+54,ShipHeightHitbox+60) << QPoint(ShipWidthHitbox-54,ShipHeightHitbox+60) << QPoint(ShipWidthHitbox-27,ShipHeightHitbox+37);
        painter->setBrush(Qt::cyan);     // Устанавливаем кисть, которой будем отрисовывать объект
        painter->drawPolygon(polygon);  // Рисуем треугольник по полигональной модели
        Q_UNUSED(option);
        Q_UNUSED(widget);


}

QPainterPath Spaceship::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;

}


void Spaceship::slotSpaceshipMoveTimer()
{
   /* Поочерёдно выполняем проверку на нажатие клавиш
     * с помощью функции асинхронного получения состояния клавиш,
     * которая предоставляется WinAPI
     * */

    if(BeginIndex){



//        QList<QGraphicsItem *> foundItems = scene()->items(SpaceshipPixmapItem->x(), SpaceshipPixmapItem->y(),
//                                                           SpaceshipScaledPixmap->width(), SpaceshipScaledPixmap->height(),
//                                                           Qt::ItemSelectionMode::IntersectsItemBoundingRect,
//                                                           Qt::SortOrder::AscendingOrder);
//           foreach (QGraphicsItem *item, foundItems) {
//               if (item == this)
//                   continue;
//               if (dynamic_cast<EnemiesPreset1*>(item) == nullptr) // check if item is enemy item
//                   continue;
//               emit signalCheckItem(item);
//           }


        if(GetAsyncKeyState(VK_UP)){


            while(CreatePixmapLimiter == 1){
            paintHitbox();
            emit signalDeleteSpaceship();
            CreateHitboxIndicator = 1;
            CreatePixmapLimiter--;
            }

            if(CreatePixmapLimiter){
                ShipHeight -= 15;
                SpaceshipPixmapItem->setY(-(846 - ShipHeight));
                setPos(mapToParent(0,-15));
                if(CircleExist){
                   ImmortalCircle->setY(-(CircleY - ShipHeight+15));
                }
            }

            CreatePixmapLimiter = 4;
            }

    if(GetAsyncKeyState(VK_LEFT)){


        while(CreatePixmapLimiter == 1){
        paintHitbox();
        emit signalDeleteSpaceship();
        CreateHitboxIndicator = 1;
        CreatePixmapLimiter--;
        }

        if(CreatePixmapLimiter){
            ShipWidth -= 15;
            SpaceshipPixmapItem->setX(-(875-ShipWidth));
            setPos(mapToParent(-15,0));
            if(CircleExist){
                ImmortalCircle->setX(-(CircleX - ShipWidth));
            }

        }

        CreatePixmapLimiter = 4;
    }

        if(GetAsyncKeyState(VK_RIGHT)){


        while(CreatePixmapLimiter == 1){

        paintHitbox();
        emit signalDeleteSpaceship();
        CreateHitboxIndicator = 1;
        CreatePixmapLimiter--;
        }
        if(CreatePixmapLimiter){
            ShipWidth += 15;
            SpaceshipPixmapItem->setX(-(875-ShipWidth));
            setPos(mapToParent(+15,0));
            if(CircleExist){
                ImmortalCircle->setX(-(CircleX - ShipWidth));
            }

        }
        CreatePixmapLimiter = 4;
    }


    if(GetAsyncKeyState(VK_DOWN)){


        while(CreatePixmapLimiter == 1){
        paintHitbox();
        emit signalDeleteSpaceship();
        CreateHitboxIndicator = 1;
        CreatePixmapLimiter--;
        }

        if(CreatePixmapLimiter){
            ShipHeight += 15;
            SpaceshipPixmapItem->setY(-(846 - ShipHeight));
            setPos(mapToParent(0,+15)); 
            if(CircleExist){
                ImmortalCircle->setY(-(CircleY - ShipHeight+15));
            }
        }

        CreatePixmapLimiter = 4;
    }




        if(GetAsyncKeyState(VK_CONTROL)){
            if(ShootIndicator1){ // разрешение на стрельбу
            if(ShotQueue == 1){
                ShotQueue = 2;
            BulletHeight1 = ShipHeight;
            BaseBulletHeight = ShipHeight;
            BaseBulletWidth = ShipWidth + 69;
            emit ReloadSignal();
            emit signalShoot1(BaseBulletWidth,BaseBulletHeight,BulletHeight1);
            }
            else{
                ShotQueue = 1;
                BulletHeight1 = ShipHeight;
                BaseBulletHeight = ShipHeight;
                BaseBulletWidth = ShipWidth + 69;
                emit ReloadSignal();
                emit signalShoot2(BaseBulletWidth,BaseBulletHeight,BulletHeight1);
            }
            }
        }


//            if(ShotQueue == 1){
//                paintBullet1();
//                if(ChangeQueue){
//                    emit SpecialSignal();
//                    ShootIndex1 = 1;
//                }
//            }
//            if(ShotQueue == 2){
//                paintBullet2();
//                ShootIndex2 = 1;
//                if(ChangeQueue){
//                    emit SpecialSignal();
//                }
//            }



if(CreateHitboxIndicator){
        QList<QGraphicsItem *> foundItems = scene()->items(SpaceshipPixmapItem->x()+ShipWidthHitbox-54, SpaceshipPixmapItem->y()+ShipHeightHitbox,
                                                           124,
                                                           60,
                                                           Qt::ItemSelectionMode::IntersectsItemBoundingRect,
                                                           Qt::SortOrder::AscendingOrder);



           foreach (QGraphicsItem *item, foundItems) {
               if (item == this)
                   continue;
               if (dynamic_cast<EnemiesPreset1*>(item) != nullptr){ // check if item is enemy item

               if(ImmortalCounter){ // true - damage  false - immortal
                   ImmortalCounter = false; // обьявляем неуязвимость
               emit signalCheckItem(item);
                   continue;
               }
               }


               if (dynamic_cast<EnemiesPreset2*>(item) != nullptr){ // check if item is enemy item
                    if(ImmortalCounter){ // true - damage  false - immortal
                        ImmortalCounter = false; // обьявляем неуязвимость
                        emit signalCheckItem(item);
                        continue;
                    }
               }

               if (dynamic_cast<EnemiesPreset3*>(item) != nullptr){ // check if item is enemy item
                    if(ImmortalCounter){ // true - damage  false - immortal
                    ImmortalCounter = false; // обьявляем неуязвимость
                    emit signalCheckItem(item);
                        continue;
                    }
               }

               if (dynamic_cast<EnemiesPreset4*>(item) != nullptr){ // check if item is enemy item
                    if(ImmortalCounter){ // true - damage  false - immortal
                    ImmortalCounter = false; // обьявляем неуязвимость
                    emit signalCheckItem(item);
                        continue;
                    }
               }

               if (dynamic_cast<EnemiesPreset5*>(item) != nullptr){ // check if item is enemy item
                    if(ImmortalCounter){ // true - damage  false - immortal
                    ImmortalCounter = false; // обьявляем неуязвимость
                    emit signalCheckItem(item);
                        continue;
                    }
               }
               if (dynamic_cast<Boss*>(item) != nullptr){ // check if item is enemy item
                    if(ImmortalCounter){ // true - damage  false - immortal
                    ImmortalCounter = false; // обьявляем неуязвимость
                    emit signalCheckItem(item);
                        continue;
                    }
               }

               if (ShipWidth <= 990 and ShipWidth >=740){
                   if(BossBeginAtackIndicator){
                   if(ImmortalCounter){
                   ImmortalCounter = false; // обьявляем неуязвимость
                   emit signalCheckItem(this);
                   continue;
                   }
                   }
               }
           }
}



        if(this->x() - 10 < -910){
            ShipWidth = -25;
            SpaceshipPixmapItem->setX(-900);/*setOffset(QPoint(ShipWidth+Shift,ShipHeight));*/// слева
            this->setX(-900);
        }

        if(this->x() + 10 > 905){
            ShipWidth = 1770;
            SpaceshipPixmapItem->setX(895);
            this->setX(895);        // справа
        }

        if(this->y() - 10 < -866){
            ShipHeight = 0;
            SpaceshipPixmapItem->setY(-846);
            this->setY(-846);       // сверху
        }

        if(this->y() + 10 > 150){
            ShipHeight = 986;
            SpaceshipPixmapItem->setY(140);
            this->setY(140);        // снизу
        }



//                    if(ShootIndex2 == 1){
//                        if(BulletHeight2 > -100){
//                            BulletItem2->setY(BaseBulletHeight2 - BulletHeight2 - 20);
//                            BulletHeight2 += 35;
//                        }

//                        else{
//                            delete BulletItem2;
//                        }
//                    }

                }
            }

void Spaceship::ReloadSlot()
{
    ShootIndicator1 = 0; // отключаем стрельбу
    ShootTimer->start(500); // запускаем таймер на следующий слот
}

void Spaceship::UnlockSlot()
{
    ShootIndicator1 = 1;
}

void Spaceship::DamageSlot(QGraphicsItem *item)
{
    Q_UNUSED(item);
    CircleExist = true; // кружок существует
                        // если true то рисуем кружок бессмертия и ставим таймер
        paintImmortalCircle();
        ImmortalTimer->start(3000);
}

void Spaceship::EndImmortalSlot()
{
    scene()->removeItem(ImmortalCircle);
    CircleExist = false; // тк кружка больше нет
    ImmortalCounter = true;
}


void Spaceship::slotAllowKeys()
{
    BeginIndex = 1;
}

void Spaceship::slotChangeBossDamage(int i)
{
    if(i){
        BossBeginAtackIndicator = true;
    }
    else{
        BossBeginAtackIndicator = false;
    }
}

void Spaceship::slotForbidKeys()
{
    BeginIndex = 0;
}





