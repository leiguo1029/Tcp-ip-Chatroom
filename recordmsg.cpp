#include "recordmsg.h"
#include "csocket.h"
#include "datafamily.h"
#include "ui_recordmsg.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

extern CSocket* cs;
extern USERINFO uInfo;

RecordMsg::RecordMsg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordMsg)
{
    ui->setupUi(this);
    connect(cs,&CSocket::recvForViewRecord,this,&RecordMsg::viewRecordMsg);
}

RecordMsg::~RecordMsg()
{
    delete ui;
}

void RecordMsg::viewRecordMsg(char* data)
{
    FRIENDMSGINFO* fmi=(FRIENDMSGINFO*)data;

    if(strcmp(fmi->s_account,uInfo.name))
    {
        QStringList sl({"我：",fmi->msg,""});
        ui->listWidget->addItems(sl);
    }
    else
    {
        QStringList sl({QString(fmi->s_account)+"：",fmi->msg,""});
        ui->listWidget->addItems(sl);
    }

}
