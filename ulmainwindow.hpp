/**************************************************************************
**
**   ulmainwindow.hpp
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef ULMAINWINDOW_HPP
#define ULMAINWINDOW_HPP

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
    
private:
    Ui::ULMainWindow *ui;
};

#endif // ULMAINWINDOW_HPP
