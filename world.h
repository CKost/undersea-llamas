/**************************************************************************
**
**   world.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef WORLD_H
#define WORLD_H

#include "chests.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "worldgenerator.h"

#include <vector>
#include <QString>

class WorldCell
{
public:
    WorldCell(int x, int y, int terraintype, Chest* contents);

    //Property: contents.
    Chest* getContents();
    void setContents(Chest* cnt);

    //Property: terraintype.
    int getTerrainType();
    void setTerrainType(int type);

    ~WorldCell() { delete contents; }
private:
    int x,y;
    int terraintype;
    Chest* contents;
};

class World
{
public:
    World(int size);
    WorldCell* getCell(int x, int y);
    static void loadFromFile(QString filename);
    ~World();
    static World* instance();
private:
    vector<WorldCell*> cells;
    static World* inst;
};

#endif // WORLD_H
