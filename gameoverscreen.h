#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H


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
#include <QString>

class GameOverScreen: public QGraphicsView
{
    Q_OBJECT
public:
    GameOverScreen(QWidget *parent = 0);
    ~GameOverScreen();
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
    void slotGameOver();

private slots:
    void slotReturnToMenu();
};

#endif // GAMEOVERSCREEN_H
