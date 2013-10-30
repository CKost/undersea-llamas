#include "world.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QString>
#include <QFile>

World::World(int size)
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            WorldCell cell(0,NULL);
            cells.push_back(cell);
        }
    }
    this->size = size;
}
WorldCell* World::getCell(int x, int y)
{
    return cells.at(x*size + y);
}
void World::loadFromFile(QString filename)
{
    ifstream rvr(filename.toStdString().c_str());
    string line;
    bool isFirstLine = true; int size = -1; int currentline = 0;
    while(getline(rvr,line))
    {
        if(isFirstLine)
        {
            if(line != "[ULWorld File v1.0]") throw "Whoa dude, that's not a legit world file. Check it before you wreck it next time, please. Kthx.";
            else isFirstLine=false;
        }
        if(!isFirstLine && size == -1)
        {
            delete inst;
            int size = stoi(line);
            inst = new World(size);
        }
        if(size != -1)
        {
            for(int i = 0; i < size; ++i)
            {
                WorldCell* temp = new WorldCell();
                switch(line.at(i))
                {
                case 'O':
                    temp->setTerrainType(OPEN);
                    break;
                case 'B':
                    temp->setTerrainType(OBSTACLE);
                    break;
                case 'S':
                    temp->setTerrainType(ROUGH);
                    break;
                case 'T':
                    temp->setTerrainType(OPEN);
                    temp->setContents(new TreasureChest());
                    break;
                case 't':
                    temp->setTerrainType(ROUGH);
                    temp->setContents(new TreasureChest());
                    break;
                case 'E':
                    temp->setTerrainType(OPEN);
                    temp->setContents(new EnemyChest());
                    break;
                case 'e':
                    temp->setTerrainType(ROUGH);
                    temp->setContents(new EnemyChest());
                    break;
                case 'R':
                    temp->setTerrainType(OPEN);
                    temp->setContents(new RiddleChest());
                    break;
                case 'r':
                    temp->setTerrainType(ROUGH);
                    temp->setContents(new RiddleChest());
                }
            }
        }
    }
}
World::~World()
{
    for(WorldCell* cell : cells)
        delete cell;
}
