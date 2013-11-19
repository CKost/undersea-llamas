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

/**
 * @brief The ULMainWindow class is the main window of the game.
 *
 * It is also the primary control class, in the gameUpdate method.
 */
class ULMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ULMainWindow(QWidget *parent = 0);
    ~ULMainWindow();
//    void SetPos(QPoint pnt,int x,int y); not sure why this is here. it is not defined, and commenting it out the program still compiles.
    /**
     * @brief keyPressEvent is called when a key is pressed.
     * @param keyevent The current state of the keyboard. (Kind of.)
     */
    void keyPressEvent(QKeyEvent *keyevent);
    /**
     * @brief keyReleaseEvent is called when a key is released.
     * @param keyevent The current state of the keyboard. (Kind of.)
     */
    void keyReleaseEvent(QKeyEvent *keyevent);
private slots:
    /**
     * @brief on_buttonInstructions_clicked is called when the user clicks the "How to Play" button.
     *
     * Displays a message box telling the user how to play the game.
     */
    void on_buttonInstructions_clicked();
    /**
     * @brief on_cheatButton_clicked is called when the user clicks the cheat mode button.
     *
     * Displays a message box warning the user about the morality of cheating, and then toggles cheat mode.
     */
    void on_cheatButton_clicked();
    /**
     * @brief on_hardStartButton_clicked is called when the user clicks the Hard button.
     *
     * Starts the game from the pre-defined hard file.
     */
    void on_hardStartButton_clicked();
    /**
     * @brief gameUpdate updates the state of the game.
     * @param elapsedTicks The number of ticks since the start of the game.
     *
     * This method redraws the world every tick, as well as checking for win/lose conditions and
     * docking the player's pesos for interest. It also moves the llamas when keys are pressed.
     */
    void gameUpdate(int elapsedTicks);
    /**
     * @brief riddler
     * @param riddle
     * @param anwser
     * @param peso
     */
    void riddler(QString riddle, QString anwser, int peso);
    QString usernameGrabber();

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
