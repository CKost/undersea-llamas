/**************************************************************************
**
**   moviedisplay.cpp
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "networkengine.h"
#include "stateengine.h"

#include <string>
#include <sstream>
#include <QDebug>

NetworkEngine::NetworkEngine(QObject *parent) :
    QObject(parent), state(&statefile), world(&worldfile)
{
    sock = new QTcpSocket(this);
    connect(sock,&QTcpSocket::readyRead,this,&NetworkEngine::onDataReceived);
    connect(sock,&QTcpSocket::disconnected,this,&NetworkEngine::onServerHangup);
}

NetworkEngine* NetworkEngine::inst = new NetworkEngine();

//BEGIN CLIENTSIDE CALLS
void NetworkEngine::tryConnect()
{
    sock->connectToHost("localhost",5000);
}
void NetworkEngine::getHiscoresFromServer()
{
    sock->write("ULGETSCORES\n");
}
void NetworkEngine::sendHiscoreToServer(QString name, int score)
{
    string temp =string("ULADDSCORE ") + name.toStdString() + string(" ") + to_string(score) + string("\n");
    sock->write(temp.c_str());
    getHiscoresFromServer();
}

//END CLIENTSIDE CALLS

void NetworkEngine::onDataReceived()
{
    while(sock->canReadLine())
    {
        QString line = QString::fromLocal8Bit(sock->readLine());
        qDebug() << line;
        QStringList splitline = line.trimmed().split(' ');
        if(splitline[0] == "ULSCORELIST")
        {
            mode = ScoreList;
            StateEngine::instance()->scores.clear();
        }
        else if(splitline[0] == "ULSCORE")
        {
            StateEngine::instance()->scores.push_back(new Highscore(splitline[1],splitline[2].toInt()));
        }
        else if(splitline[0] == "ULENDSCORES")
            mode = Idle;
    }
}
void NetworkEngine::onServerHangup()
{
    sock->deleteLater();
}
