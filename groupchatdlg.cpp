#include "groupchatdlg.h"
#include "datafamily.h"
#include "csocket.h"
#include "ui_groupchatdlg.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

extern bool state;
extern USERINFO uInfo;
extern CSocket* cs;

GroupChatDlg::GroupChatDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupChatDlg)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->listWidget->addItem("你已进入聊天室");
    ui->listWidget->addItem("");

    connect(cs,&CSocket::recvForInitGD,this,&GroupChatDlg::initOLList);
    connect(ui->pushButton,&QPushButton::clicked,this,&GroupChatDlg::sendMsg);
    connect(cs,&CSocket::recvForGroupMsg,this,&GroupChatDlg::readMsg);
    connect(cs,&CSocket::recvForLeaveGroupMsg,this,&GroupChatDlg::sbLeaveGroup);

    DATA dt={INITGD};
    INITGDINFO igi={0};
    strcpy(igi.email,uInfo.account);
    strcpy(igi.name,uInfo.name);
    memcpy(&dt.info,&igi,sizeof(INITGDINFO));
    cs->send((char*)&dt,sizeof(DATA));
}

GroupChatDlg::~GroupChatDlg()
{
    DATA dt={LEAVEGROUP};
    REQUEST rq={0};
    strcpy(rq.account,uInfo.account);
    memcpy(&dt.info,&rq,sizeof(REQUEST));
    cs->send((char*)&dt,sizeof(DATA));

    delete ui;
}

void GroupChatDlg::initOLList(char* data)
{
    INITGDINFO* igi=(INITGDINFO*)data;
    ui->listWidget_2->addItem(igi->name);
}

void GroupChatDlg::sendMsg()
{
    DATA dt={GROUPMSG};
    GROUPMSGINFO gmi={0};
    strcpy(gmi.account,uInfo.account);
    strcpy(gmi.name,uInfo.name);
    strcpy(gmi.msg,ui->textEdit->toPlainText().toUtf8().data());
    memcpy(&dt.info,&gmi,sizeof(GROUPMSGINFO));
    cs->send((char*)&dt,sizeof(DATA));
    QStringList sl({"我：",gmi.msg,""});
    ui->listWidget->addItems(sl);
    ui->textEdit->setText("");
}

void GroupChatDlg::readMsg(char* data)
{
    GROUPMSGINFO* gmi=(GROUPMSGINFO*)data;
    if(gmi->type==1)
    {
        ui->listWidget->addItem(QString(gmi->name)+"已进入聊天室");
        ui->listWidget->addItem("");
        ui->listWidget_2->addItem(gmi->name);
        return;
    }
    QStringList sl({gmi->name,gmi->msg,""});
    ui->listWidget->addItems(sl);
}

void GroupChatDlg::sbLeaveGroup(char* data)
{
    REQUEST* rq=(REQUEST*)data;
    ui->listWidget->addItem(QString(rq->account)+"已离开聊天室");
    ui->listWidget->addItem("");
    int count=ui->listWidget_2->count();
    for(int i=0;i<count;i++)
    {
        QListWidgetItem* item=ui->listWidget_2->item(i);
        if(item->text()==QString(rq->account))
        {
            delete item;
            break;
        }
    }
}
