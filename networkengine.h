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
/**
 * @brief The NEState enum holds states for NetworkEngine.
 *
 * NEState is something I've been inspired to do by my Ele 110 course, making NetworkEngine a state machine.
 * Basically, it starts in Idle state, and then takes different actions with the input depending on the state.
 * In Idle state, it reads the input to determine which state it should enter, and in the other states, when it finishes
 * it returns to Idle.
 *
 * (This was more impressive in its initial form, but multiplayer functionality was too much to code server-side.)
 */
enum NEState {Idle,ScoreList};

/**
 * @brief The NetworkEngine class is the network handler.
 *
 * NetworkEngine is the class handling all network I/O for Undersea Llamas.
 * It is a state-machine, as described in NEState, and also a singleton class.
 *
 * @see NEState
 */
class NetworkEngine : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief instance returns the one allowed instance of NetworkEngine.
     * @return the singleton instance
     */
    static NetworkEngine* instance() {return inst;}
    QTcpSocket* sock;


    vector<QString> gamelist;
    NEState mode;
    QString statefile,worldfile;
    QTextStream state,world;
    //CLIENT INITIATED CALLS
    /**
     * tryConnect attempts a connection to the server.
     */
    void tryConnect();
    /**
     * getHiscoresFromServer gets the HighScores list from the server.
     */
    void getHiscoresFromServer();
    /**
     * Sends a highscore to the server for inclusion in the list.
     * @param name The username to send to the server.
     * @param score The score the user achieved. (Their pesos + 100 times their remaining lives)
     */
    void sendHiscoreToServer(QString name, int score);
    //END CLIENT INITIATED CALLS

private:
    explicit NetworkEngine(QObject *parent = 0);
    static NetworkEngine* inst;
public slots:
    /**
     * @brief onDataReceived is a slot that handles data from the server.
     * It will act differently depending on NetworkEngine's state.
     * @see NEState
     */
    void onDataReceived();
    /**
     * @brief onServerHangup is a slot called on server disconnect.
     * It simply cleans up the socket gracefully.
     */
    void onServerHangup();
};

#endif // NETWORKENGINE_H
