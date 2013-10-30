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
#include "ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"

#include <QObject>
#include <vector>
#include <QTimer>
#include <QString>
#include <string>

class StateEngine : public QObject
{
    Q_OBJECT

public:
    static StateEngine instance();
    Llama* getLlama(int id);
    vector<QString> getRiddle();
    void saveToFile(QString filename);
    void loadFromFile(QString filename);
    void addLlama(int id, string username = "Player");

    void punishLlama(int llamaID);
    void payLlama(int llamaID);
    bool moveLlama(int llamaID, double x, double y);
    void openChest(int llamaID, double x, double y);

    QString toStateString();
    void fromStateString();

private:
    StateEngine();
    vector<Llama*> llamas;
    QString currentRiddle, currentAnswer;
    static StateEngine inst;
    QTimer clock;
    int numTicks;
    string currentWorldFile;

signals:
    void tick(int numTicks);
private slots:
    void on_timer_timeout();
};

class Highscore {
    QString name;
    int score;

    Highscore(QString initName, int initScore):score(initScore), name(initName) {}
    QString printAScore() {
        string output = to_string(name) + " " + to_string(score);
        QString output2 = output;
        return output2;
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
