/**************************************************************************
**
**   worldgenerator.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
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
