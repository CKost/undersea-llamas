/**************************************************************************
**
**   stateengine.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef STATEENGINE_H
#define STATEENGINE_H

#include "chests.h"
#include "llama.h"
#include "riddle.h"
#include "world.h"
#include "worldgenerator.h"

#include <QObject>
#include <vector>
#include <QTimer>
#include <QString>
#include <string>

class Llama;
class StateEngine : public QObject
{
    Q_OBJECT

public:
    static StateEngine* instance();
    Llama* getLlama(int id);
    void saveToFile(QString filename);
    void loadFromFile(QString filename);
    void addLlama(QString username = "Player");

    void punishLlama(int llamaID, int livesToTake);
    void payLlama(int llamaID, int pesosToGive);
    void youAreTheWeakestLinkLlama(int llamaID);
    bool moveLlama(int llamaID, double x, double y);
    void openTChest(int llamaID, double x, double y);
    void openEChest(int llamaID, double x, double y);
    void openRChest(int llamaID, double x, double y);

    QString toStateString();
    void fromStateString(QString string);

private:
    StateEngine();
    Riddle riddleEngine;
    vector<Llama*> llamas;
    QString currentRiddle, currentAnswer;
    static StateEngine inst;
    QTimer clock;
    int numTicks;                                                                                   //numTicks perhaps requires some explanation. It's the variable storing the number
                                                                                                    //of elapsed ticks since the start of the game. (In other words, the timer.)
    string currentWorldFile;

signals:
    void tick(int numTicks);
    void askRiddle(QString riddle, QString answer, int pesos);
private slots:
    void on_timer_timeout();
};

class Highscore {
    QString name;
    int score;

    Highscore(QString initName, int initScore):score(initScore), name(initName) {}
    QString printAScore() {
        return QString::fromStdString(name.toStdString() + string(" ") + to_string(score));
    }
};

class HighscoreList {
    vector<Highscore> list;

public:
    HighscoreList();

    vector<Highscore> getList() {
        return list;
    }

    //adds a highscore to the list of highscores
    void addHighscore(string name, int score) {

    }
    void sort();

};

#endif // STATEENGINE_H
