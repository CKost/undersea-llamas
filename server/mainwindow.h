#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <deque>
#include <QString>
#include <string>
#include <sstream>

using namespace std;

namespace Ui {
class MainWindow;
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
    deque<Highscore*> highScores;

public:
    //constructor
    HighscoreList() {}

    //returns highScores vector
    deque<Highscore*> getList() {
        return highScores;
    }

    bool isEmpty() { return highScores.empty(); }

    //adds a highscore to the list of highscores
    void addHighscore(Highscore *h);

    //returns highScores vector as QStrings
    QString returnScoreString() {

        stringstream ss;
        ss << "ULBEGINSCORES" << endl;
        for(Highscore* h : highScores)
        {
            ss << "ULSCORE " << h->getName().toStdString() << " " << h->getScore() << endl;
        }
        ss << "ULENDSCORES" << endl;
        return QString::fromStdString(ss.str());
//        QString scoreString = "ULBEGINSCORES\n";
//        for(Highscore* h : highScores)
//        {
//            scoreString += "ULSCORE " + h->getName() +" "+ QString::number(h->getScore()) + "\n";
//        }
//        scoreString += "ULENDSCORES\n";
    }

};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addToLog(QString msg);
    HighscoreList scores;

private slots:
    void clientConnected();
    void dataReceived();
    void clientDisconnected();

private:
    Ui::MainWindow *ui;

    QTcpServer* server;
    int connectCount;
};

#endif // MAINWINDOW_H
