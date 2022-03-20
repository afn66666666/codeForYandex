 #include "leveltwographic.h"

LevelTwoGraphic::LevelTwoGraphic(QWidget *parent)
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

    StartTimer = new QTimer();
    GameTimer = new QTimer();
    EnemyTimer = new QTimer();
    EndTimer = new QTimer();
    Preset1Timer = new QTimer();
    Preset2Timer = new QTimer();
    Preset3Timer = new QTimer();
    Preset4Timer = new QTimer();
    Preset5Timer = new QTimer();

    bullet_1 = new Bullet1();
    bullet_2 = new Bullet2();

    connect(this,&LevelTwoGraphic::signalForbidKeys,SpaceshipPixmap,&Spaceship::slotForbidKeys);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,SpaceshipPixmap,&Spaceship::slotAllowKeys);
    connect(this,&LevelTwoGraphic::signalBlock,SpaceshipPixmap,&Spaceship::slotAllowKeys);

    connect(this,&LevelTwoGraphic::signalEnd,this,&LevelTwoGraphic::slotEndLevel);
    connect(SpaceshipPixmap,SIGNAL(signalDeleteSpaceship()),this, SLOT(slotDeleteSpaceship()));
    connect(SpaceshipPixmap,&Spaceship::signalCheckItem,this,&LevelTwoGraphic::slotDamage);
    connect(Preset1Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn1Preset);
    connect(Preset2Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn2Preset);
    connect(Preset2Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn3Preset);
    connect(Preset2Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn4Preset);
    connect(Preset5Timer,&QTimer::timeout, this,&LevelTwoGraphic::Spawn5Preset);
//    connect(Preset3Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn3Preset);
//    connect(Preset4Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn4Preset);
//    connect(Preset5Timer,&QTimer::timeout,this,&LevelTwoGraphic::Spawn5Preset);


    Preset1Timer->setSingleShot(true);
    Preset1Timer->start(3000);

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
//    SpaceshipPixmap->setPos(100,100);

    // Добавляем первую группу в сцену
               // Добавляем вторую группу в сцену


    EndTimer->setSingleShot(true);
    StartTimer->setSingleShot(true);
    // Подключаем СЛОТ для отрисовки к таймеру
    StartTimer->start(0);
    GameTimer->start(1000/50);
    EnemyTimer->start(1000/70);

    connect(bullet_1,&Bullet1::signalKill,this,&LevelTwoGraphic::slotKill);
    connect(bullet_2,&Bullet2::signalKill,this,&LevelTwoGraphic::slotKill);
    connect(SpaceshipPixmap,&Spaceship::signalShoot1,bullet_1,&Bullet1::slotBulletCreate);
    connect(SpaceshipPixmap,&Spaceship::signalShoot2,bullet_2,&Bullet2::slotBulletCreate);


//    connect(EndTimer,&QTimer::timeout,this,&LevelTwoGraphic::slotEndLevel);

    connect(GameTimer,&QTimer::timeout,SpaceshipPixmap,&Spaceship::slotSpaceshipMoveTimer);
    connect(StartTimer,&QTimer::timeout, this,&LevelTwoGraphic::slotLevelTwo);



}
LevelTwoGraphic::~LevelTwoGraphic()
{

}


void LevelTwoGraphic::slotLevelTwo()
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


     LevelOnePixmap = QPixmap(":/images/ef6a0b042d7e6830cb082f264300e0a7 (1).png");
     QPixmap LevelOneScaledPixmap = LevelOnePixmap.scaled(QSize(Width, Height));
     QGraphicsPixmapItem* LevelOneItemScreen = scene->addPixmap(LevelOneScaledPixmap);
     group_screen->addToGroup(LevelOneItemScreen);

     LifesPixmap =  QPixmap(":/images/heart.png");
     LifesPixmapScaled = LifesPixmap.scaled(60,60);
     LifesPixmapItem = scene->addPixmap(LifesPixmapScaled);
     LifesPixmapItem->setPos(Width - 170,0);
     group_screen->addToGroup(LifesPixmapItem);



}

void LevelTwoGraphic::slotDeleteSpaceship()
{
    deleteItemsFromGroup(group_spaceship);
}

void LevelTwoGraphic::slotAllowKeys()
{
    emit signalAllowKeysSecond();
}

void LevelTwoGraphic::slotDamage()
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

void LevelTwoGraphic::slotKill(QGraphicsItem*item)
{
    scene->removeItem(Scores);
    delete Scores;
    ScorePoints += 3000;
    Scores = new QGraphicsTextItem(QString::number(ScorePoints));
    Scores->setDefaultTextColor(QColor::fromRgb(235,34,106));
    Scores->setPos(1920 - 250,90);
    Scores->setFont(mfont);
    scene->addItem(Scores);

    delete item;

}

void LevelTwoGraphic::slotEndLevel()
{

    emit signalEndLevel(ScorePoints);
}

void LevelTwoGraphic::slotOutOfScreen()
{
    if(TimerSetterLimiter){
        Preset2Timer->setSingleShot(true);
        Preset2Timer->start(30);
        TimerSetterLimiter = false;
    }

}


void LevelTwoGraphic::resizeEvent(QResizeEvent *event)
{
    StartTimer->start(1);   // Как только событие произошло стартуем таймер для отрисовки
    QGraphicsView::resizeEvent(event);  // Запускаем событие родителького класса
}

void LevelTwoGraphic::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group) {
          delete item;
       }
    }
}

void LevelTwoGraphic::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        emit signalForbidKeys();
        emit signalMiniMenu2();
    }
}

void LevelTwoGraphic::Spawn1Preset()
{
    enemies_1_1 = new EnemiesPreset2();
    enemies_1_1->RectX = 600;

    enemies_1_2 = new EnemiesPreset2();
    enemies_1_2->RectX = 700;

    enemies_1_3 = new EnemiesPreset2();
    enemies_1_3->RectX = 800;

    enemies_1_4 = new EnemiesPreset2();
    enemies_1_4->RectX = 900;

    enemies_1_5 = new EnemiesPreset2();
    enemies_1_5->RectX = 1000;

    enemies_1_6 = new EnemiesPreset2();
    enemies_1_6->RectX = 1100;

    enemies_1_7 = new EnemiesPreset2();
    enemies_1_7->RectX = 1200;

    enemies_1_8 = new EnemiesPreset2();
    enemies_1_8->RectX = 1300;


    scene->addItem(enemies_1_1);
    scene->addItem(enemies_1_2);
    scene->addItem(enemies_1_3);
    scene->addItem(enemies_1_4);
    scene->addItem(enemies_1_5);
    scene->addItem(enemies_1_6);
    scene->addItem(enemies_1_7);
    scene->addItem(enemies_1_8);


    connect(EnemyTimer,&QTimer::timeout,enemies_1_1,&EnemiesPreset2::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_1_2,&EnemiesPreset2::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_1_3,&EnemiesPreset2::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_1_4,&EnemiesPreset2::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_1_5,&EnemiesPreset2::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_1_6,&EnemiesPreset2::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_1_7,&EnemiesPreset2::slotEnemiesTimer);
    connect(EnemyTimer,&QTimer::timeout,enemies_1_8,&EnemiesPreset2::slotEnemiesTimer);

    connect(Preset1Timer,&QTimer::timeout,enemies_1_1,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_1_1,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_1_1,&EnemiesPreset2::slotRunEnemies);

    connect(Preset1Timer,&QTimer::timeout,enemies_1_2,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_1_2,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_1_2,&EnemiesPreset2::slotRunEnemies);

    connect(Preset1Timer,&QTimer::timeout,enemies_1_3,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_1_3,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_1_3,&EnemiesPreset2::slotRunEnemies);

    connect(Preset1Timer,&QTimer::timeout,enemies_1_4,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_1_4,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_1_4,&EnemiesPreset2::slotRunEnemies);

    connect(Preset1Timer,&QTimer::timeout,enemies_1_5,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_1_5,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_1_5,&EnemiesPreset2::slotRunEnemies);

    connect(Preset1Timer,&QTimer::timeout,enemies_1_6,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_1_6,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_1_6,&EnemiesPreset2::slotRunEnemies);

    connect(Preset1Timer,&QTimer::timeout,enemies_1_7,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_1_7,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_1_7,&EnemiesPreset2::slotRunEnemies);

    connect(Preset1Timer,&QTimer::timeout,enemies_1_8,&EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_1_8,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_1_8,&EnemiesPreset2::slotRunEnemies);

    connect(enemies_1_1,&EnemiesPreset2::signalOutOfScreen,this,&LevelTwoGraphic::slotOutOfScreen);
    connect(enemies_1_8,&EnemiesPreset2::signalOutOfScreen,this,&LevelTwoGraphic::slotOutOfScreen);

    EndLimiter = 1;
}

void LevelTwoGraphic::Spawn2Preset()
{
    enemies_2_1 = new EnemiesPreset3();
    enemies_2_1->www = 30;

    enemies_2_2 = new EnemiesPreset3();
    enemies_2_2->RectX = -110;
    enemies_2_2->RectY = -110;
    enemies_2_2->www = 110;
    enemies_2_2->hhh = 20;
    enemies_2_2->BaseEnemyHeight3 = -110;
    enemies_2_2->BaseEnemyWidth3 = -110;

    enemies_2_3 = new EnemiesPreset3();
    enemies_2_3->RectX = -190;
    enemies_2_3->RectY = -190;
    enemies_2_3->www = 200;
    enemies_2_3->hhh = 20;
    enemies_2_3->BaseEnemyHeight3 = -190;
    enemies_2_3->BaseEnemyWidth3 = -190;

    enemies_2_4 = new EnemiesPreset3();
    enemies_2_4->RectX = -270;
    enemies_2_4->RectY = -270;
    enemies_2_4->www = 290;
    enemies_2_4->hhh = 20;
    enemies_2_4->BaseEnemyHeight3 = -270;
    enemies_2_4->BaseEnemyWidth3 =  -270;

    enemies_2_5 = new EnemiesPreset3();
    enemies_2_5->RectX = -360;
    enemies_2_5->RectY = -360;
    enemies_2_5->www = 370;
    enemies_2_5->hhh = 20;
    enemies_2_5->BaseEnemyHeight3 = -360;
    enemies_2_5->BaseEnemyWidth3 =  -360;

    enemies_2_6 = new EnemiesPreset3();
    enemies_2_6->RectX = -450;
    enemies_2_6->RectY = -450;
    enemies_2_6->www = 460;
    enemies_2_6->hhh = 20;
    enemies_2_6->BaseEnemyHeight3 = -450;
    enemies_2_6->BaseEnemyWidth3 =  -450;

    enemies_2_7 = new EnemiesPreset3();
    enemies_2_7->RectX = -540;
    enemies_2_7->RectY = -540;
    enemies_2_7->www = 550;
    enemies_2_7->hhh = 20;
    enemies_2_7->BaseEnemyHeight3 = -540;
    enemies_2_7->BaseEnemyWidth3 =  -540;

    enemies_2_8 = new EnemiesPreset3();
    enemies_2_8->RectX = -630;
    enemies_2_8->RectY = -630;
    enemies_2_8->www = 640;
    enemies_2_8->hhh = 20;
    enemies_2_8->BaseEnemyHeight3 = -630;
    enemies_2_8->BaseEnemyWidth3 =  -630;


    scene->addItem(enemies_2_1);
    scene->addItem(enemies_2_2);
    scene->addItem(enemies_2_3);
    scene->addItem(enemies_2_4);
    scene->addItem(enemies_2_5);
    scene->addItem(enemies_2_6);
    scene->addItem(enemies_2_7);
    scene->addItem(enemies_2_8);

    connect(EnemyTimer,&QTimer::timeout, enemies_2_1, &EnemiesPreset3::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_2_1,&EnemiesPreset3::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_2_1,&EnemiesPreset3::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_2_2,&EnemiesPreset3::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_2_2,&EnemiesPreset3::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_2_2,&EnemiesPreset3::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_2_3, &EnemiesPreset3::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_2_3,&EnemiesPreset3::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_2_3,&EnemiesPreset3::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_2_4, &EnemiesPreset3::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_2_4,&EnemiesPreset3::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_2_4,&EnemiesPreset3::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_2_5, &EnemiesPreset3::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_2_5,&EnemiesPreset3::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_2_5,&EnemiesPreset3::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_2_6, &EnemiesPreset3::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_2_6,&EnemiesPreset3::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_2_6,&EnemiesPreset3::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_2_7, &EnemiesPreset3::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_2_7,&EnemiesPreset3::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_2_7,&EnemiesPreset3::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_2_8, &EnemiesPreset3::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_2_8,&EnemiesPreset3::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_2_8,&EnemiesPreset3::slotRunEnemies);
}

void LevelTwoGraphic::Spawn3Preset()
{
    enemies_3_1 = new EnemiesPreset4();
    enemies_3_1->www = - 1000;
    enemies_3_1->hhh = 20;

    enemies_3_2 = new EnemiesPreset4();
    enemies_3_2->RectX = 1090;
    enemies_3_2->RectY = -140;
    enemies_3_2->www = -1090;
    enemies_3_2->hhh = 20;
    enemies_3_2->BaseEnemyHeight4 = -140;
    enemies_3_2->BaseEnemyWidth4 =  1090;

    enemies_3_3 = new EnemiesPreset4();
    enemies_3_3->RectX = 1180;
    enemies_3_3->RectY = -230;
    enemies_3_3->www = -1180;
    enemies_3_3->hhh = 20;
    enemies_3_3->BaseEnemyHeight4 = -230;
    enemies_3_3->BaseEnemyWidth4 =  1180;

    enemies_3_4 = new EnemiesPreset4();
    enemies_3_4->RectX = 1270;
    enemies_3_4->RectY = -320;
    enemies_3_4->www = -1270;
    enemies_3_4->hhh = 20;
    enemies_3_4->BaseEnemyHeight4 = -320;
    enemies_3_4->BaseEnemyWidth4 =  1270;

    enemies_3_5 = new EnemiesPreset4();
    enemies_3_5->RectX = 1360;
    enemies_3_5->RectY = -410;
    enemies_3_5->www = -1360;
    enemies_3_5->hhh = 20;
    enemies_3_5->BaseEnemyHeight4 = -410;
    enemies_3_5->BaseEnemyWidth4 =  1360;

    enemies_3_6 = new EnemiesPreset4();
    enemies_3_6->RectX = 1450;
    enemies_3_6->RectY = -500;
    enemies_3_6->www = -1450;
    enemies_3_6->hhh = 20;
    enemies_3_6->BaseEnemyHeight4 = -500;
    enemies_3_6->BaseEnemyWidth4 =  1450;

    enemies_3_7 = new EnemiesPreset4();
    enemies_3_7->RectX = 1540;
    enemies_3_7->RectY = -590;
    enemies_3_7->www = -1530;
    enemies_3_7->hhh = 20;
    enemies_3_7->BaseEnemyHeight4 = -590;
    enemies_3_7->BaseEnemyWidth4 =  1540;

    enemies_3_8 = new EnemiesPreset4();
    enemies_3_8->RectX = 1630;
    enemies_3_8->RectY = -680;
    enemies_3_8->www = -1630;
    enemies_3_8->hhh = 20;
    enemies_3_8->BaseEnemyHeight4 = -680;
    enemies_3_8->BaseEnemyWidth4 =  1630;



    scene->addItem(enemies_3_1);
    scene->addItem(enemies_3_2);
    scene->addItem(enemies_3_3);
    scene->addItem(enemies_3_4);
    scene->addItem(enemies_3_5);
    scene->addItem(enemies_3_6);
    scene->addItem(enemies_3_7);
    scene->addItem(enemies_3_8);

    connect(EnemyTimer,&QTimer::timeout, enemies_3_1, &EnemiesPreset4::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_2_8,&EnemiesPreset3::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_2_8,&EnemiesPreset3::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_3_2, &EnemiesPreset4::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_3_2,&EnemiesPreset4::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_3_2,&EnemiesPreset4::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_3_3, &EnemiesPreset4::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_3_3,&EnemiesPreset4::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_3_3,&EnemiesPreset4::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_3_4, &EnemiesPreset4::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_3_4,&EnemiesPreset4::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_3_4,&EnemiesPreset4::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_3_5, &EnemiesPreset4::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_3_5,&EnemiesPreset4::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_3_5,&EnemiesPreset4::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_3_6, &EnemiesPreset4::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_3_6,&EnemiesPreset4::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_3_6,&EnemiesPreset4::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_3_7, &EnemiesPreset4::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_3_7,&EnemiesPreset4::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_3_7,&EnemiesPreset4::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_3_8, &EnemiesPreset4::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_3_8,&EnemiesPreset4::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_3_8,&EnemiesPreset4::slotRunEnemies);

}

void LevelTwoGraphic::Spawn4Preset()
{
    enemies_4_1 = new EnemiesPreset5();
    enemies_4_1->www = -1500;

    enemies_4_2 = new EnemiesPreset5();
    enemies_4_2->RectX = 1700;
    enemies_4_2->www =  -1500;

    enemies_4_3 = new EnemiesPreset5();
    enemies_4_3->RectX = 1900;
    enemies_4_3->www =  -1500;

    enemies_4_4 = new EnemiesPreset5();
    enemies_4_4->RectX = 2100;
    enemies_4_4->www =  -1500;

    enemies_4_5 = new EnemiesPreset5();
    enemies_4_5->RectX = 2300;
    enemies_4_5->www =  -1500;

    enemies_4_6 = new EnemiesPreset5();
    enemies_4_6->RectX = 2500;
    enemies_4_6->www =  -1500;

    enemies_4_7 = new EnemiesPreset5();
    enemies_4_7->RectX = 2700;
    enemies_4_7->www =  -1500;

    enemies_4_8 = new EnemiesPreset5();
    enemies_4_8->RectX = 2900;
    enemies_4_8->www =  -1500;



    scene->addItem(enemies_4_1);
    scene->addItem(enemies_4_2);
    scene->addItem(enemies_4_3);
    scene->addItem(enemies_4_4);
    scene->addItem(enemies_4_5);
    scene->addItem(enemies_4_6);
    scene->addItem(enemies_4_7);
    scene->addItem(enemies_4_8);

    connect(EnemyTimer,&QTimer::timeout, enemies_4_1, &EnemiesPreset5::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_4_1,&EnemiesPreset5::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_4_1,&EnemiesPreset5::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_4_2, &EnemiesPreset5::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_4_2,&EnemiesPreset5::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_4_2,&EnemiesPreset5::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_4_3, &EnemiesPreset5::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_4_3,&EnemiesPreset5::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_4_3,&EnemiesPreset5::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_4_4, &EnemiesPreset5::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_4_4,&EnemiesPreset5::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_4_4,&EnemiesPreset5::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_4_5, &EnemiesPreset5::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_4_5,&EnemiesPreset5::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_4_5,&EnemiesPreset5::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_4_6, &EnemiesPreset5::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_4_6,&EnemiesPreset5::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_4_6,&EnemiesPreset5::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_4_7, &EnemiesPreset5::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_4_7,&EnemiesPreset5::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_4_7,&EnemiesPreset5::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_4_8, &EnemiesPreset5::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_4_8,&EnemiesPreset5::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_4_8,&EnemiesPreset5::slotRunEnemies);

    Preset5Timer->setSingleShot(true);
    Preset5Timer->start(5500);

}

void LevelTwoGraphic::Spawn5Preset()
{
    enemies_5_1 = new EnemiesPreset2();
    enemies_5_1->RectX = 100;

    enemies_5_2 = new EnemiesPreset2();
    enemies_5_2->RectX = 200;
    enemies_5_2->RectY = -230;
    enemies_5_2->BaseEnemyHeight2 = -160;

    enemies_5_3 = new EnemiesPreset2();
    enemies_5_3->RectX = 300;
    enemies_5_3->RectY = -360;
    enemies_5_3->BaseEnemyHeight2 = -290;

    enemies_5_4 = new EnemiesPreset2();
    enemies_5_4->RectX = 400;
    enemies_5_4->RectY = -490;
    enemies_5_4->BaseEnemyHeight2 = -420;

    enemies_5_5 = new EnemiesPreset2();
    enemies_5_5->RectX = 500;
    enemies_5_5->RectY = -620;
    enemies_5_5->BaseEnemyHeight2 = -550;

    enemies_5_6 = new EnemiesPreset2();
    enemies_5_6->RectX = 600;
    enemies_5_6->RectY = -750;
    enemies_5_6->BaseEnemyHeight2 = -680;

    enemies_5_7 = new EnemiesPreset2();
    enemies_5_7->RectX = 700;
    enemies_5_7->RectY = -880;
    enemies_5_7->BaseEnemyHeight2 = -810;

    enemies_5_8 = new EnemiesPreset2();
    enemies_5_8->RectX = 800;
    enemies_5_8->RectY = -1000;
    enemies_5_8->BaseEnemyHeight2 = -940;

    enemies_5_9 = new EnemiesPreset2();
    enemies_5_9->RectX = 900;
    enemies_5_9->RectY = -1130;
    enemies_5_9->BaseEnemyHeight2 = -1070;

    enemies_5_10 = new EnemiesPreset2();
    enemies_5_10->RectX = 1000;
    enemies_5_10->RectY = -1250;
    enemies_5_10->BaseEnemyHeight2 = -1200;

    enemies_5_11 = new EnemiesPreset2();
    enemies_5_11->RectX = 1100;
    enemies_5_11->RectY = -1380;
    enemies_5_11->BaseEnemyHeight2 = -1330;

    enemies_5_12 = new EnemiesPreset2();
    enemies_5_12->RectX = 1200;
    enemies_5_12->RectY = -1510;
    enemies_5_12->BaseEnemyHeight2 = -1460;


    scene->addItem(enemies_5_1);
    scene->addItem(enemies_5_2);
    scene->addItem(enemies_5_3);
    scene->addItem(enemies_5_4);
    scene->addItem(enemies_5_5);
    scene->addItem(enemies_5_6);
    scene->addItem(enemies_5_7);
    scene->addItem(enemies_5_8);
    scene->addItem(enemies_5_9);
    scene->addItem(enemies_5_10);
    scene->addItem(enemies_5_11);
    scene->addItem(enemies_5_12);


    connect(EnemyTimer,&QTimer::timeout, enemies_5_1, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_1,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_1,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_2, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_2,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_2,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_3, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_3,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_3,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_4, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_4,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_4,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_5, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_5,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_5,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_6, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_6,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_6,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_7, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_7,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_7,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_8, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_8,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_8,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_9, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_9,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_9,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_10, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_10,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_10,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_11, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_11,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_11,&EnemiesPreset2::slotRunEnemies);

    connect(EnemyTimer,&QTimer::timeout, enemies_5_12, &EnemiesPreset2::slotEnemiesTimer);
    connect(this,&LevelTwoGraphic::signalForbidKeys,enemies_5_12,&EnemiesPreset2::slotFreezeEnemies);
    connect(this,&LevelTwoGraphic::signalAllowKeysSecond,enemies_5_12,&EnemiesPreset2::slotRunEnemies);

    connect(enemies_5_10,&EnemiesPreset2::signalOutOfScreen,this,&LevelTwoGraphic::slotEndLevel);
    EndTimer->start(4000);

}
