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
/**
 * @brief The MovieDisplay class is a dialog that shows a GIF to the user.
 */
class MovieDisplay : public QDialog
{
    Q_OBJECT

private:
    Ui::MovieDisplay *ui;
    
public:
    /** MovieDisplay constructor*/
    explicit MovieDisplay(QWidget *parent = 0);
    /** MovieDisplay destructor*/
    ~MovieDisplay();
};

#endif // MOVIEDISPLAY_H
