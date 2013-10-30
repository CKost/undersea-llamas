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

#include "stateengine.h"
#include "worldgenerator.h"
#include "ui_ulmainwindow.h"

#include <QMainWindow>

class ULMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ULMainWindow(QWidget *parent = 0);
    ~ULMainWindow();
    
private slots:
    void on_buttonInstructions_clicked();
    void on_cheatButton_clicked(); //Typed in, not auto-created by go to slot on UI screen :L
    void on_startButton_clicked();

private:
    Ui::ULMainWindow *ui;
};

#endif // ULMAINWINDOW_H
