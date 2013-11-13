#include "moviedisplay.h"
#include "ui_moviedisplay.h"
#include <QMovie>
#include <QLabel>

MovieDisplay::MovieDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovieDisplay)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie("://images/pm8gm.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setGeometry(QRect(0,-75,300,300));
    processLabel->setMovie(movie);
    movie->start();
    processLabel->show();
}

MovieDisplay::~MovieDisplay()
{
    delete ui;
}
