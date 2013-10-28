/***************************************************************************
**
**  riddle.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

//This header file has the stuff for the vector which hold the vectors (that will be in riddle.cpp) that the user can call
#ifndef RIDDLE_H
#define RIDDLE_H

#include "chests.h"
#include "llama.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"

#include <vector>
#include <iostream>

using namespace std;

class Riddle
{
private:
    std::vector<string> riddles;

public:
            //Return size of riddle
            get_SizeRiddles(){return riddles.size();}
            //call to add riddles to riddle vector
             add_riddlesToriddles(string x){riddles.push_back(x);}

};

#endif // RIDDLE_H
