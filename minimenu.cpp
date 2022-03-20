#include "minimenu.h"

MiniMenu::MiniMenu(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    this->setMinimumHeight(this->height());
    this->setMinimumWidth(this->width());

    scene = new QGraphicsScene();
    group = new QGraphicsItemGroup();
    this->setScene(scene);
    scene->addItem(group);
    timerMiniMenu = new QTimer();
    timerMiniMenu->start(3);
    connect(timerMiniMenu, &QTimer::timeout, this, &MiniMenu::slotMiniMenu);
    MiniMenuParagraphCounter = 1;


}

MiniMenu::~MiniMenu()
{

}

int MiniMenu::MiniMenuParagraphMove(int parcounter)
{
    if(parcounter>2){
        parcounter = 1;
    }
    if(parcounter < 1){
        parcounter = 2;
    }
    return parcounter;
}

void MiniMenu::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up){
        MiniMenuParagraphCounter++;
        MiniMenuParagraphCounter = MiniMenuParagraphMove(MiniMenuParagraphCounter);
        slotMiniMenu();
    }
    if(event->key() == Qt::Key_Down){
        MiniMenuParagraphCounter--;
        MiniMenuParagraphCounter = MiniMenuParagraphMove(MiniMenuParagraphCounter);
        slotMiniMenu();
    }

    if(event->key() == Qt::Key_Return){
        switch(MiniMenuParagraphCounter){
        case 1:
            emit signalContinue();
            break;
        case 2:
            emit signalBackToMainMenu();
            break;
        }
    }
}

void MiniMenu::slotMiniMenu()
{
    this->deleteItemsFromGroup(group);
    int Width = this->width();      // определяем ширину нашего виджета
    int Height = this->height();
    int MenuWidth = Width/2.45;
    int MenuHeight = Height/3;    // определяем высоту нашего виджета

    QPen ScenePen(QColor::fromRgb(9,0,77));
    group->addToGroup(scene->addRect(0,0,Width,Height,ScenePen,QBrush(QColor::fromRgb(9,0,77))));
    MiniMenuPointerItem = scene->addPixmap(MiniMenuPointerScaledPixmap);
    group->addToGroup(MiniMenuPointerItem);

//    scene->addItem(MiniMenuPointerItem);
    switch(MiniMenuParagraphCounter){

    case 1:
        MiniMenuPointerItem->setOffset(MenuWidth - 140, MenuHeight+150);
        break;
    case 2:
        MiniMenuPointerItem->setOffset(MenuWidth -90, MenuHeight+220);
        break;

    }



    QFont mfont = QFont("UpheavalPro-Regular", 32, QFont::Bold);

    QGraphicsTextItem * StringContinue = new QGraphicsTextItem("continue game");
    StringContinue->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringContinue->setPos(MenuWidth - 50,MenuHeight+140);
    StringContinue->setFont(mfont);

    QGraphicsTextItem * StringQuit = new QGraphicsTextItem("to main menu");
    StringQuit->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringQuit->setPos(MenuWidth - 27,MenuHeight+210);
    StringQuit->setFont(mfont);

    scene->addItem(StringContinue);
    scene->addItem(StringQuit);

}


void MiniMenu::deleteItemsFromGroup(QGraphicsItemGroup *group)
{

    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}
