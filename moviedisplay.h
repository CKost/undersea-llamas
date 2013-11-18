/**************************************************************************
**
**   moviedisplay.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef MOVIEDISPLAY_H
#define MOVIEDISPLAY_H

#include <QDialog>

namespace Ui {
class MovieDisplay;
}

class MovieDisplay : public QDialog
{
    Q_OBJECT
    
public:
    explicit MovieDisplay(QWidget *parent = 0);
    ~MovieDisplay();
    
private:
    Ui::MovieDisplay *ui;
};

#endif // MOVIEDISPLAY_H
