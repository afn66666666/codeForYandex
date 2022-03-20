#ifndef ENEMIESPRESET1_H
#define ENEMIESPRESET1_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>



class EnemiesPreset1 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit EnemiesPreset1(QObject *parent = 0);
    ~EnemiesPreset1();

    int BaseEnemyWidth1;
    int RectX;
    int RectY;

signals:
    void signalControlSpaceShip();

private slots:
private:
    QRectF Form;
    int BeginEnemies;
    int FirstPingIndex;
    bool PaintAllowIndex;
    QTimer * SpawnTimer;

    QPixmap  EnemyPixmap =  QPixmap(":/images/enemyyy.png");
    QPixmap EnemyPixmapScaled = EnemyPixmap.scaled(180,100);

    QGraphicsItem * enemy1;
    QGraphicsPixmapItem* EnemyPixmapItem1;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;


    void paintEnemy1();



    int KillIndicator;

    int EnemyWidth1;



public slots:
    void slotEnemiesTimer();
    void slotFreezeEnemies();
    void slotRunEnemies();
    void slotDeleteEnemy();

};

#endif // ENEMIESPRESET1_H
