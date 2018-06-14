#include "myfrienddlg.h"
#include "ui_myfrienddlg.h"
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include "datafamily.h"
#include "csocket.h"
#include "chatwindow.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

extern bool state;
extern USERINFO uInfo;
extern CSocket* cs;

myFriendDlg::myFriendDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myFriendDlg)
{
    ui->setupUi(this);
    ui->myfriendTree->setColumnWidth(0,190);
    ui->myfriendTree->setColumnWidth(1,116);
//    REQUEST rq={0};
//    rq.type=INITMF;
//    strcpy(rq.account,account);
//    cs->send((char*)&rq,sizeof(REQUEST));

    QTreeWidgetItem* item1=new QTreeWidgetItem(ui->myfriendTree,{"在线",""});
    QTreeWidgetItem* item2=new QTreeWidgetItem(ui->myfriendTree,{"离线",""});
    subItem.push_back(item1);
    subItem.push_back(item2);
    connect(ui->myfriendTree,&QTreeWidget::itemDoubleClicked,this,&myFriendDlg::startChat);
    connect(ui->myfriendTree,&QTreeWidget::itemPressed,this,&myFriendDlg::popMenu);
    connect(cs,&CSocket::recvForInitMF,this,&myFriendDlg::updateList);
    connect(cs,&CSocket::recvForOffLineMsg,this,&myFriendDlg::friendOffLine);
    connect(cs,&CSocket::recvForOnLineMsg,this,&myFriendDlg::friendOnLine);
}

myFriendDlg::~myFriendDlg()
{
    delete ui;
}

void myFriendDlg::updateList(char* data)
{
    INITMFINFO* imi=(INITMFINFO*)data;
    QTreeWidgetItem* item=new QTreeWidgetItem({imi->name,""});
    QVariant vi(imi->email);
    item->setData(0,Qt::UserRole,vi);
    if(imi->status==1)
    subItem[0]->addChild(item);
    else
        subItem[1]->addChild(item);
}

void myFriendDlg::friendOffLine(char* data)
{
    REQUEST* rq=(REQUEST*)data;
    int count=subItem[0]->childCount();
    for(int i=0;i<count;i++)
    {
        QTreeWidgetItem* item=subItem[0]->child(i);
        if(item->text(0)==QString(rq->account))
        {
            subItem[1]->addChild(new QTreeWidgetItem(*item));
            delete item;
            break;
        }
    }
}

void myFriendDlg::friendOnLine(char* data)
{
    REQUEST* rq=(REQUEST*)data;
    int count=subItem[1]->childCount();
    for(int i=0;i<count;i++)
    {
        QTreeWidgetItem* item = subItem[1]->child(i);
        if(item->text(0)==QString(rq->account))
        {
            subItem[0]->addChild(new QTreeWidgetItem(*item));
            delete item;
            return;
        }
    }
}

void myFriendDlg::popMenu(QTreeWidgetItem* item)
{
    curItem=item;
    if(qApp->mouseButtons()!=Qt::RightButton)
        return;
    if(item->parent()==NULL)
    {
        QMenu* mu=new QMenu(ui->myfriendTree);
        QAction* act_1=new QAction("添加分组");
        QAction* act_2=new QAction("删除该分组");
        mu->addAction(act_1);
        mu->addAction(act_2);
        connect(act_1,&QAction::triggered,this,&myFriendDlg::addGroup);
        connect(act_2,&QAction::triggered,this,&myFriendDlg::deleteGroup);
        mu->show();
        mu->exec(QCursor::pos());
    }
    else
    {
        QMenu mu(ui->myfriendTree);
        QAction* act_1=new QAction("开始聊天");
        QAction* act_2=new QAction("查看该好友信息");
        QAction* act_3=new QAction("修改备注");
        QAction* act_4=new QAction("修改分组");
        QAction* act_5=new QAction("拉入黑名单");
        QAction* act_6=new QAction("删除该好友");
        mu.addAction(act_1);
        mu.addAction(act_2);
        mu.addAction(act_3);
        mu.addAction(act_4);
        mu.addAction(act_5);
        mu.addAction(act_6);

        connect(act_1,&QAction::triggered,this,&myFriendDlg::_startChat);
        connect(act_2,&QAction::triggered,this,&myFriendDlg::viewInfo);
        connect(act_3,&QAction::triggered,this,&myFriendDlg::alterRemark);
        connect(act_4,&QAction::triggered,this,&myFriendDlg::modifyGroup);
        connect(act_5,&QAction::triggered,this,&myFriendDlg::toBlackList);
        connect(act_6,&QAction::triggered,this,&myFriendDlg::delFriend);

        mu.show();
        mu.exec(QCursor::pos());
    }
}

void myFriendDlg::addGroup()
{
    qDebug()<<"添加分组";
}

void myFriendDlg::viewInfo()
{

}

void myFriendDlg::alterRemark()
{

}

void myFriendDlg::modifyGroup()
{

}

void myFriendDlg::toBlackList()
{

}

void myFriendDlg::delFriend()
{

}

void myFriendDlg::deleteGroup()
{
    qDebug()<<"删除分组";
}

void myFriendDlg::_startChat()
{

}

void myFriendDlg::startChat(QTreeWidgetItem* item)
{
    if(qApp->mouseButtons()!=Qt::LeftButton)
        return;
    if(item->parent()==NULL)
        return;
    ChatWindow* cw=new ChatWindow(this,item->data(0,Qt::UserRole).toString(),item->text(0));
    char str[30]={0};
    sprintf(str,"与%s聊天中",item->text(0).toUtf8().data());
    cw->setWindowTitle(str);
    cw->show();
}
