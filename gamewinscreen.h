#ifndef GAMEWINSCREEN_H
#define GAMEWINSCREEN_H


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
#include "gameoverscreen.h"
#include <iostream>
#include <fstream>
#include <string>

class GameWinScreen: public QGraphicsView
{
    Q_OBJECT
public:
    GameWinScreen(QWidget *parent = 0);
    ~GameWinScreen();

    int Scores;
    void RecordInFile(int Scores);


private:
    QGraphicsScene * scene;
    QGraphicsItemGroup * group;
    QTimer * timer;
    QTimer * Retimer;

    bool TimerLimiter = true;

signals:
    void signalReturnToMenu();
public slots:
    void slotGameWIN();

private slots:
    void slotReturnToMenu();
};

#endif // GAMEWINSCREEN_H
