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

class StateEngine : public QObject
{
    Q_OBJECT

public:
    static StateEngine instance();
    Llama* getLlama(int id);
    vector<QString> getRiddle();
    void saveToFile(QString filename);
    void loadFromFile(QString filename);

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

signals:
    void tick(int numTicks);
private slots:
    void on_timer_timeout();
};

#endif // STATEENGINE_H
