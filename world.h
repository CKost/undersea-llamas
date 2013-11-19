/**************************************************************************
**
**   world.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef WORLD_H
#define WORLD_H

#include "chest.h"

#include <vector>
#include <QString>

using namespace std;
class Chest;
class WorldCell;

enum TerrainType{ROUGH,OPEN,OBSTACLE};

class World
{
private:
    vector<WorldCell*> cells;
    static World* inst;
    int size;

public:
    /** World constructor*/
    World(int size);

    /** Gets a world cell with coordinates x, y
     *@param int x
     *@param int y
     *@return WorldCell pointer
     */
    WorldCell* getCell(int x, int y);
    /** Sets a world cell with coordinates <x>, <y>, as a <cell>
     *@param int x
     *@param int y
     *@param WorldCell* cell
     *@return void
     */
    void setCell(int x, int y, WorldCell* cell);
    /** Loads world from a file with name <filename>
     *@param QString filename
     *@return void
     */
    static void loadFromFile(QString filename);
    /** Loads world from a <string>
     *@param QString string
     *@return void
     */
    static void loadFromQString(QString string);

    /** World deconstructor*/
    ~World();

    /** Gets an instance of a world*/
    static World* instance() {return inst;}
    /** Gets the size of the world*/
    int getSize() { return size; }
    /** Deletes instance of the world and creates a new one*/
    static void reset() { delete inst; inst = new World(4); }
};


class WorldCell
{
private:
    TerrainType terraintype;
    Chest* chest;

public:
    /** WorldCell constructor*/
    WorldCell(TerrainType newTerrainType, Chest* newContents) {
        terraintype = newTerrainType;
        chest = newContents;
    }

    /** Gets world cell*/
    WorldCell* getCell() { return this; }

    /** Gets cell contents (chest)*/
    Chest* getChest() { return chest; }
    /** Sets cell contents (chest)*/
    void setContents(Chest* cnt) { chest = cnt; }

    /** Gets terrain type*/
    TerrainType getTerrainType() {return terraintype;}
    /** Sets terrain type*/
    void setTerrainType(TerrainType type) {terraintype = type;}

    /** WorldCell destructor*/
    ~WorldCell() { delete chest; }
};


#endif // WORLD_H
