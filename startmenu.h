#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

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


// Расширяем класс QGraphicsView
class StartMenu : public QGraphicsView // главное меню
{
    Q_OBJECT


public:
    explicit StartMenu(QWidget *parent = 0);
    ~StartMenu();

    int MenuParagraphChange(int MenuParagraphCounter );
    void FireSignal();
    int StartGameIndicator;
private:
    int MenuParagraphCounter;
    int TempPointer;
    bool InMenuIndicator;

signals:
    void signalStartGame();

private slots:
    void slotStartMenu();  /* слот для обработчика переполнения таймера
                             * в нём будет производиться перерисовка
                             * виджета
                                */

public:
    void keyPressEvent(QKeyEvent *event);


private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsItemGroup  *group_1;
       // Объявляем первую группу элементов

    QPixmap MenuPointerPixmap = QPixmap(":/images/pngtree-cursor-icon-for-your-project-png-image_1904905.jpg");
    QPixmap MenuPointerScaledPixmap = MenuPointerPixmap.scaled(QSize(50,50));
    QFont mfont = QFont("UpheavalPro-Regular", 32, QFont::Bold);  
    QGraphicsPixmapItem* MenuParagraphPointer;

    QTimer * timer;

    int ReturnLimiter = 1;

    void resizeEvent(QResizeEvent *event);


    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);
};

#endif // MYGRAPHICVIEW_H
