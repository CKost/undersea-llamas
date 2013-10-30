/***************************************************************************
**
**  riddle.cpp
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "chests.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"
#include <cstdlib>

using namespace std;

//This will hold all the contents of the riddle vector that is defined in the riddle.h header file


//Add first riddle to vector. Anwser seperated from riddle with a percent sign


Riddle::add_riddlesToriddles(riddle_1);

Riddle::add_riddlesToriddles(riddle_2);

Riddle::add_riddlesToriddles(riddle_3);

string Riddle::get_riddle()
{
    string ranRiddle;
    riddles[rand() % 3]=ranRiddle;
    return ranRiddle;
}
