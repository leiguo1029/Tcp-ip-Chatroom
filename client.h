#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QAbstractSocket>
#include <QTcpSocket>

class QTcpSocket;

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    void Init();

private:
    Ui::Client *ui;
    QTcpSocket* tcpSocket;
    QString msg;
    static int nCount;

private slots:
    void newConnect();
    void disConnect();
    void readMessage();
    void sendButtonDown();
    void sendMessage();
    void displayError(QAbstractSocket::SocketError);
};

#endif // CLIENT_H
