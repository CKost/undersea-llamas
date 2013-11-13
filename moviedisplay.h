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
