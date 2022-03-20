#include "changestage2.h"

ChangeStage2::ChangeStage2(QWidget*parent):
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
    connect(timer,&QTimer::timeout,this,&ChangeStage2::slotStageThree);
    Retimer->start(0);
    connect(Retimer,&QTimer::timeout,this,&ChangeStage2::slotChangeStage);
}

ChangeStage2::~ChangeStage2()
{

}

void ChangeStage2::slotChangeStage()
{
    int Width = this->width();      // определяем ширину нашего виджета
    int Height = this->height();
    int MenuWidth = Width/2.45;
    int MenuHeight = Height/3;    // определяем высоту нашего виджета

    QPen ScenePen(QColor::fromRgb(9,0,77));
    scene->addRect(0,0,Width,Height,ScenePen,QBrush(QColor::fromRgb(9,0,77)));

    QFont mfont = QFont("UpheavalPro-Regular", 32, QFont::Bold);

    QGraphicsTextItem * StringStage = new QGraphicsTextItem("boss level");
    StringStage->setDefaultTextColor(QColor::fromRgb(235,34,106));
    StringStage->setPos(MenuWidth ,MenuHeight+140);
    StringStage->setFont(mfont);
    scene->addItem(StringStage);
    if(TimerLimiter){
        TimerLimiter = false;
        timer->start(3000);
    }

}

void ChangeStage2::slotStageThree()
{
    emit signalStageThree();
}
