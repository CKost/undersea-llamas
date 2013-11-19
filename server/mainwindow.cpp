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

void HighscoreList::addHighscore(Highscore *h) {
    while (highScores.size() >= 20) {
        Highscore* delScore = highScores.front();
        delete delScore;
        highScores.pop_front();
    }
    highScores.push_back(h);
}

void MainWindow::dataReceived()
{
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());

    addToLog("Received data from socket ");
    while (sock->canReadLine())
    {
        QString str = sock->readLine();
        addToLog(str);
        if (str == "ULGETSCORES\n")
        {
            if(scores.isEmpty()) return;
            QString highScores = scores.returnScoreString();
            //send highScores to users
            sock->write(highScores.toLocal8Bit());
            // send data to all connected clients
            /*for (QObject *obj : server->children()) {
                QTcpSocket *anotherSock = dynamic_cast<QTcpSocket*>(obj);
                if (anotherSock != NULL)
                    anotherSock->write(highScores.toLocal8Bit());
            */
        }
        QStringList splitline = str.split(" ");
        if(splitline.at(0) == "ULADDSCORE")
        {
            Highscore* temp = new Highscore(splitline.at(1),splitline.at(2).toInt());
            scores.addHighscore(temp);
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


