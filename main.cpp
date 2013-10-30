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

int main(int argc, char *argv[])
{

    assert(Riddle::get_SizeRiddles()==0);
    Riddle::add_riddlesToriddles();
    assert(Riddle::get_SizeRiddles()==3);

    QApplication a(argc, argv);
    ULMainWindow w;
    w.show();
    
    return a.exec();



}
