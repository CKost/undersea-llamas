#include "world.h"

World::World(int size)
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            WorldCell cell;
            cell.setTerrainType(0);
            cell.setContents(0);
            cells.push_back(&cell);
        }
    }
    this->size = size;
}
int World::getSize() { return size; }
