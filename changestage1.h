#ifndef CHANGESTAGE1_H
#define CHANGESTAGE1_H


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

class ChangeStage: public QGraphicsView
{
    Q_OBJECT
public:
    ChangeStage(QWidget *parent = 0);
    ~ChangeStage();


private:
    QGraphicsScene * scene;
    QGraphicsItemGroup * group;
    QTimer * timer;
    QTimer * Retimer;

    bool TimerLimiter = true;

signals:
    void signalStageTwo();
public slots:
    void slotChangeStage();

private slots:
    void slotStageTwo();
};
#endif
