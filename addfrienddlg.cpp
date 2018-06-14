#include "addfrienddlg.h"
#include "datafamily.h"
#include "csocket.h"
#include <QStringList>
#include "ui_addfrienddlg.h"
#include <QMessageBox>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

QString sex[3]={"男","女","未知"};

extern bool state;
extern USERINFO uInfo;
extern CSocket* cs;
AddfriendDlg::AddfriendDlg(QWidget *parent) :
    QDialog(parent),
    hasFriend(0),
    f_account{0},
    ui(new Ui::AddfriendDlg)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&AddfriendDlg::sendAccount);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&AddfriendDlg::addFriend);
    connect(cs,&CSocket::recvForFriendInfo,this,&AddfriendDlg::readData);
}

AddfriendDlg::~AddfriendDlg()
{
    delete ui;
}

void AddfriendDlg::sendAccount()
{
    DATA dt={0};
    REQUEST rq={0};
    dt.type=FRIEND;
    strcpy(rq.account,ui->lineEdit->text().toUtf8().data());
    memcpy(&dt.info,&rq,sizeof(REQUEST));
    cs->send((char*)&dt,sizeof(DATA));
}

void AddfriendDlg::addFriend()
{
    if(!hasFriend)
    {
        QMessageBox::information(this,"提示","无好友可添加！");
        return;
    }
    DATA dt={0};
    dt.type=ADDFRIEND;
    FRIENDMSGINFO fmi={0};
    strcpy(fmi.s_account,uInfo.account);
    strcpy(fmi.r_account,f_account);
    memcpy(&dt.info,&fmi,sizeof(FRIENDMSGINFO));
    cs->send((char*)&dt,sizeof(DATA));
}

void AddfriendDlg::readData(char* data)
{
    //清空列表
    for(int index=0;index<ui->listWidget->count();index++)
    {
        QListWidgetItem* item=ui->listWidget->takeItem(0);
        delete item;
    }

    FRIENDINFO* afi=(FRIENDINFO*)data;
    if(!afi->status)
    {
        hasFriend=false;
        QMessageBox::information(this,"提示","该用户不存在！");
        return;
    }

    hasFriend=true;
    strcpy(f_account,afi->email);
    QStringList sl({QString("姓名：")+afi->name,QString("电子邮箱：")+afi->email,
                    QString("性别：")+sex[afi->sex-1],QString("生日：")+afi->birthday,
                    QString("个性签名：")+afi->signature});
    ui->listWidget->addItems(sl);
//    QPushButton* addButton=new QPushButton("添加",this);
//    addButton->setGeometry(260,310,61,29);

}
