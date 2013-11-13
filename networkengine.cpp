#include "networkengine.h"
#include "stateengine.h"
#include <string>
#include <sstream>

NetworkEngine::NetworkEngine(QObject *parent) :
    QObject(parent)
{
    sock = new QTcpSocket(this);
    connect(sock,&QTcpSocket::readyRead,this,&NetworkEngine::onDataReceived);
    connect(sock,&QTcpSocket::disconnected,this,&NetworkEngine::onServerHangup);
    sock->connectToHost("shredder.resnet.bju",42000);
}

NetworkEngine* NetworkEngine::inst = new NetworkEngine();

//BEGIN CLIENTSIDE CALLS

void NetworkEngine::getGamesFromServer()
{
    sock->write("ULGETLIST");
}

void NetworkEngine::joinGame(int gameid, QString username)
{
    QString temp = QString("ULCONNECT ") + QString::fromStdString(to_string(gameid)) + QString(":") + username;
    sock->write(temp.toLocal8Bit());
}

void NetworkEngine::hangUp(int llama)
{
    string temp = string("ULREQUESTQUIT ") + to_string(llama);
    sock->write(temp.c_str());
}
void NetworkEngine::moveLlama(int llama, int x, int y)
{
    string temp = string("ULMOVE ") + to_string(llama) + string(":") + to_string(x) + string(":") + to_string(y);
    sock->write(temp.c_str());
}
void NetworkEngine::openChest(int llama, int x, int y, int pesos, int damage)
{
    stringstream ss;
    ss << "ULOPEN " << llama << ":" << x << ":" << y << ":" << pesos << ":" << damage;
    sock->write(ss.str().c_str());
}
void NetworkEngine::getHiscoresFromServer()
{
    sock->write("ULGETSCORES");
}
void NetworkEngine::sendHiscoreToServer(QString name, int score)
{
    string temp =string("ULADDSCORE ") + name.toStdString() + string(":") + to_string(score);
    sock->write(temp.c_str());
}

//END CLIENTSIDE CALLS

void NetworkEngine::onDataReceived()
{
    while(sock->canReadLine())
    {
        QString line = sock->readLine();
        QStringList splitline = line.split(" ");
        if(splitline[0] == "ULBEGINLIST")
            mode = GameList;
        else if(splitline[0] == "ULLISTITEM" && mode == GameList)
            gamelist.push_back(splitline[1]);
        else if(splitline[0] == "ULENDLIST")
            mode = Idle;
        else if(splitline[0] == "ULSTATEFILE")
            mode = StateFile;
        else if(splitline[0] == "ULENDSTATE")
            mode = Idle;
        else if(splitline[0] == "ULWORLDFILE")
            mode = WorldFile;
        else if(splitline[0] == "ULSCORELIST")
            mode = ScoreList;
        else if(splitline[0] == "ULSCORE")
            ;//TODO: IMPLEMENT SCORING FUNCTIONALITY
        else if(splitline[0] == "ULENDSCORES")
            mode = Idle;
        if(mode == StateFile)
        {

        }
    }
}
void NetworkEngine::onServerHangup()
{
    sock->deleteLater();
}
