/**************************************************************************
**
**   networkengine.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef NETWORKENGINE_H
#define NETWORKENGINE_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QStringList>

using namespace std;

enum NEState {Idle,GameList,StateFile,WorldFile,ScoreList};

class NetworkEngine : public QObject
{
    Q_OBJECT
public:
    static NetworkEngine* instance() {return inst;}
    QTcpSocket* sock;


    vector<QString> gamelist;
    NEState mode;
    QString statefile,worldfile;
    QTextStream state,world;
    //CLIENT INITIATED CALLS
    void getGamesFromServer();
    void joinGame(int gameid, QString username);
    void hangUp(int llama);
    void tryConnect();

    void moveLlama(int llama, int x, int y);
    void openChest(int llama, int x, int y, int pesos, int damage);

    void getHiscoresFromServer();
    void sendHiscoreToServer(QString name, int score);
    //END CLIENT INITIATED CALLS

private:
    explicit NetworkEngine(QObject *parent = 0);
    static NetworkEngine* inst;
public slots:
    void onDataReceived();
    void onServerHangup();
};

#endif // NETWORKENGINE_H
