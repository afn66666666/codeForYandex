#ifndef LEVELONEGRAPHIC_H
#define LEVELONEGRAPHIC_H

#include <string>

#include "startmenu.h"
#include "spaceship.h"
#include "minimenu.h"


#include "enemiespreset1.h"
#include "enemiespreset2.h"


#include "changestage1.h"

#include "bullet1.h"
#include "bullet2.h"
#include <QList>


class LevelOneGraphic:public QGraphicsView
{
    Q_OBJECT
public:

    explicit LevelOneGraphic(QWidget*parent = 0);

    ~LevelOneGraphic();

signals:
    void signalBlock(); // block buttons
    void signalMiniMenu();  // minimenu
    void signalForbidKeys();
    void signalAllowKeysSecond();
    void signalStartPreset2();
    void signalEnd();  //
    void signalEndLevel(int Scores);
    void signalEndGame(LevelOneGraphic*item,int Scores);
public slots:
    void slotLevelOne();
    void slotDeleteSpaceship();
    void slotAllowKeys();
    void slotDamage();
    void slotKill(QGraphicsItem*item);
    void slotEndLevel();


private slots:

    void slotOutOfScreen();
private:

    EnemiesPreset1 * enemies_1;
    EnemiesPreset1 * enemies_2;
    EnemiesPreset1 * enemies_3;
    EnemiesPreset1 * enemies_4;
    EnemiesPreset1 * enemies_5;
    EnemiesPreset1 * enemies_6;

    EnemiesPreset2 * enemies_2_1;
    EnemiesPreset2 * enemies_2_2;
    EnemiesPreset2 * enemies_2_3;
    EnemiesPreset2 * enemies_2_4;
    EnemiesPreset2 * enemies_2_5;
    EnemiesPreset2 * enemies_2_6;
    EnemiesPreset2 * enemies_2_7;
    EnemiesPreset2 * enemies_2_8;

    Bullet1             * bullet_1;
    Bullet2             * bullet_2;

    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsItemGroup  *group_spaceship;
    QGraphicsItemGroup  *group_screen;
    QPixmap              ScreenPicture;
    QGraphicsPixmapItem *LevelScreen;

    QPixmap  LevelOnePixmap;
    QPixmap  LevelOneScaledPixmap;
    QGraphicsPixmapItem* LevelOneItemScreen;

    QTimer              *StartTimer;
    QTimer              *GameTimer;
    QTimer              *Preset2Timer;
    QTimer              *EnemyTimer;
    QTimer              *EndTimer;


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
    int LifesCounter;
    int MemoryDontLeakLimimter;
    bool DeleteItmesLimiter;
    bool aaa;
    unsigned long int ScorePoints;
    void resizeEvent(QResizeEvent *event);
    void deleteItemsFromGroup(QGraphicsItemGroup *group);
    void keyPressEvent(QKeyEvent*event);
    void Spawn2Preset();


};

#endif // LEVELONEGRAPHIC_H
