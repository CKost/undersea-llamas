#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addToLog(QString msg);

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
