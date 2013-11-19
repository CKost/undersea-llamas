/**************************************************************************
**
**   ulmainwindow.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef ULMAINWINDOW_H
#define ULMAINWINDOW_H

#include "chest.h"
#include "chestlabel.h"
#include "llama.h"
#include "llamalabel.h"
#include "stateengine.h"
#include "ui_ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMainWindow>

class LlamaLabel;
class ChestLabel;
class LlamaStats;

class ULMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ULMainWindow(QWidget *parent = 0);
    ~ULMainWindow();
//    void SetPos(QPoint pnt,int x,int y); not sure why this is here. it is not defined, and commenting it out the program still compiles.
    void keyPressEvent(QKeyEvent *keyevent);
    void keyReleaseEvent(QKeyEvent *keyevent);
private slots:
    void on_buttonInstructions_clicked();
    void on_cheatButton_clicked();
    void on_hardStartButton_clicked();
    void gameUpdate(int elapsedTicks);
    void riddler(QString riddle, QString anwser, int peso);

    void on_btnLoadState_clicked();

    void on_btnSaveState_clicked();

    void on_btnCreateWorld_clicked();

    void on_hiscoreBtn_clicked();

private:
    Ui::ULMainWindow *ui;
    QString currentUser;
    int playerID;
    bool aKey;
    bool sKey;
    bool wKey;
    bool dKey;
    bool oKey;
    bool gameStarted;
    bool gameOver;
    void resetGame();
};

#endif // ULMAINWINDOW_H
