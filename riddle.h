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

#include <string>
#include <vector>
#include <iostream>
#include <QString>

using namespace std;

class Riddle
{
private:
   static std::vector<QString> riddles;
   // string riddle1,riddle2,riddle3;
static QString riddle1,riddle2,riddle3;
public:

/*
    //Constructor W/Riddles Set
    Riddle(string __riddle1="It wanders far, sometimes high sometimes low, but always finishs OK%CpS111_Grade",
           string _riddle2="What goes round the house and in the house but never touches the house%sun",
           string _riddle3="The more you take, the more you leave behind. What are they?%footsteps")
           :riddle1(__riddle1),riddle2(_riddle2),riddle3(_riddle3) {}

*/
      //Return size of riddle
      static int get_SizeRiddles(){ return riddles.size(); }
       //call to add riddles to riddle vector

       static void add_riddlesToriddles();
       //Get riddle method, generate random # and return that vector
       QString get_riddle();
};

#endif // RIDDLE_H
