#ifndef LEVELTWOGRAPHIC_H
#define LEVELTWOGRAPHIC_H

#include "spaceship.h"
#include "minimenu.h"

#include "enemiespreset3.h"
#include "enemiespreset4.h"
#include "enemiespreset5.h"
#include "enemiespreset6.h"

#include "bullet1.h"
#include "bullet2.h"

#include <QList>

class LevelTwoGraphic:public QGraphicsView
{
    Q_OBJECT
public:

    explicit LevelTwoGraphic(QWidget*parent = 0);

    ~LevelTwoGraphic();

    int LifesCounter;
signals:
    void signalBlock();
    void signalMiniMenu2();
    void signalForbidKeys();
    void signalAllowKeysSecond();
    void signalStartPreset2();
    void signalEnd();
    void signalEndLevel(int Scores);
    void signalEndGame(LevelTwoGraphic* item,int Scores);
public slots:
    void slotLevelTwo();
    void slotDeleteSpaceship();
    void slotAllowKeys();
    void slotDamage();
    void slotKill(QGraphicsItem*item);
    void slotEndLevel();


private slots:

    void slotOutOfScreen();
    void Spawn1Preset();
    void Spawn2Preset();
    void Spawn3Preset();
    void Spawn4Preset();
    void Spawn5Preset();

private:

    EnemiesPreset2 * enemies_1_1;
    EnemiesPreset2 * enemies_1_2;
    EnemiesPreset2 * enemies_1_3;
    EnemiesPreset2 * enemies_1_4;
    EnemiesPreset2 * enemies_1_5;
    EnemiesPreset2 * enemies_1_6;
    EnemiesPreset2 * enemies_1_7;
    EnemiesPreset2 * enemies_1_8;
    EnemiesPreset2 * enemies_1_9;
    EnemiesPreset2 * enemies_1_10;

    EnemiesPreset2 * enemies_5_1;
    EnemiesPreset2 * enemies_5_2;
    EnemiesPreset2 * enemies_5_3;
    EnemiesPreset2 * enemies_5_4;
    EnemiesPreset2 * enemies_5_5;
    EnemiesPreset2 * enemies_5_6;
    EnemiesPreset2 * enemies_5_7;
    EnemiesPreset2 * enemies_5_8;
    EnemiesPreset2 * enemies_5_9;
    EnemiesPreset2 * enemies_5_10;
    EnemiesPreset2 * enemies_5_11;
    EnemiesPreset2 * enemies_5_12;

    EnemiesPreset3 * enemies_2_1;
    EnemiesPreset3 * enemies_2_2;
    EnemiesPreset3 * enemies_2_3;
    EnemiesPreset3 * enemies_2_4;
    EnemiesPreset3 * enemies_2_5;
    EnemiesPreset3 * enemies_2_6;
    EnemiesPreset3 * enemies_2_7;
    EnemiesPreset3 * enemies_2_8;

    EnemiesPreset4 * enemies_3_1;
    EnemiesPreset4 * enemies_3_2;
    EnemiesPreset4 * enemies_3_3;
    EnemiesPreset4 * enemies_3_4;
    EnemiesPreset4 * enemies_3_5;
    EnemiesPreset4 * enemies_3_6;
    EnemiesPreset4 * enemies_3_7;
    EnemiesPreset4 * enemies_3_8;

    EnemiesPreset5 * enemies_4_1;
    EnemiesPreset5 * enemies_4_2;
    EnemiesPreset5 * enemies_4_3;
    EnemiesPreset5 * enemies_4_4;
    EnemiesPreset5 * enemies_4_5;
    EnemiesPreset5 * enemies_4_6;
    EnemiesPreset5 * enemies_4_7;
    EnemiesPreset5 * enemies_4_8;


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
    QTimer              *EnemyTimer;
    QTimer              *EndTimer;

    QTimer              *Preset1Timer;
    QTimer              *Preset2Timer;
    QTimer              *Preset3Timer;
    QTimer              *Preset4Timer;
    QTimer              *Preset5Timer;

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

#endif // LEVELTWOGRAPHIC_H
