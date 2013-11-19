/***************************************************************************
**
**  riddle.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef RIDDLE_H
#define RIDDLE_H

#include <string>
#include <vector>
#include <iostream>
#include <QString>

using namespace std;
/**
 * @brief The Riddle class holds riddles.
 */
class Riddle
{
private:
    static std::vector<QString> riddles;
    static QString riddle1,riddle2,riddle3;

public:
    /** Gets the size of the riddles vector
     *@param none
     *@return int riddles.size()
     */
    static int get_SizeRiddles(){ return riddles.size(); }

    /** Adds riddles to the riddles vector (anwser seperated from riddle with a percent sign)
     *@param none
     *@return void
     */
    static void add_riddlesToriddles();

    /** Gets a random riddle from riddles vector
     *@param none
     *@return QString ranRiddle (random riddle)
     */
    QString get_riddle();
};

#endif // RIDDLE_H
