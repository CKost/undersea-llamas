/**************************************************************************
**
**   worldgenerator.cpp
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "worldgenerator.h"
#include <vector>
#include "world.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

WorldGenerator::WorldGenerator()
{
                 tile1 = {"OOBB",
                          "OOTB",
                          "OBBB",
                          "OOOO"};
                 tile2 = {"BBOO",
                          "BTOO",
                          "BBBO",
                          "OOOO"};
                 tile3 = {"OOOO",
                          "OOBO",
                          "BTBO",
                          "BBBO"};
                 tile4 = {"OOOO",
                          "OBOO",
                          "OBTB",
                          "OBBB"};
                 tile5 = {"OOBB",
                          "OOEB",
                          "OBBB",
                          "OOOO"};
                 tile6 = {"BBOO",
                          "BEOO",
                          "BBBO",
                          "OOOO"};
                 tile7 = {"OOOO",
                          "OOBO",
                          "BEBO",
                          "BBBO"};
                 tile8 = {"OOOO",
                          "OBOO",
                          "OBEB",
                          "OBBB"};
                 tile9 = {"OOBB",
                          "OORB",
                          "OBBB",
                          "OOOO"};
                 tileA = {"BBOO",
                          "BROO",
                          "BBBO",
                          "OOOO"};
                 tileB = {"OOOO",
                          "OOBO",
                          "BRBO",
                          "BBBO"};
                 tileC = {"OOOO",
                          "OBOO",
                          "OBRB",
                          "OBBB"};
}

bool WorldGenerator::generate(string name)
{
    vector<string> world;
    vector<vector<string>*> cells = {&tile1, &tile2, &tile3, &tile4, &tile5, &tile6, &tile7, &tile8, &tile9, &tileA, &tileB, &tileC};
}
