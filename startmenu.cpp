#include "startmenu.h"
#include <mainwindow.h>

StartMenu::StartMenu(QWidget *parent)
    : QGraphicsView(parent)
{

    /* Немного поднастроим отображение виджета и его содержимого */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    /* Также зададим минимальные размеры виджета
     * */

    this->setMinimumHeight(this->height());
    this->setMinimumWidth(this->width());

    scene = new QGraphicsScene();   // Инициализируем сцену для отрисовки
    this->setScene(scene);          // Устанавливаем сцену в виджет

    group_1 = new QGraphicsItemGroup();
    // Инициализируем первую группу элементов
     // Инициализируем вторую группу элементов

    scene->addItem(group_1);
    // Добавляем первую группу в сцену
               // Добавляем вторую группу в сцену

//    QPixmap MenuPointerPixmap = QPixmap(":/images/pngtree-cursor-icon-for-your-project-png-image_1904905.jpg");

    timer = new QTimer();               // Инициализируем Таймер
    timer->setSingleShot(true);
    // Подключаем СЛОТ для отрисовки к таймеру
    timer->start(3);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotStartMenu()));


    MenuParagraphCounter = 1;
    TempPointer = 0;
    StartGameIndicator = 0;
    InMenuIndicator = true;
}

StartMenu::~StartMenu()
{

}


int StartMenu::MenuParagraphChange(int MenuParagraphCounter)
{
    if(MenuParagraphCounter == 6){
        MenuParagraphCounter = 1;
    }

    if(MenuParagraphCounter == 0){
        MenuParagraphCounter = 5;
    }
//    if(MenuParagraphCounter == 11 || MenuParagraphCounter == 9){
//        return 10;
//    }
    return MenuParagraphCounter;
}

void StartMenu::FireSignal()
{
    emit signalStartGame();
}


void StartMenu::slotStartMenu(){

    /* Удаляем все элементы со сцены,
     * если они есть перед новой отрисовкой
     * */
    this->deleteItemsFromGroup(group_1);

    int Width = this->width();      // определяем ширину нашего виджета
    int Height = this->height();    // определяем высоту нашего виджета
    int MenuWidth = Width/2.45;
    int MenuHeight = Height/3;
    /* Устанавливаем размер сцены по размеру виджета
     * Первая координата - это левый верхний угол,
     * а Вторая - это правый нижний угол
     * */
    scene->setSceneRect(0,0,Width,Height);

    /* Приступаем к отрисовке произвольной картинки
     * */


    /* Нарисуем черный прямоугольник
     * */

    MenuParagraphPointer = scene->addPixmap(MenuPointerScaledPixmap);

    switch(MenuParagraphCounter){
    case 1:

        MenuParagraphPointer->setOffset(MenuWidth - 70 ,MenuHeight+10);
        break;
    case 2:

        MenuParagraphPointer->setOffset(MenuWidth - 70, MenuHeight + 80);
        break;

    case 3:
        MenuParagraphPointer->setOffset(MenuWidth - 30, MenuHeight + 150);
        break;

    case 4:
        MenuParagraphPointer->setOffset(MenuWidth - 10, MenuHeight + 220);
        break;

    case 5:
        MenuParagraphPointer->setOffset(MenuWidth+20, MenuHeight + 290);
        break;
    }


    QGraphicsTextItem * StringStartGame = new QGraphicsTextItem("start game");
    StringStartGame->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringStartGame->setPos(MenuWidth,MenuHeight);
    StringStartGame->setFont(mfont);


    QGraphicsTextItem * StringAboutGame = new QGraphicsTextItem("about game");
    StringAboutGame->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringAboutGame->setPos(MenuWidth,MenuHeight+70);
    StringAboutGame->setFont(mfont);


    QGraphicsTextItem * StringRecords = new QGraphicsTextItem("records");
    StringRecords->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringRecords->setPos(MenuWidth+45,MenuHeight+140);
    StringRecords->setFont(mfont);


    QGraphicsTextItem * StringAuthor = new QGraphicsTextItem("Author");
    StringAuthor->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringAuthor->setPos(MenuWidth+60,MenuHeight+210);
    StringAuthor->setFont(mfont);


    QGraphicsTextItem * StringQuit = new QGraphicsTextItem("Quit");
    StringQuit->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringQuit->setPos(MenuWidth+100,MenuHeight+280);
    StringQuit->setFont(mfont);


    QPen ScenePen(QColor::fromRgb(9,0,77));
    group_1->addToGroup(scene->addRect(0,0,Width,Height,ScenePen,QBrush(QColor::fromRgb(9,0,77))));

    group_1->addToGroup(StringStartGame);
    group_1->addToGroup(StringAboutGame);
    group_1->addToGroup(StringRecords);
    group_1->addToGroup(StringAuthor);
    group_1->addToGroup(StringQuit);


    group_1->addToGroup(MenuParagraphPointer);

}



    /* Этим методом перехватываем событие изменения размера виджет
     * */
    void StartMenu::resizeEvent(QResizeEvent *event)
    {
        timer->start(3);   // Как только событие произошло стартуем таймер для отрисовки
        QGraphicsView::resizeEvent(event);  // Запускаем событие родителького класса
    }


/* Метод для удаления всех элементов из группы
 * */
void StartMenu::deleteItemsFromGroup(QGraphicsItemGroup *group)
{

    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}




