#ifndef BOSS_H
#define BOSS_H


#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>



class Boss : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Boss(QObject *parent = 0);
    ~Boss();


signals:
    void signalDamageOn(int i);
    void signalGameWin();



private:

    QTimer * SpawnTimer;

    QPixmap BossPixmap = QPixmap(":/images/tumblr_mmv8c3IiTO1sqhtkyo1_250.png");
    QPixmap BossPixmapScaled = BossPixmap.scaled(800,500);
    QGraphicsPixmapItem * BossPixmapItem;



    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QGraphicsItem *LaserItem;
    QPixmap LaserPixmap = QPixmap(":/images/816-8162960_laser-beam-laser-sprite-pixel-art.png");
    QPixmap LaserPixmapScaled = LaserPixmap.scaled(200,700);
    QGraphicsPixmapItem * LaserPixmapItem;

    QTimer * ShootTimer;
    QTimer * PrepareTimer;

    int ShootIndicator;
    int BeginEnemies;
    bool PaintIndicator;
    int BossLifes;


public slots:
    void slotShooting();
    void slotFreezeEnemies();
    void slotRunEnemies();
    void slotBossDamage();

};

#endif // BOSS_H
