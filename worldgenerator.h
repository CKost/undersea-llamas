/**************************************************************************
**
**   worldgenerator.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include "chest.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "world.h"

#include <QObject>
#include <QString>
/**
 * @brief The WorldGenerator class is a prodecural world generator.
 *
 * It uses a set of 12 pre-defined tiles, picks 16 randomly from those 12, and arranges them haphazardly in a way that will
 * not box the player in 9 times out of 10.
 */
class WorldGenerator
{
public:
    vector<QString> tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9, tileA, tileB, tileC;

    /** WorldGenerator constructor*/
    WorldGenerator();

    /** Creates a random world and saves it to a file.
     *@param name the name of the world file.
     *@return true if file written successfully, otherwise false
     */
    bool generate(QString name);
};

#endif // WORLDGENERATOR_H
