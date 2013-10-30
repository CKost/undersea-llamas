/***************************************************************************
**
**  riddle.cpp
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/
#include "riddle.h"
#include "chests.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"
#include <cstdlib>
#include <string>


using namespace std;

//This will hold all the contents of the riddle vector that is defined in the riddle.h header file


//Add riddles to vector. Anwser seperated from riddle with a percent sign
  void Riddle::add_riddlesToriddles()
  { riddles.push_back(riddle1);
    riddles.push_back(riddle2);
    riddles.push_back(riddle3);
  }



string Riddle::get_riddle()
{
    string ranRiddle;
    riddles[rand() % 3]=ranRiddle;
    return ranRiddle;
}
