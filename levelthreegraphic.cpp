#include "levelthreegraphic.h"

LevelThreeGraphic::LevelThreeGraphic(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    this->setMinimumHeight(1000);
    this->setMinimumWidth(1900);

    ScorePoints = 0;
    TimerSetterLimiter = true;
    EndLimiter = 0;
    scene = new QGraphicsScene();// Инициализируем сцену для отрисовки
    this->setScene(scene);
    MemoryDontLeakLimimter = 0;
    LifesCounter = 3;

    SpaceshipPixmap = new Spaceship();
    boss = new Boss();


    StartTimer = new QTimer();
    GameTimer = new QTimer();
    DamageCheckTimer = new QTimer();
    EndTimer = new QTimer();


    bullet_1 = new Bullet1();
    bullet_2 = new Bullet2();

    connect(this,&LevelThreeGraphic::signalForbidKeys,SpaceshipPixmap,&Spaceship::slotForbidKeys);
    connect(this,&LevelThreeGraphic::signalAllowKeysSecond,SpaceshipPixmap,&Spaceship::slotAllowKeys);
    connect(this,&LevelThreeGraphic::signalBlock,SpaceshipPixmap,&Spaceship::slotAllowKeys);
    connect(boss,&Boss::signalGameWin,this,&LevelThreeGraphic::slotGameWin);
    connect(this,&LevelThreeGraphic::signalEnd,this,&LevelThreeGraphic::slotEndLevel);
    connect(SpaceshipPixmap,SIGNAL(signalDeleteSpaceship()),this, SLOT(slotDeleteSpaceship()));
    connect(SpaceshipPixmap,&Spaceship::signalCheckItem,this,&LevelThreeGraphic::slotDamage);

    connect(bullet_2,&Bullet2::signalBossHit,this,&LevelThreeGraphic::slotBossHit);
//    connect(Preset3Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn3Preset);
//    connect(Preset4Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn4Preset);
//    connect(Preset5Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn5Preset);




    group_spaceship = new QGraphicsItemGroup();
    group_screen = new QGraphicsItemGroup();


    scene->addItem(group_screen);
    scene->addItem(SpaceshipPixmap);



    Lifes = new QGraphicsTextItem("X 3");
    Lifes->setDefaultTextColor(QColor::fromRgb(235,34,106));
    Lifes->setPos(1920 - 120,0);
    Lifes->setFont(mfont);
    scene->addItem(Lifes);

    Scores = new QGraphicsTextItem("0");
    Scores->setDefaultTextColor(QColor::fromRgb(235,34,106));
    Scores->setPos(1920 - 250,80);
    Scores->setFont(mfont);
    scene->addItem(Scores);
    scene->addItem(group_spaceship);
    scene->addItem(bullet_1);
    scene->addItem(bullet_2);
    scene->addItem(boss);
//    SpaceshipPixmap->setPos(100,100);

    // Добавляем первую группу в сцену
               // Добавляем вторую группу в сцену


    EndTimer->setSingleShot(true);
    StartTimer->setSingleShot(true);
    // Подключаем СЛОТ для отрисовки к таймеру
    StartTimer->start(0);
    GameTimer->start(1000/50);
    DamageCheckTimer->start(1000/70);

    connect(DamageCheckTimer,&QTimer::timeout,this,&LevelThreeGraphic::DamageCheckSlot);
    connect(bullet_1,&Bullet1::signalBossHit,this,&LevelThreeGraphic::slotBossHit);
    connect(bullet_2,&Bullet2::signalBossHit,this,&LevelThreeGraphic::slotBossHit);
//    connect(bullet_1,&Bullet1::signalKill,this,&LevelThreeGraphic::slotKill);
//    connect(bullet_2,&Bullet2::signalKill,this,&LevelThreeGraphic::slotKill);
    connect(SpaceshipPixmap,&Spaceship::signalShoot1,bullet_1,&Bullet1::slotBulletCreate);
    connect(SpaceshipPixmap,&Spaceship::signalShoot2,bullet_2,&Bullet2::slotBulletCreate);
    connect(EndTimer,&QTimer::timeout,this,&LevelThreeGraphic::slotEndLevel);
    connect(GameTimer,&QTimer::timeout,SpaceshipPixmap,&Spaceship::slotSpaceshipMoveTimer);
    connect(StartTimer,&QTimer::timeout, this,&LevelThreeGraphic::slotLevelTwo);

    connect(bullet_1,&Bullet1::signalBossHit,boss,&Boss::slotBossDamage);
    connect(bullet_2,&Bullet2::signalBossHit,boss,&Boss::slotBossDamage);
    connect(boss,&Boss::signalDamageOn,SpaceshipPixmap,&Spaceship::slotChangeBossDamage);



}
LevelThreeGraphic::~LevelThreeGraphic()
{

}


void LevelThreeGraphic::slotLevelTwo()
{
     if(MemoryDontLeakLimimter){
        this->deleteItemsFromGroup(group_spaceship);
        this->deleteItemsFromGroup(group_screen);
     }
     MemoryDontLeakLimimter = 1;
     int Width          = this->width();
     int Height         = this->height();

     emit signalBlock();
     scene->setSceneRect(0,0,Width,Height);

     SpaceshipPixmapItemBegin = scene->addPixmap(SpaceshipScaledPixmapBegin);
     SpaceshipPixmapItemBegin->setOffset(QPoint(875,846));
     group_spaceship->addToGroup(SpaceshipPixmapItemBegin);

     LevelOnePixmap = QPixmap(":/images/27a3182951c93a85aa3c2a5e71c7062d.jpg");
     QPixmap LevelOneScaledPixmap = LevelOnePixmap.scaled(QSize(Width, Height));
     QGraphicsPixmapItem* LevelOneItemScreen = scene->addPixmap(LevelOneScaledPixmap);
     group_screen->addToGroup(LevelOneItemScreen);

     LifesPixmap =  QPixmap(":/images/heart.png");
     LifesPixmapScaled = LifesPixmap.scaled(60,60);
     LifesPixmapItem = scene->addPixmap(LifesPixmapScaled);
     LifesPixmapItem->setPos(Width - 170,0);
     group_screen->addToGroup(LifesPixmapItem);



}

void LevelThreeGraphic::slotDeleteSpaceship()
{
    deleteItemsFromGroup(group_spaceship);
}

void LevelThreeGraphic::slotAllowKeys()
{
    emit signalAllowKeysSecond();
}

void LevelThreeGraphic::slotDamage()
{

    int Width = this->width();
    LifesCounter--;
    switch(LifesCounter){
    case 2:
        scene->removeItem(Lifes);
        delete Lifes;
        Lifes = new QGraphicsTextItem("X 2");
        Lifes->setDefaultTextColor(QColor::fromRgb(235,34,106));
        Lifes->setPos(Width - 100,0);
        Lifes->setFont(mfont);
        scene->addItem(Lifes);
        break;
    case 1:
        scene->removeItem(Lifes);
        delete Lifes;
        Lifes = new QGraphicsTextItem("X 1");
        Lifes->setDefaultTextColor(QColor::fromRgb(235,34,106));
        Lifes->setPos(Width - 100,0);
        Lifes->setFont(mfont);
        scene->addItem(Lifes);
        break;
    case 0:
        scene->removeItem(Lifes);
        delete Lifes;
        Lifes = new QGraphicsTextItem("X 0");
        Lifes->setDefaultTextColor(QColor::fromRgb(235,34,106));
        Lifes->setPos(Width - 100,0);
        Lifes->setFont(mfont);
        scene->addItem(Lifes);
        break;
    case -1:
        emit signalEndGame(this, ScorePoints);
    }
}

void LevelThreeGraphic::slotBossHit()
{
    scene->removeItem(Scores);
    delete Scores;
    ScorePoints += 250;
    Scores = new QGraphicsTextItem(QString::number(ScorePoints));
    Scores->setDefaultTextColor(QColor::fromRgb(235,34,106));
    Scores->setPos(1920 - 250,90);
    Scores->setFont(mfont);
    scene->addItem(Scores);

}

void LevelThreeGraphic::slotEndLevel()
{

    emit signalEndLevel(ScorePoints);
}

void LevelThreeGraphic::slotGameWin()
{
    scene->removeItem(boss);
    delete boss;
    QTimer * WinTimer;
    WinTimer = new QTimer();
    WinTimer->start(3000);
    connect(WinTimer,&QTimer::timeout,this,&LevelThreeGraphic::slotGameWinScreen);

}

void LevelThreeGraphic::slotGameWinScreen()
{
    emit signalGameWinScreen(ScorePoints);
}

void LevelThreeGraphic::DamageCheckSlot()
{

}




void LevelThreeGraphic::resizeEvent(QResizeEvent *event)
{
    StartTimer->start(1);   // Как только событие произошло стартуем таймер для отрисовки
    QGraphicsView::resizeEvent(event);  // Запускаем событие родителького класса
}

void LevelThreeGraphic::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group) {
          delete item;
       }
    }
}

void LevelThreeGraphic::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        emit signalForbidKeys();
        emit signalMiniMenu2();
    }
}




