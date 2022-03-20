#include<startmenu.h>
#include "levelonegraphic.h"

void StartMenu::keyPressEvent(QKeyEvent *event) // попробовать через другой СЛОТ или через аргумент slotalarmtimer
{
    Q_UNUSED(event);
    if(event->key() == Qt::Key_Down){
        if(InMenuIndicator){
    MenuParagraphCounter++;
    MenuParagraphCounter = MenuParagraphChange(MenuParagraphCounter);
    if(MenuParagraphCounter != 10){
        slotStartMenu();
    }
        }

    }

    if(event->key() == Qt::Key_Up){
        if(InMenuIndicator){
        MenuParagraphCounter--;
        MenuParagraphCounter = MenuParagraphChange(MenuParagraphCounter);
        if(MenuParagraphCounter != 10){
            slotStartMenu();
        }
        }
    }

    if(event->key() == Qt::Key_Return){
        switch(MenuParagraphCounter){
        case 5:
            QApplication::quit();
            break;

        case 4:
        {
            TempPointer = 4;
            InMenuIndicator = false;
            MenuParagraphCounter = 10;
            deleteItemsFromGroup(group_1);
            QPen ScenePen(QColor::fromRgb(9,0,77));
            group_1->addToGroup(scene->addRect(0,0,this->width(),this->height(),ScenePen,QBrush(QColor::fromRgb(9,0,77))));
            QGraphicsTextItem* StringDev = new QGraphicsTextItem("kim ilya, m8o-111b-20, 2021");
            StringDev->setDefaultTextColor(QColor::fromRgb(235,34,106));
            StringDev->setPos(this->width()/2-350,this->height()-180);
            StringDev->setFont(mfont);
            group_1->addToGroup(StringDev);
            break;
        }
        case 3:
        {
            TempPointer = 3;
            InMenuIndicator = false;
            MenuParagraphCounter = 10;
            deleteItemsFromGroup(group_1);
            QPen ScenePen(QColor::fromRgb(9,0,77));
            group_1->addToGroup(scene->addRect(0,0,this->width(),this->height(),ScenePen,QBrush(QColor::fromRgb(9,0,77))));
            break;
        }
        case 2:
        {
            TempPointer = 2;
            InMenuIndicator = false;
            MenuParagraphCounter = 10;
            deleteItemsFromGroup(group_1);
            QPen ScenePen(QColor::fromRgb(9,0,77));
            group_1->addToGroup(scene->addRect(0,0,this->width(),this->height(),ScenePen,QBrush(QColor::fromRgb(9,0,77))));

            QGraphicsTextItem* StringControls_1 = new QGraphicsTextItem("up,down,left,right - spaceship movement");
            StringControls_1->setDefaultTextColor(QColor::fromRgb(235,34,106));
            StringControls_1->setPos(this->width()/5,this->height()/5);
            StringControls_1->setFont(mfont);
            group_1->addToGroup(StringControls_1);

            QGraphicsTextItem* StringControls_2 = new QGraphicsTextItem("ctrl - shoot");
            StringControls_2->setDefaultTextColor(QColor::fromRgb(235,34,106));
            StringControls_2->setPos(this->width()/5,this->height()/5 + 100);
            StringControls_2->setFont(mfont);
            group_1->addToGroup(StringControls_2);
            break;
        }


        case 1:
        {
            while(ReturnLimiter){
            StartGameIndicator = 1; 
            deleteItemsFromGroup(group_1);
            FireSignal();
            ReturnLimiter = 0;
            break;
            }
        }
}

}

    if(event->key() == Qt::Key_Escape){
        if(MenuParagraphCounter  == 10){
            InMenuIndicator = true;
            MenuParagraphCounter = TempPointer;
            slotStartMenu();
        }
        }
    }


