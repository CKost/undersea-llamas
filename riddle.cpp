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
/*vector<string> Riddle::riddles=new vector<string>();
 *@param <string> vector that holds strings of riddes.
 */
vector<QString> Riddle::riddles;

//This will hold all the contents of the riddle vector that is defined in the riddle.h header file
QString Riddle::riddle1="It wanders far, sometimes high sometimes low, but always finishs OK%CpS111_Grade";
QString Riddle::riddle2=" What goes round the house and in the house but never touches the house%sun";
QString Riddle::riddle3="The more you take, the more you leave behind. What are they?%footsteps";

/*Add riddles to vector. Anwser seperated from riddle with a percent sign
 *@param void method
 */

void Riddle::add_riddlesToriddles()
{
    riddles.push_back(riddle1);
    riddles.push_back(riddle2);
    riddles.push_back(riddle3);
}

/*Returns a random riddle
 *@param void method
 *@return a random riddle
 */

QString Riddle::get_riddle()
{
    QString ranRiddle;
    ranRiddle=riddles[rand() % 3];
    return ranRiddle;
}
