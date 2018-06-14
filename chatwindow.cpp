#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "csocket.h"
#include <QFileSystemModel>
#include <opencv2/opencv.hpp>
#include <datafamily.h>
#include <QDateTime>
#include "recordmsg.h"
#include <QFileDialog>

using namespace std;
using namespace cv;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

extern bool state;
extern USERINFO uInfo;
extern CSocket* cs;

bool ChatWindow::isRecordVideo=false;

ChatWindow::ChatWindow(QWidget *parent,QString acc,QString name) :
    QDialog(parent),
    f_account(acc),
    f_name(name),
    ui(new Ui::ChatWindow),
    isVideoChat(false)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
//    QFileSystemModel* model=new QFileSystemModel();
//    model->setRootPath(QString(QDir::currentPath()));
//    ui->listView->setModel(model);
//    ui->listView->setRootIndex(model->index(QDir::currentPath()));
//    ui->treeView->setModel(model);
//    ui->treeView->setRootIndex(model->index(QDir::currentPath()));

    qDebug()<<"连接成功";

    ui->sendvoiceButton->setToolTip("发送语音消息");
    ui->sendvoiceButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->phoneButton->setToolTip("语音聊天");
    ui->phoneButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->videoButton->setToolTip("视频聊天");
    ui->videoButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->sendfileButton->setToolTip("发送文件");
    ui->sendfileButton->setCursor(QCursor(Qt::PointingHandCursor));

    connect(ui->videoButton,&QToolButton::clicked,this,&ChatWindow::videoChat);
    connect(ui->phoneButton,&QToolButton::clicked,this,&ChatWindow::phoneChat);
    connect(ui->sendvoiceButton,&QToolButton::clicked,this,&ChatWindow::sendVoice);
    connect(ui->sendfileButton,&QToolButton::clicked,this,&ChatWindow::sendFile);
    connect(ui->sendButton,&QPushButton::clicked,this,&ChatWindow::sendMsg);
    connect(cs,&CSocket::recvForFriendMsg,this,&ChatWindow::readMsg);
    connect(ui->historyButton,&QPushButton::clicked,this,&ChatWindow::reqviewRecord);
    connect(cs,&CSocket::recvforTransferFile,this,&ChatWindow::recvFile);
    connect(cs,&CSocket::recvForVideoChat,this,&ChatWindow::recvVideo);

}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==timerId)
    {
        if(m_videoimgQueue.empty())
            return;
        std::vector<uchar> videoBuf=m_videoimgQueue.front();
        Mat img=imdecode(videoBuf,CV_LOAD_IMAGE_COLOR);
        imshow("xxx",img);
        m_videoimgQueue.pop();
    }
}



void ChatWindow::sendVoice()
{

}

void ChatWindow::phoneChat()
{

}

void ChatWindow::recvFile(char* data)
{
    TRANSFERFILEDATA* tfd=(TRANSFERFILEDATA*)data;
    QFile file(QString("D:\\Qt Project\\Client\\file\\")+tfd->filename);
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QDataStream out(&file);
    char* buf=new char[tfd->size];
    memcpy(buf,tfd->data,tfd->size);
    out.writeRawData(buf,tfd->size);
    if(tfd->flag==1)
    {
        ui->listWidget->addItem("文件接收成功！");
        ui->listWidget->addItem("");
    }
    file.flush();
    file.close();

}

void ChatWindow::recvVideo(char* data)
{
    if(!isVideoChat)
    {
        timerId=startTimer(100);
        isVideoChat=true;
    }
    VIDEOCHATDATA* vcd=(VIDEOCHATDATA*)data;
    for(int i=0;i<vcd->size;i++)
    {
        m_videoBuf.push_back(vcd->data[i]);
    }
    if(vcd->flag==1)
    {
        m_videoimgQueue.push(m_videoBuf);
        m_videoBuf.clear();
    }
}

void ChatWindow::videoChat()
{
    VideoCapture vc(0);
    vc.set(CV_CAP_PROP_FRAME_WIDTH,300);
    vc.set(CV_CAP_PROP_FRAME_HEIGHT,200);
    while(1)
    {
        Mat frame;
        vc>>frame;
        imshow(QString("与XXX视频中").toLocal8Bit().data(),frame);
        std::vector<uchar> buff;
        imencode(".jpg",frame,buff);
        int size=buff.size();
        char* buf=new char[size];
        for(int i=0;i<size;i++)
        {
            buf[i]=buff[i];
        }

        DATA dt={VIDEOCHAT};
        while(size>0)
        {
            VIDEOCHATDATA vcd={0};
            vcd.flag=0;

            if(size>1024)
                vcd.size=1024;
            else
            {
                vcd.size=size;
                vcd.flag=1;
            }

            strcpy(vcd.s_account,uInfo.account);
            strcpy(vcd.r_account,f_account.toUtf8().data());
            memcpy(vcd.data,buf,vcd.size);
            memcpy(&dt.info,&vcd,sizeof(VIDEOCHATDATA));
            cs->send((char*)&dt,sizeof(DATA));
            buf+=1024;
            size-=1024;
        }
//        VIDEOCHATDATA vcd={0};
//        vcd.flag=0;
//        memcpy(&dt.info,&vcd,sizeof(VIDEOCHATDATA));
//        cs->send((char*)&dt,sizeof(DATA));
        if(waitKey(100)=='q')
        {
            break;
        }
    }
}

void ChatWindow::sendFile()
{
    QString fileName=QFileDialog::getOpenFileName(this,"打开文件","");
    if(fileName==QString(""))
        return;
      QFile file(fileName);
    QFileInfo fi(file);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    int size=file.size();
    char* buf=new char[size];
    in.readRawData(buf,size);
    DATA dt={TRANSFERFILE};
    while(size>0)
    {
        TRANSFERFILEDATA tfd={0};
        tfd.flag=0;
        if(size>1024)
            tfd.size=1024;
        else
        {
            tfd.flag=1;
            tfd.size=size;
        }
        strcpy(tfd.filename,fi.fileName().toUtf8().data());
        strcpy(tfd.suffix,fi.suffix().toUtf8().data());
        strcpy(tfd.s_account,uInfo.account);
        strcpy(tfd.r_account,f_account.toUtf8().data());
        memcpy(tfd.data,buf,tfd.size);
        memcpy(&dt.info,&tfd,sizeof(TRANSFERFILEDATA));
        cs->send((char*)&dt,sizeof(DATA));
        buf+=1024;
        size-=1024;
    }
    TRANSFERFILEDATA tfd={0};
    memcpy(&dt.info,&tfd,sizeof(TRANSFERFILEDATA));
    cs->send((char*)&dt,sizeof(DATA));
    ui->listWidget->addItem("文件发送成功！");
    ui->listWidget->addItem("");
}

void ChatWindow::sendMsg()
{
    FRIENDMSGINFO fmi={0};
    DATA dt={0};
    dt.type=FRIENDMSG;
    strcpy(fmi.s_account,uInfo.account);
    strcpy(fmi.r_account,f_account.toUtf8().data());
    strcpy(fmi.msg,ui->textEdit->toPlainText().toUtf8().data());
    memcpy(&dt.info,&fmi,sizeof(FRIENDMSGINFO));
    QDateTime dtime;
    dtime.setDate(QDate::currentDate());
    dtime.setTime(QTime::currentTime());
    QString cdt=dtime.toString("yyyy-MM-dd hh:mm:ss");
    ui->listWidget->addItems(QStringList({cdt,"我：",ui->textEdit->toPlainText(),""}));
    cs->send((char*)&dt,sizeof(DATA));
    ui->textEdit->setText("");
}

void ChatWindow::readMsg(char* data)
{
    QDateTime dtime;
    dtime.setDate(QDate::currentDate());
    dtime.setTime(QTime::currentTime());
    QString cdt=dtime.toString("yyyy-MM-dd hh:mm:ss");
    FRIENDMSGINFO* fmi=(FRIENDMSGINFO*)data;
    ui->listWidget->addItems(QStringList({cdt,f_name,fmi->msg,""}));
}

void ChatWindow::reqviewRecord()
{
    RecordMsg* rm=new RecordMsg(this);
    rm->show();
    DATA dt={VIEWRECORDMSG};
    VIEWRECORDINFO vri={0};
    strcpy(vri.s_account,uInfo.account);
    strcpy(vri.r_account,f_account.toUtf8().data());
    memcpy(&dt.info,&vri,sizeof(VIEWRECORDINFO));
    cs->send((char*)&dt,sizeof(DATA));
}
