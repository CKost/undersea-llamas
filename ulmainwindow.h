/**************************************************************************
**
**   ulmainwindow.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef ULMAINWINDOW_H
#define ULMAINWINDOW_H
#include <QLabel>
#include "stateengine.h"
#include "worldgenerator.h"
#include "ui_ulmainwindow.h"
#include "llamalabel.h"
#include "llama.h"
#include "world.h"
#include "chestlabel.h"
#include "chests.h"
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
    void SetPos(QPoint pnt,int x,int y);
    void keyPressEvent(QKeyEvent *keyevent);
    void keyReleaseEvent(QKeyEvent *keyevent);
private slots:
    void on_buttonInstructions_clicked();
    void on_cheatButton_clicked();
    void on_easyStartButton_clicked();
    void on_hardStartButton_clicked();
    void gameUpdate(int elapsedTicks);

    //void on_easyStartButton_clicked();

    void on_btnLoadState_clicked();

    void on_btnSaveState_clicked();

    void on_btnCreateWorld_clicked();

private:
    Ui::ULMainWindow *ui;
    LlamaStats *llamaStats;
    LlamaLabel *llamaLabel;
    ChestLabel *chestLabel;
    ChestLabel *chestLabel2;
    ChestLabel *chestLabel3;
    QString currentUser;
    int playerID;
    //QLabel *chest;
    bool aKey;
    bool sKey;
    bool wKey;
    bool dKey;
    bool oKey;
    bool gameStarted;
    bool gameOver;

};

#endif // ULMAINWINDOW_H
