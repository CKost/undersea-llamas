/**************************************************************************
**
**   stateengine.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "stateengine.h"
#include "riddle.h"
#include <iostream>
#include <fstream>

using namespace std;

StateEngine StateEngine::inst;

StateEngine StateEngine::instance() { return inst; }

vector<QString> StateEngine::getRiddle()
{
    throw "Dude, totally not implemented.";
    //TODO: GET CURT TO IMPLEMENT RIDDLE RETRIEVAL
}

void StateEngine::saveToFile(QString filename)
{
    ofstream rvr(filename.toWCharArray());
    rvr << "[ULState File v1.0]" << endl; //Important: this signature is used for validation.
    rvr << "beginllamas" << endl;
    rvr <<
}
