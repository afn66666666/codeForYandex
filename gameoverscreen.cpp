#include "gameoverscreen.h"

GameOverScreen::GameOverScreen(QWidget*parent):
    QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    this->setMinimumHeight(this->height());
    this->setMinimumWidth(this->width());


    scene = new QGraphicsScene();
    timer = new QTimer();
    Retimer = new QTimer();

    this->setScene(scene);
    connect(timer,&QTimer::timeout,this,&GameOverScreen::slotReturnToMenu);
    Retimer->start(0);
    connect(Retimer,&QTimer::timeout,this,&GameOverScreen::slotGameOver);

}

GameOverScreen::~GameOverScreen()
{

}

void GameOverScreen::slotGameOver()
{
    int Width = this->width();      // определяем ширину нашего виджета
    int Height = this->height();
    int MenuWidth = Width/2.45;
    int MenuHeight = Height/3;    // определяем высоту нашего виджета

    QPen ScenePen(QColor::fromRgb(9,0,77));
    scene->addRect(0,0,Width,Height,ScenePen,QBrush(QColor::fromRgb(9,0,77)));

    QFont mfont = QFont("UpheavalPro-Regular", 32, QFont::Bold);

    QGraphicsTextItem * StringStage = new QGraphicsTextItem("Game Over");
    StringStage->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringStage->setPos(MenuWidth - 40,MenuHeight);
    StringStage->setFont(mfont);

    QGraphicsTextItem * StringScores = new QGraphicsTextItem("Your score:");
    StringScores->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringScores->setPos(MenuWidth - 60,MenuHeight + 80);
    StringScores->setFont(mfont);

    QGraphicsTextItem * StringNumber = new QGraphicsTextItem(QString::number(Scores));
    StringNumber->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringNumber->setPos(MenuWidth + 290,MenuHeight + 80);
    StringNumber->setFont(mfont);

    scene->addItem(StringStage);
    scene->addItem(StringScores);
    scene->addItem(StringNumber);

    if(TimerLimiter){
        TimerLimiter = false;
        timer->start(3000);
    }

}

void GameOverScreen::slotReturnToMenu()
{
    emit signalReturnToMenu();
}
