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

void NetworkEngine::getGamesFromServer()
{
    sock->write("ULGETLIST\n");
}

void NetworkEngine::tryConnect()
{
    sock->connectToHost("localhost",5000);
}

void NetworkEngine::joinGame(int gameid, QString username)
{
    QString temp = QString("ULCONNECT ") + QString::fromStdString(to_string(gameid)) + QString(":") + username + QString("\n");
    sock->write(temp.toLocal8Bit());
}

void NetworkEngine::hangUp(int llama)
{
    string temp = string("ULREQUESTQUIT ") + to_string(llama) + string("\n");
    sock->write(temp.c_str());
}
void NetworkEngine::moveLlama(int llama, int x, int y)
{
    string temp = string("ULMOVE ") + to_string(llama) + string(":") + to_string(x) + string(":") + to_string(y) + string("\n");
    sock->write(temp.c_str());
}
void NetworkEngine::openChest(int llama, int x, int y, int pesos, int damage)
{
    stringstream ss;
    ss << "ULOPEN " << llama << ":" << x << ":" << y << ":" << pesos << ":" << damage << endl;
    sock->write(ss.str().c_str());
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
        QString line = QString::fromLocal8Bit(sock->readLine()).trimmed();
        qDebug() << line;
        QStringList splitline = line.split(" ");
        if(splitline[0] == "ULBEGINLIST")
            mode = GameList;
        else if(splitline[0] == "ULLISTITEM" && mode == GameList)
            gamelist.push_back(splitline[1]);
        else if(splitline[0] == "ULENDLIST")
            mode = Idle;
        else if(splitline[0] == "ULSTATEBEGIN")
            mode = StateFile;
        else if(splitline[0] == "ULSTATEEND")
        {
            mode = Idle;
            StateEngine::instance()->fromStateString(statefile);
        }
        else if(splitline[0] == "ULWORLDBEGIN")
            mode = WorldFile;
        else if(splitline[0] == "ULWORLDEND")
        {
            mode = Idle;
            World::loadFromQString(worldfile);
        }
        else if(splitline[0] == "ULSCORELIST")
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
        if(mode == StateFile)
        {
            state << line << endl;
        }
        if(mode == WorldFile)
        {
            world << line << endl;
        }
        if(splitline[0] == "ULMOVE")
        {
            QStringList args = splitline[1].split(":");
            StateEngine::instance()->moveLlama(args[0].toInt(),args[1].toInt(), args[2].toInt());
        }
        if(splitline[0] == "ULTICK")
        {
            StateEngine::instance()->syncTicks(splitline[1].toInt());
        }
    }
}
void NetworkEngine::onServerHangup()
{
    sock->deleteLater();
}
