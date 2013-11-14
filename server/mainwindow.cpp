#include <vector>
#include <QMessageBox>
#include <QDateTime>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <string>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connectCount(0)
{
    ui->setupUi(this);

    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &MainWindow::clientConnected);
    if (!server->listen(QHostAddress::Any, 5000)) {
        QMessageBox::critical(this, "Uh oh", "Cannot start socket.");
        exit(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addToLog(QString msg)
{
    QDateTime now = QDateTime::currentDateTime();
    ui->txtLog->appendPlainText(now.toString("hh:mm:ss") + " " + msg);
}

void MainWindow::clientConnected()
{
    QTcpSocket *sock = server->nextPendingConnection();
    connect(sock, &QTcpSocket::disconnected, this, &MainWindow::clientDisconnected);
    connect(sock, &QTcpSocket::readyRead, this, &MainWindow::dataReceived);
    ++connectCount;
    ui->lblConnected->setText(QString::number(connectCount));
    addToLog("Client connected.");
}

void MainWindow::dataReceived()
{
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());

    addToLog("Received data from socket ");
    while (sock->canReadLine()) {
        QString str = sock->readLine();
        if (str == "ULGETSCORES") {
            HighscoreList *h = new HighscoreList();
            QString highScores = h->returnScoreString();
            //send highScores to users

            // send data to all connected clients
            for (QObject *obj : server->children()) {
                QTcpSocket *anotherSock = dynamic_cast<QTcpSocket*>(obj);
                if (anotherSock != NULL)
                    anotherSock->write(highScores.toLocal8Bit());
            }
        }

    }
}

void MainWindow::clientDisconnected()
{
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    sock->deleteLater();
    --connectCount;
    ui->lblConnected->setText(QString::number(connectCount));
    addToLog("Client disconnected.");
}

class Highscore {
    QString name;
    int score;
public:
    //constructor
    Highscore(QString initName, int initScore):name(initName), score(initScore) {}

    QString printAScore() {
        QString answer = name + " " + QString::number(score);
        return answer;
    }

    QString getName() { return name; }
    int getScore() { return score; }
};

class HighscoreList {
private:
    vector<Highscore*> highScores;

public:
    //constructor
    HighscoreList() {}

    //returns highScores vector
    vector<Highscore*> getList() {
        return highScores;
    }

    //adds a highscore to the list of highscores
    void addHighscore(Highscore *h) {highScores.push_back(h);}

    //returns highScores vector as QStrings
    QString returnScoreString() {

        QString scoreString = "ULBEGINSCORES\n";
        for (int i = 0; i < 2; i++) {
            Highscore *h = highScores.at(i);
            scoreString += "ULSCORE " + h->getName() + QString::number(h->getScore()) + "\n";
        }
        scoreString += ULENDSCORES;
    }


    void sort();

};
