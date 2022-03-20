#ifndef CHANGESTAGE2_H
#define CHANGESTAGE2_H


#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>

class ChangeStage2: public QGraphicsView
{
    Q_OBJECT
public:
    ChangeStage2(QWidget *parent = 0);
    ~ChangeStage2();


private:
    QGraphicsScene * scene;
    QGraphicsItemGroup * group;
    QTimer * timer;
    QTimer * Retimer;

    bool TimerLimiter = true;

signals:
    void signalStageThree();
public slots:
    void slotChangeStage();

private slots:
    void slotStageThree();
};

#endif // CHANGESTAGE2_H
