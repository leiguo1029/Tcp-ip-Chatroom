#include "client.h"
#include "ui_client.h"
#include <QtNetwork>
#include <QMessageBox>
#include "datafamily.h"

int Client::nCount=0;

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    tcpSocket=new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::readyRead,this,&Client::readMessage);

    connect(ui->sendButton,&QPushButton::clicked,this,&Client::sendButtonDown);

    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));

    connect(tcpSocket,&QTcpSocket::disconnected,this,&Client::disConnect);

    connect(ui->connectButton,&QPushButton::clicked,this,&Client::newConnect);
}

Client::~Client()
{
    delete ui;
}

void Client::Init()
{
    newConnect();
    show();
}

void Client::newConnect()
{
    tcpSocket->abort();
    tcpSocket->connectToHost(ADDRESS,PORT);
}

void Client::disConnect()
{
    ui->listWidget->insertItem(nCount++,tr("disconnect to the server!"));
}

void Client::readMessage()
{
   // QDataStream in(tcpSocket);
   // in.setVersion(QDataStream::Qt_5_9);

    msg=tcpSocket->readAll();

    ui->listWidget->insertItem(nCount++,msg);

}

void Client::sendButtonDown()
{
    if(ui->textEdit->toPlainText()=="")
        return;
    sendMessage();
    ui->textEdit->setText("");
}

void Client::sendMessage()
{
    QString mstr=ui->textEdit->toPlainText();
    tcpSocket->write(mstr.toUtf8());
    qDebug()<<tr("send successfully!");
}

void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
}


