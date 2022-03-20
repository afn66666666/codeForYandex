#include "levelonegraphic.h"


LevelOneGraphic::LevelOneGraphic(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    this->setMinimumHeight(1000);
    this->setMinimumWidth(1900);

    ScorePoints = 0;
    DeleteItmesLimiter = true;
    EndLimiter = 0;
    aaa = false;
    scene = new QGraphicsScene();// Инициализируем сцену для отрисовки
    this->setScene(scene);
    LifesCounter = 3;
    MemoryDontLeakLimimter = 0;

    SpaceshipPixmap = new Spaceship();

    enemies_1 = new EnemiesPreset1();

    enemies_2 = new EnemiesPreset1();
    enemies_2->BaseEnemyWidth1 = 2300;
    enemies_2->RectX = 2300;

    enemies_3 = new EnemiesPreset1();
    enemies_3->BaseEnemyWidth1 = 2500;
    enemies_3->RectX = 2500;

    enemies_4 = new EnemiesPreset1();
    enemies_4->BaseEnemyWidth1 = 2700;
    enemies_4->RectX = 2700;

    enemies_5 = new EnemiesPreset1();
    enemies_5->BaseEnemyWidth1 = 2900;
    enemies_5->RectX = 2900;

    bullet_1 = new Bullet1();
    bullet_2 = new Bullet2();

    connect(this,&LevelOneGraphic::signalForbidKeys,SpaceshipPixmap,&Spaceship::slotForbidKeys);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,SpaceshipPixmap,&Spaceship::slotAllowKeys);
    connect(this,&LevelOneGraphic::signalBlock,SpaceshipPixmap,&Spaceship::slotAllowKeys);

    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_1,&EnemiesPreset1::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_1,&EnemiesPreset1::slotRunEnemies);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_2,&EnemiesPreset1::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_2,&EnemiesPreset1::slotRunEnemies);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_3,&EnemiesPreset1::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_3,&EnemiesPreset1::slotRunEnemies);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_4,&EnemiesPreset1::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_4,&EnemiesPreset1::slotRunEnemies);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_5,&EnemiesPreset1::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_5,&EnemiesPreset1::slotRunEnemies);

    connect(this,&LevelOneGraphic::signalEnd,this,&LevelOneGraphic::slotEndLevel);
    connect(SpaceshipPixmap,SIGNAL(signalDeleteSpaceship()),this, SLOT(slotDeleteSpaceship()));
    connect(SpaceshipPixmap,&Spaceship::signalCheckItem,this,&LevelOneGraphic::slotDamage);


    group_spaceship = new QGraphicsItemGroup();
    group_screen = new QGraphicsItemGroup();


    scene->addItem(group_screen);
    scene->addItem(SpaceshipPixmap);

    scene->addItem(enemies_1);
    scene->addItem(enemies_2);
    scene->addItem(enemies_3);
    scene->addItem(enemies_4);
    scene->addItem(enemies_5);


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
//    SpaceshipPixmap->setPos(100,100);

    // Добавляем первую группу в сцену
               // Добавляем вторую группу в сцену
    StartTimer = new QTimer();
    GameTimer = new QTimer();
    EnemyTimer = new QTimer();
    Preset2Timer = new QTimer();
    EndTimer = new QTimer();

    EndTimer->setSingleShot(true);
    StartTimer->setSingleShot(true);
    // Подключаем СЛОТ для отрисовки к таймеру
    StartTimer->start(0);
    GameTimer->start(1000/50);
    EnemyTimer->start(1000/70);

    connect(bullet_1,&Bullet1::signalKill,this,&LevelOneGraphic::slotKill);
    connect(bullet_2,&Bullet2::signalKill,this,&LevelOneGraphic::slotKill);
    connect(SpaceshipPixmap,&Spaceship::signalShoot1,bullet_1,&Bullet1::slotBulletCreate);
    connect(SpaceshipPixmap,&Spaceship::signalShoot2,bullet_2,&Bullet2::slotBulletCreate);

    connect(EnemyTimer,&QTimer::timeout,enemies_1,&EnemiesPreset1::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_2,&EnemiesPreset1::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_3,&EnemiesPreset1::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_4,&EnemiesPreset1::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_5,&EnemiesPreset1::slotEnemiesTimer);
    connect(EndTimer,&QTimer::timeout,this,&LevelOneGraphic::slotEndLevel);

    connect(GameTimer,&QTimer::timeout,SpaceshipPixmap,&Spaceship::slotSpaceshipMoveTimer);
    connect(StartTimer, SIGNAL(timeout()), this, SLOT(slotLevelOne()));


}
LevelOneGraphic::~LevelOneGraphic()
{

}


void LevelOneGraphic::slotLevelOne()
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

     LevelOnePixmap = QPixmap(":/images/baa284faff2374fe7e6901a2811fe121.jpg");
     LevelOneScaledPixmap = LevelOnePixmap.scaled(QSize(Width, Height));
     LevelOneItemScreen = scene->addPixmap(LevelOneScaledPixmap);
     group_screen->addToGroup(LevelOneItemScreen);


     LifesPixmap =  QPixmap(":/images/heart.png");
     LifesPixmapScaled = LifesPixmap.scaled(60,60);
     LifesPixmapItem = scene->addPixmap(LifesPixmapScaled);
     LifesPixmapItem->setPos(Width - 170,0);
     group_screen->addToGroup(LifesPixmapItem);



}

void LevelOneGraphic::slotDeleteSpaceship()
{
    deleteItemsFromGroup(group_spaceship);
}

void LevelOneGraphic::slotAllowKeys()
{
    emit signalAllowKeysSecond();
}

void LevelOneGraphic::slotDamage()
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
        emit signalEndGame(this,ScorePoints);
    }
}

void LevelOneGraphic::slotKill(QGraphicsItem*item)
{
    scene->removeItem(Scores);
    delete Scores;
    ScorePoints += 3000;
    Scores = new QGraphicsTextItem(QString::number(ScorePoints));
    Scores->setDefaultTextColor(QColor::fromRgb(235,34,106));
    Scores->setPos(1920 - 250,90);
    Scores->setFont(mfont);
    scene->addItem(Scores);

    if(ScorePoints == 15000){
       ScorePoints = 16000;
       Spawn2Preset();
       Preset2Timer->start(1000/70);
    }
    delete item;

}

void LevelOneGraphic::slotEndLevel()
{

    emit signalEndLevel(ScorePoints);
}

void LevelOneGraphic::slotOutOfScreen()
{
    if(DeleteItmesLimiter){
//        DeleteItmesLimiter = false;
    }
    if(EndLimiter){
        if(DeleteItmesLimiter){
            EndTimer->start(100);
            DeleteItmesLimiter = false;
        }
    }

}


void LevelOneGraphic::resizeEvent(QResizeEvent *event)
{
    StartTimer->start(1);   // Как только событие произошло стартуем таймер для отрисовки
    QGraphicsView::resizeEvent(event);  // Запускаем событие родителького класса
}

void LevelOneGraphic::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group) {
          delete item;
       }
    }
}

void LevelOneGraphic::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        emit signalForbidKeys();
        emit signalMiniMenu();
    }
}

void LevelOneGraphic::Spawn2Preset()
{
    enemies_2_1 = new EnemiesPreset2();
    enemies_2_1->RectX = 600;

    enemies_2_2 = new EnemiesPreset2();
    enemies_2_2->RectX = 700;

    enemies_2_3 = new EnemiesPreset2();
    enemies_2_3->RectX = 800;

    enemies_2_4 = new EnemiesPreset2();
    enemies_2_4->RectX = 900;

    enemies_2_5 = new EnemiesPreset2();
    enemies_2_5->RectX = 1000;

    enemies_2_6 = new EnemiesPreset2();
    enemies_2_6->RectX = 1100;

    enemies_2_7 = new EnemiesPreset2();
    enemies_2_7->RectX = 1200;

    enemies_2_8 = new EnemiesPreset2();
    enemies_2_8->RectX = 1300;

    scene->addItem(enemies_2_1);
    scene->addItem(enemies_2_2);
    scene->addItem(enemies_2_3);
    scene->addItem(enemies_2_4);
    scene->addItem(enemies_2_5);
    scene->addItem(enemies_2_6);
    scene->addItem(enemies_2_7);
    scene->addItem(enemies_2_8);

    connect(Preset2Timer,&QTimer::timeout,enemies_2_1,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_2_1,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_2_1,&EnemiesPreset2::slotRunEnemies);

    connect(Preset2Timer,&QTimer::timeout,enemies_2_2,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_2_2,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_2_2,&EnemiesPreset2::slotRunEnemies);

    connect(Preset2Timer,&QTimer::timeout,enemies_2_3,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_2_3,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_2_3,&EnemiesPreset2::slotRunEnemies);

    connect(Preset2Timer,&QTimer::timeout,enemies_2_4,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_2_4,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_2_4,&EnemiesPreset2::slotRunEnemies);

    connect(Preset2Timer,&QTimer::timeout,enemies_2_5,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_2_5,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_2_5,&EnemiesPreset2::slotRunEnemies);

    connect(Preset2Timer,&QTimer::timeout,enemies_2_6,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_2_6,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_2_6,&EnemiesPreset2::slotRunEnemies);

    connect(Preset2Timer,&QTimer::timeout,enemies_2_7,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_2_7,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_2_7,&EnemiesPreset2::slotRunEnemies);

    connect(Preset2Timer,&QTimer::timeout,enemies_2_8,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelOneGraphic::signalForbidKeys,enemies_2_8,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelOneGraphic::signalAllowKeysSecond,enemies_2_8,&EnemiesPreset2::slotRunEnemies);

    connect(enemies_2_1,&EnemiesPreset2::signalOutOfScreen,this,&LevelOneGraphic::slotOutOfScreen);
    connect(enemies_2_8,&EnemiesPreset2::signalOutOfScreen,this,&LevelOneGraphic::slotOutOfScreen);

    EndLimiter = 1;
}


