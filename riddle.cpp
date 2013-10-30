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

string riddle_1= "It wanders far, sometimes high sometimes low, but always finishs OK%CpS111_Grade";

string riddle_2="What goes round the house and in the house but never touches the house%sun";

string riddle_3="The more you take, the more you leave behind. What are they?%footsteps";

Riddle::add_riddlesToriddles(riddle_1);

Riddle::add_riddlesToriddles(riddle_2);

Riddle::add_riddlesToriddles(riddle_3);

string Riddle::get_riddle()
{
    string ranRiddle;
    riddles[rand() % 3]=ranRiddle;
    return ranRiddle;
}
