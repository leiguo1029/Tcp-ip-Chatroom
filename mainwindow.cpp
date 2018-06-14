#include "mainwindow.h"
#include "chatroomlistdlg.h"
#include "myfrienddlg.h"
#include "addfrienddlg.h"
#include "noticedlg.h"
#include "ui_mainwindow.h"
#include "datafamily.h"
#include <QMovie>
#include <csocket.h>
#include <QMessageBox>


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

extern bool state;
extern USERINFO uInfo;
extern CSocket* cs;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    connect(cs,&CSocket::recvForInitMW,this,&MainWindow::readData);


    ChatRoomListDlg* crDlg=new ChatRoomListDlg(ui->mwTab);
    myFriendDlg* mfDlg=new myFriendDlg(ui->mwTab);
    AddfriendDlg* afDlg=new AddfriendDlg(ui->mwTab);
    NoticeDlg* ntDlg=new NoticeDlg(ui->mwTab);
    delete ui->tab;
    delete ui->tab_2;
    QPixmap img(":/img/img/timo.jpg");
    QPixmap faceimg=img.scaled(121,121,Qt::KeepAspectRatio);
    ui->faceingLabel->setPixmap(faceimg);
    QIcon icon(":/img/img/circle.jpg");
    setWindowIcon(icon);

    ui->mwTab->addTab(crDlg,QString("聊天室"));
    ui->mwTab->addTab(mfDlg,QString("我的好友"));
    ui->mwTab->addTab(afDlg,QString("添加好友"));
    ui->mwTab->addTab(ntDlg,QString("消息"));
    DATA dt={0};
    dt.type=INITMW;
    REQUEST rq={0};
    strcpy(rq.account,uInfo.account);
    memcpy(&dt.info,&rq,sizeof(REQUEST));
    cs->send((char*)&dt,sizeof(DATA));
}

MainWindow::~MainWindow()
{
    DATA dt={FRIENDOFFLINE};
    REQUEST rq={0};
    strcpy(rq.account,uInfo.account);
    memcpy(&dt.info,&rq,sizeof(REQUEST));
    cs->send((char*)&dt,sizeof(DATA));

    delete ui;
}

void MainWindow::readData(char* data)
{
    INITMWINFO* imi=(INITMWINFO*)data;
    strcpy(uInfo.name,imi->name);
    ui->nameLabel->setText(imi->name);
    return;
}

