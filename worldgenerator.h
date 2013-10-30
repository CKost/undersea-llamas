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
#include <string>

class WorldGenerator
{
    vector<string> tile1 {"OOBB",
                          "OOTB",
                          "OBBB",
                          "OOOO"};
    vector<string> tile2 {"BBOO",
                          "BTOO",
                          "BBBO",
                          "OOOO"};
    vector<string> tile3 {"OOOO",
                          "OOBO",
                          "BTBO",
                          "BBBO"};
    vector<string> tile4 {"OOOO",
                          "OBOO",
                          "OBTB",
                          "OBBB"};

};

#endif // WORLDGENERATOR_H
