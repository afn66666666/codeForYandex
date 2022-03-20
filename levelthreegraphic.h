#ifndef LEVELTHREEGRAPHIC_H
#define LEVELTHREEGRAPHIC_H


#include "spaceship.h"
#include "minimenu.h"

#include "enemiespreset3.h"
#include "enemiespreset4.h"
#include "enemiespreset5.h"
#include "enemiespreset6.h"
#include "boss.h"
#include "bullet1.h"
#include "bullet2.h"

#include <QList>

class LevelThreeGraphic:public QGraphicsView
{
    Q_OBJECT
public:

    explicit LevelThreeGraphic(QWidget*parent = 0);

    ~LevelThreeGraphic();

    int LifesCounter;
signals:
    void signalBlock();
    void signalMiniMenu2();
    void signalForbidKeys();
    void signalAllowKeysSecond();
    void signalStartPreset2();
    void signalEnd();
    void signalEndLevel(int Scores);
    void signalEndGame(LevelThreeGraphic* item,int Scores);
    void signalGameWinScreen(int Scores);
public slots:

private slots:
    void DamageCheckSlot();
    void slotDamage();
    void slotLevelTwo();
    void slotDeleteSpaceship();
    void slotAllowKeys();
    void slotBossHit();
    void slotEndLevel();
    void slotGameWin();
    void slotGameWinScreen();

private:


    Boss                *boss;

    Bullet1             * bullet_1;
    Bullet2             * bullet_2;

    QGraphicsScene      *scene;     // РћР±СЉСЏРІР»СЏРµРј СЃС†РµРЅСѓ РґР»СЏ РѕС‚СЂРёСЃРѕРІРєРё
    QGraphicsItemGroup  *group_spaceship;
    QGraphicsItemGroup  *group_screen;
    QPixmap              ScreenPicture;
    QPixmap              LevelOneScaledPixmap;
    QGraphicsPixmapItem *LevelScreen;
    QGraphicsPixmapItem *LevelOneItemScreen;

    QTimer              *StartTimer;
    QTimer              *GameTimer;
    QTimer              *DamageCheckTimer;
    QTimer              *EndTimer;


    QPixmap              LevelOnePixmap;
    Spaceship           *SpaceshipPixmap;
    MiniMenu            *MiniMenu;

    QPixmap SpaceshipPixmapBegin = QPixmap(":/images/karablpro.png");
    QPixmap SpaceshipScaledPixmapBegin = SpaceshipPixmapBegin.scaled(QSize(150,100));
    QGraphicsPixmapItem* SpaceshipPixmapItemBegin;

    QPixmap LifesPixmap;
    QPixmap LifesPixmapScaled;
    QGraphicsItem * LifesPixmapItem;
    QGraphicsTextItem * Lifes;
    QGraphicsTextItem * Scores;

    QFont mfont = QFont("UpheavalPro-Regular", 32, QFont::Bold);

    int EndLimiter;
    int ReturnLimiter = 1;
    int MemoryDontLeakLimimter;
    bool TimerSetterLimiter;
    unsigned long int ScorePoints;
    void resizeEvent(QResizeEvent *event);
    void deleteItemsFromGroup(QGraphicsItemGroup *group);
    void keyPressEvent(QKeyEvent*event);



};

#endif // LEVELTHREEGRAPHIC_H
