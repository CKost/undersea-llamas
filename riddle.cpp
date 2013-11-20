/***************************************************************************
**
**  riddle.cpp
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "chest.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"

#include <QString>

using namespace std;

vector<QString> Riddle::riddles;

//This will hold all the contents of the riddle vector that is defined in the riddle.h header file
QString Riddle::riddle1="What do you add to a barrel to make it lighter?%holes";
QString Riddle::riddle2="What goes around the house and in the house, but never touches the house?%sun";
QString Riddle::riddle3="The more you take, the more you leave behind. What are they?%footsteps";
QString Riddle::riddle4="One word in this sentence is misspelled. What word is it?%misspelled";
QString Riddle::riddle5="What goes up and never comes down?%age";
QString Riddle::riddle6="You do not want to have them, but when you do have them, you do not want to lose them. What are they?%lawsuits";
QString Riddle::riddle7="What's the fewest number of chairs you would need around a table to seat four fathers, two grandfathers, and four sons?%four";
QString Riddle::riddle8="What was the biggest island in the world before the discovery of Australia by Captain Cook?%Australia";
QString Riddle::riddle9="What spends the day at the window, goes to the table for meals, and hides at night?%flies";
QString Riddle::riddle10="What is that which goes with a carriage, comes with a carriage, is of no use to a carriage, and yet the carriage cannot go without it?%noise";
QString Riddle::riddle11="What do you break when you name it?%silence";

//Load Riddles
void Riddle::add_riddlesToriddles()
{
    riddles.push_back(riddle1);
    riddles.push_back(riddle2);
    riddles.push_back(riddle3);
    riddles.push_back(riddle4);
    riddles.push_back(riddle5);
    riddles.push_back(riddle6);
    riddles.push_back(riddle7);
    riddles.push_back(riddle8);
    riddles.push_back(riddle9);
    riddles.push_back(riddle10);
    riddles.push_back(riddle11);
}

//Return a random riddle
QString Riddle::get_riddle()
{
    QString ranRiddle;
    ranRiddle=riddles[rand() % 11];
    return ranRiddle;
}
