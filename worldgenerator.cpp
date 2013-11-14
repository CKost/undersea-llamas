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
#include <cstdlib>
#include <QFile>
#include <QTextStream>
#include <QString>

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

bool WorldGenerator::generate(QString name)
{
    vector<string> world;
    vector<vector<QString>> cells = {tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9, tileA, tileB, tileC};
    int selections[16];
    for(int i = 0; i < 16; ++i)
        selections[i] = rand() % 12;
    QFile file (name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw "file load error";
    QTextStream out(&file);
    out << "[ULWorld File v1.0]" << endl;
    out << 18 << endl;
    out << "BBBBBBBBBBBBBBBBBB" << endl;
    for(int i = 0; i < 4; ++i)
    {
        out << "B" << (cells.at(selections[0])).at(i) << cells.at(selections[1]).at(i) << cells.at(selections[2]).at(i) << cells.at(selections[3]).at(i) << "B" << endl;
    }
    for(int i = 0; i < 4; ++i)
    {
        out << "B" << (cells.at(selections[4])).at(i) << cells.at(selections[5]).at(i) << cells.at(selections[6]).at(i) << cells.at(selections[7]).at(i) << "B" << endl;
    }
    for(int i = 0; i < 4; ++i)
    {
        out << "B" << (cells.at(selections[8])).at(i) << cells.at(selections[9]).at(i) << cells.at(selections[10]).at(i) << cells.at(selections[11]).at(i) << "B" << endl;
    }
    for(int i = 0; i < 4; ++i)
    {
        out << "B" << (cells.at(selections[12])).at(i) << cells.at(selections[13]).at(i) << cells.at(selections[14]).at(i) << cells.at(selections[15]).at(i) << "B" << endl;
    }
    out << "BBBBBBBBBBBBBBBBBB" << endl;
    out.flush();
    file.close();
    return true;
}
