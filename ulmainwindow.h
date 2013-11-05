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
#include <QWidget>
#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMainWindow>



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
    void on_startButton_clicked();


private:
    Ui::ULMainWindow *ui;
    QLabel *llama;
    QLabel *chest;
    bool aKey;
    bool sKey;
    bool wKey;
    bool dKey;
    bool oKey;

};



#endif // ULMAINWINDOW_H
