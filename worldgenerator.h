/**************************************************************************
**
**   worldgenerator.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include "chests.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "world.h"

#include <QObject>
#include <QString>

class WorldGenerator
{
public:
    vector<QString> tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9, tileA, tileB, tileC;
    WorldGenerator();
    bool generate(QString name);
};

#endif // WORLDGENERATOR_H
