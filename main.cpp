/***************************************************************************
**
**   main.cpp
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "chests.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"
#include <cassert>
#include <QApplication>

bool unitTest();

int main(int argc, char *argv[])
{
    unitTest();
    QApplication a(argc, argv);
    ULMainWindow w;
    w.show();
    
    return a.exec();
}

bool unitTest()
{
    StateEngine* se = StateEngine::instance();
    World* world = World::instance();
    se->loadFromFile(":/textfiles/statefile.ulstate");
    assert(se->getLlama(1)->getUsername() == "SpazDude");
    assert(world->getCell(5,7)->getTerrainType() == OPEN);
    assert(world->getCell(5,7)->getChest() != NULL);
    assert(world->getCell(5,7)->getChest()->empty);
    assert(se->getLlama(0)->getPesos()==400);

    assert(Riddle::get_SizeRiddles()==0);
    Riddle::add_riddlesToriddles();
    assert(Riddle::get_SizeRiddles()==3);
}
