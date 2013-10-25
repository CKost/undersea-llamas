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
    StateEngine();

private:
    static vector<Llama*> llamas;
    static QString currentRiddle, currentAnswer;

signals:
    void tick(int numTicks);
private slots:
    void on_timer_timeout();
};

#endif // STATEENGINE_H
