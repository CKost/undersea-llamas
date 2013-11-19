/**************************************************************************
**
**   moviedisplay.cpp
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "moviedisplay.h"
#include "ui_moviedisplay.h"

#include <QMovie>
#include <QLabel>
#include <QtMultimedia/QMediaPlayer>

MovieDisplay::MovieDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovieDisplay)
{
    ui->setupUi(this);

    //This block of code displays Llama gif when a riddle is anwsered correctly
    QMovie *movie = new QMovie("://images/pm8gm.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setGeometry(QRect(0,-75,300,300));
    processLabel->setMovie(movie);
    movie->start();

    //This block of codes plays a audio file when a riddle is anwsered correctly.
    //IMPORTANT::Audio path must be hard coded to location of file! Copy of .mp3 can be found in resource file
    QMediaPlayer *player = new QMediaPlayer(this);
    player->setVolume(50);
    player->setMedia(QUrl("http://shredder.resnet.bju/sound/649341_SOUNDDOGS__an.mp3"));
    player->play();
}

MovieDisplay::~MovieDisplay()
{
    delete ui;
}
