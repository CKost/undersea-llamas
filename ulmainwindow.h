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

#include "chests.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "world.h"
#include "worldgenerator.h"

#include <QMainWindow>

namespace Ui {
class ULMainWindow;
}

class ULMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ULMainWindow(QWidget *parent = 0);
    ~ULMainWindow();
    
private slots:
    void on_buttonInstructions_clicked();

private:
    Ui::ULMainWindow *ui;
};

#endif // ULMAINWINDOW_H
