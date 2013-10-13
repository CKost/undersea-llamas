/**************************************************************************
**
**   ulmainwindow.hpp
**
**   This file copyright 2013 Alex Fischer.
**   Work done for CpS 111 at Bob Jones University.
**
**   You may use this file however you see fit, with one exception:
**   You may not pass this work off as your own.
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
