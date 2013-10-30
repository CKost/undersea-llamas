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

#include <vector>
#include <QString>


using namespace std;
class Chest;
class WorldCell;

enum TerrainType{ROUGH,OPEN,OBSTACLE};

class World
{
public:
    World(int size);
    WorldCell* getCell(int x, int y);
    static void loadFromFile(QString filename);
    ~World();
    static World* instance() {return inst;}
    int getSize() { return size; }
private:
    vector<WorldCell*> cells;
    static World* inst;
    int size;
};


class WorldCell
{
private:
    TerrainType terraintype;
    Chest* chest;

public:
    //WorldCell constructor
    WorldCell(int newTerrainType, Chest* newContents) {
        terraintype = newTerrainType;
        chest = newContents;
    }

    WorldCell* getCell() { return this; }
    //Property: contents.
    Chest* getChest() { return chest; }
    void setContents(Chest* cnt) { chest = cnt; }

    //Property: terraintype.
    TerrainType getTerrainType() {return terraintype;}
    void setTerrainType(TerrainType type) {terraintype = type;}

    //WorldCell destructor
    ~WorldCell() { delete chest; }
};

#endif // WORLD_H
