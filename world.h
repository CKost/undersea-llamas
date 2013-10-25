#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "chests.h"
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
