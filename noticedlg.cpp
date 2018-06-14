#include "noticedlg.h"
#include "datafamily.h"
#include "csocket.h"
#include "ui_noticedlg.h"
#include <QMessageBox>
#include "chatwindow.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

extern USERINFO uInfo;
extern CSocket* cs;

NoticeDlg::NoticeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoticeDlg)
{
    ui->setupUi(this);
    connect(cs,&CSocket::recvForAddFriend,this,&NoticeDlg::insertADDFriendMsg);
    connect(cs,&CSocket::recvForReadOffLineMsg,this,&NoticeDlg::insertOffLineMsgTip);
    connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,&NoticeDlg::dealMsg);
}

NoticeDlg::~NoticeDlg()
{
    delete ui;
}

void NoticeDlg::insertADDFriendMsg(char* data)
{
    FRIENDMSGINFO* fmi=(FRIENDMSGINFO*)data;
    int count=ui->listWidget->count();
    if (count!=0)
    {
        for(int i=0;i<count;i++)
        {
            QListWidgetItem* lwi=ui->listWidget->takeItem(i);
            QStringList sList=m_slist[i];
            if(sList[0]==QString("0"))
            {
                break;
            }
            if(sList[1]==QString(fmi->s_account))
            {
                return;
            }
        }
    }
    QStringList sl({"1",fmi->s_account,fmi->msg});
    m_slist.push_back(sl);
    ui->listWidget->addItem(QString("添加好友请求"));
}

void NoticeDlg::insertOffLineMsgTip(char* data)
{
    FRIENDMSGINFO* fmi=(FRIENDMSGINFO*)data;
    for(int i=0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* lwi=ui->listWidget->takeItem(i);
        QStringList sList=m_slist[i];
        if(sList[0]==QString("1"))
        {
            break;
        }
        if(sList[1]==QString(fmi->s_account))
        {
            sList[2]=QString(sList[2].toInt()+1);
            sList.push_back(QString(fmi->msg));
            m_slist[i]=sList;
            lwi->setText(QString("来自")+fmi->s_account+"的未读消息  +"+sList[2]);
            return;
        }
    }

    QListWidgetItem* item=new QListWidgetItem();
    QStringList sl({"0",fmi->s_account,"1",fmi->msg});
    m_slist.push_back(sl);
    item->setText(QString("来自")+fmi->s_account+"的未读消息  +1");
    ui->listWidget->addItem(item);
}

void NoticeDlg::dealMsg(QListWidgetItem *item)
{
    int index=ui->listWidget->row(item);
    QStringList sList=m_slist[index];
    if(sList[0]==QString("1"))
    {
        int re=QMessageBox::information(this,"好友请求",sList[1]+"请求加你为好友",QMessageBox::Ok|QMessageBox::Ignore);
        if(re==QMessageBox::Ignore)
        {
            return;
        }
        if(re==QMessageBox::Ok)
        {
            DATA dt={AGREEADDFRIEND};
            AGREEADDFRIENDINFO aafi={0};
            strcpy(aafi.s_account,uInfo.account);
            strcpy(aafi.r_account,sList[1].toUtf8().data());
            memcpy(&dt.info,&aafi,sizeof(AGREEADDFRIENDINFO));
            cs->send((char*)&dt,sizeof(DATA));
        }
    }
}
