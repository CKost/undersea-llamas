/**************************************************************************
**
**   worldgenerator.hpp
**
**   This file copyright 2013 Alex Fischer.
**   Work done for CpS 111 at Bob Jones University.
**
**   You may use this file however you see fit, with one exception:
**   You may not pass this work off as your own.
**
**************************************************************************/

#ifndef WORLDGENERATOR_HPP
#define WORLDGENERATOR_HPP

#include <QObject>

class WorldGenerator : public QObject
{
    Q_OBJECT
public:
    explicit WorldGenerator(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // WORLDGENERATOR_HPP
