#ifndef STATEENGINE_H
#define STATEENGINE_H

#include <QObject>
#include <vector>
#include <QTimer>
#include <QString>
#include "llama.h"

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
