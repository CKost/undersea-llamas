#include "world.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <stdexcept>

World* World::inst = new World(0);

World::World(int size)
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            WorldCell* cell = new WorldCell(OPEN,NULL);
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
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) throw "thrown";
    bool isFirstLine = true; int size = -1; int currentline = 0;
    QTextStream in (&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(isFirstLine)
        {
            if(line != "[ULWorld File v1.0]") throw "Whoa dude, that's not a legit world file. Check it before you wreck it next time, please. Kthx.";
            else isFirstLine=false;
            continue;
        }
        if(!isFirstLine && size == -1)
        {
            delete inst;
            inst = new World(line.toInt());
            continue;
        }
        if(size != -1)
        {
            for(int i = 0; i < size; ++i)
            {
                WorldCell* temp = new WorldCell(OPEN,NULL);
                switch(line.at(i).toLatin1())
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
