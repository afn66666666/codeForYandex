#ifndef MINIMENU_H
#define MINIMENU_H

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

class MiniMenu:public QGraphicsView
{
    Q_OBJECT
public:
    MiniMenu(QWidget *parent = 0);
    ~MiniMenu();

signals:
    void signalBackToMainMenu();
    void signalContinue();
    void signalAllowKeys();
private:
    int MiniMenuParagraphMove(int parcounter);
    QGraphicsScene * scene;
    QGraphicsItemGroup * group;
    QTimer         * timerMiniMenu;

    QPixmap MiniMenuPointerPixmap = QPixmap(":/images/pngtree-cursor-icon-for-your-project-png-image_1904905.jpg");
    QPixmap MiniMenuPointerScaledPixmap = MiniMenuPointerPixmap.scaled(QSize(50,50));
    QGraphicsPixmapItem * MiniMenuPointerItem;

    int MiniMenuParagraphCounter;

    void keyPressEvent(QKeyEvent*event);
    void deleteItemsFromGroup(QGraphicsItemGroup *group);
private slots:
    void slotMiniMenu();
};

#endif // MINIMENU_H
