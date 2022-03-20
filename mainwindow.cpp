#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QtWidgets/QFileDialog>
#include <QtGui>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QPixmap pix(":/images/2066281(1).png"); // созданеие обьекта Qpixmap
    ui->label->SetScaledPixMap(pix);
    StartScreenLimiter = 1;
    Score = 0;
    scene = new QGraphicsScene;

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::keyPressEvent(QKeyEvent* keyevent)
{
    while(StartScreenLimiter){
    if(keyevent->key() == Qt::Key_Return){
        connect(this,&MainWindow::signalReturn,this,&MainWindow::slotReturn1);
        slotReturn1();
    }
    else
    {
        break;
    }
    }
}

void MainWindow::slotReturn1()
{


        StartScreenLimiter--;
        MainMenu   = new StartMenu();  /* Инициализируем виджет с графикой */
        /* и добавляем его на слой */
        ui->label->close();
//        ui->label->close();
        ui->gridLayout_2->addWidget(MainMenu);
        connect(MainMenu,&StartMenu::signalStartGame,this,&MainWindow::slotStartGame);
        MainMenu->setFocus(Qt::FocusReason::ActiveWindowFocusReason);


}

void MainWindow::slotStartGame()
{

    LevelOne = new LevelOneGraphic();
    connect(LevelOne,&LevelOneGraphic::signalMiniMenu,this,&MainWindow::slotMiniMenu);
    connect(LevelOne,&LevelOneGraphic::signalEndLevel,this,&MainWindow::slotChangeStage);
    connect(LevelOne,&LevelOneGraphic::signalEndGame,this,&MainWindow::slotGameOver);
    connect(MainMenu,&StartMenu::signalStartGame,LevelOne,&LevelOneGraphic::slotLevelOne);
    ui->gridLayout_2->removeWidget(MainMenu);
    ui->gridLayout_2->addWidget(LevelOne);

    MainMenu->close();
    delete MainMenu;
    LevelOne->setFocus(Qt::FocusReason::ActiveWindowFocusReason);

}

void MainWindow::slotBackToMainMenu1()
{
    ui->gridLayout_2->removeWidget(minimenu);
    ui->gridLayout_2->removeWidget(LevelOne);
    minimenu->close();
    LevelOne->close();
    delete minimenu;
    delete LevelOne;
    slotReturn1();
}

void MainWindow::slotBackToMainMenu2()
{
    ui->gridLayout_2->removeWidget(minimenu);
    ui->gridLayout_2->removeWidget(LevelTwo);
    minimenu->close();
    LevelTwo->close();
    delete minimenu;
    delete LevelTwo;
    slotReturn1();
}

void MainWindow::slotMiniMenu()
{
    ui->gridLayout_2->removeWidget(LevelOne);
    minimenu = new MiniMenu();
    connect(minimenu,&MiniMenu::signalBackToMainMenu,this,&MainWindow::slotBackToMainMenu1);
    connect(minimenu,&MiniMenu::signalContinue,this,&MainWindow::slotContinue);

    ui->gridLayout_2->addWidget(minimenu);
    minimenu->setFocus(Qt::FocusReason::ActiveWindowFocusReason);

}

void MainWindow::slotMiniMenu2()
{
    ui->gridLayout_2->removeWidget(LevelTwo);
    minimenu = new MiniMenu();
    connect(minimenu,&MiniMenu::signalBackToMainMenu,this,&MainWindow::slotBackToMainMenu2);
    connect(minimenu,&MiniMenu::signalContinue,this,&MainWindow::slotContinue2);

    ui->gridLayout_2->addWidget(minimenu);
    minimenu->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
}

void MainWindow::slotContinue()
{
    LevelOne->slotAllowKeys();
    ui->gridLayout_2->removeWidget(minimenu);
    minimenu->close();
    delete minimenu;
    ui->gridLayout_2->addWidget(LevelOne);
    LevelOne->setFocus(Qt::FocusReason::ActiveWindowFocusReason);

}

void MainWindow::slotContinue2()
{
    LevelTwo->slotAllowKeys();
    ui->gridLayout_2->removeWidget(minimenu);
    minimenu->close();
    delete minimenu;
    ui->gridLayout_2->addWidget(LevelTwo);
    LevelTwo->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
}




void MainWindow::slotReturn2()
{
    ui->gridLayout_2->removeWidget(gameover);
    delete gameover;
    slotReturn1();
}

void MainWindow::slotReturn3()
{
    ui->gridLayout_2->removeWidget(GameWin);
    delete GameWin;
    slotReturn1();
}

void MainWindow::slotChangeStage (int Scores)
{
    Score += Scores;
    ui->gridLayout_2->removeWidget(LevelOne);
    delete LevelOne;
    stage_2 = new ChangeStage;
    connect(stage_2,&ChangeStage::signalStageTwo,this,&MainWindow::slotStageTwo);
    ui->gridLayout_2->addWidget(stage_2);
    stage_2->slotChangeStage();
}

void MainWindow::slotChangeStage2(int Scores)
{
    Score += Scores;
    ui->gridLayout_2->removeWidget(LevelTwo);
    delete LevelTwo;
    stage_3 = new ChangeStage2;
    connect(stage_3,&ChangeStage2::signalStageThree,this,&MainWindow::slotStageThree);
    ui->gridLayout_2->addWidget(stage_3);
    stage_3->slotChangeStage();
}

void MainWindow::slotStageTwo()
{

    LevelTwo = new LevelTwoGraphic();
    connect(LevelTwo,&LevelTwoGraphic::signalMiniMenu2,this,&MainWindow::slotMiniMenu2);
    connect(LevelTwo,&LevelTwoGraphic::signalEndLevel,this,&MainWindow::slotChangeStage2);
    connect(LevelTwo,&LevelTwoGraphic::signalEndGame,this,&MainWindow::slotGameOver);
    ui->gridLayout_2->addWidget(LevelTwo);
    LevelTwo->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
    ui->gridLayout_2->removeWidget(stage_2);
        delete stage_2;
}

void MainWindow::slotStageThree()
{
    LevelThree = new LevelThreeGraphic();
    ui->gridLayout_2->addWidget(LevelThree);
    connect(LevelThree,&LevelThreeGraphic::signalGameWinScreen,this,&MainWindow::slotGameWinScreen);
    connect(LevelThree,&LevelThreeGraphic::signalEndGame,this,&MainWindow::slotGameOver);
    ui->gridLayout_2->removeWidget(stage_3);
    delete stage_3;
    ui->gridLayout_2->addWidget(LevelThree);
}

void MainWindow::slotGameWinScreen(int Scores)
{
    Score += Scores;
    ui->gridLayout_2->removeWidget(LevelThree);
    delete LevelThree;
    GameWin = new GameWinScreen();
    connect(GameWin,&GameWinScreen::signalReturnToMenu,this,&MainWindow::slotReturn3);
    GameWin->Scores = Score;
    GameWin->slotGameWIN();
    ui->gridLayout_2->addWidget(GameWin);
}

void MainWindow::slotGameOver(QWidget *item, int Scores)
{
    Score += Scores;
    ui->gridLayout_2->removeWidget(item);
    delete item;
    gameover = new GameOverScreen();
    connect(gameover,&GameOverScreen::signalReturnToMenu,this,&MainWindow::slotReturn2);
    gameover->Scores = Score;
    gameover->slotGameOver();
    ui->gridLayout_2->addWidget(gameover);

}




