#ifndef MAINMENUBEGINSCENE_H
#define MAINMENUBEGINSCENE_H

#include <QMainWindow>
#include "startscreen.h"
#include <startmenu.h>

#include "levelonegraphic.h"
#include "leveltwographic.h"
#include "levelthreegraphic.h"
#include "gameoverscreen.h"
#include "gamewinscreen.h"
#include "changestage1.h"
#include "changestage2.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void StartScreenDelete();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    StartMenu        *MainMenu;

    LevelOneGraphic  *LevelOne;
    LevelTwoGraphic  *LevelTwo;
    LevelThreeGraphic*LevelThree;

    QGraphicsScene   *scene;
    MiniMenu         *minimenu;

    ChangeStage      *stage_2;
    ChangeStage2     *stage_3;

    GameOverScreen   *gameover;
    GameWinScreen    *GameWin;

    int Score;
//    LevelOneGraphic  * tmp;

signals:
    void signalReturn();
private slots:
    void slotMiniMenu();
    void slotMiniMenu2();

    void slotStartGame();

    void slotBackToMainMenu1();
    void slotBackToMainMenu2();

    void slotContinue();
    void slotContinue2();

    void slotReturn1();
    void slotReturn2();
    void slotReturn3();

    void slotChangeStage(int Scores);
    void slotChangeStage2(int Scores);

    void slotStageTwo();
    void slotStageThree();

    void slotGameWinScreen(int Scores);

    void slotGameOver(QWidget * item, int Scores);

private:
    int StartScreenLimiter;
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent* keyevent);




};
#endif // MAINMENUBEGINSCENE_H
