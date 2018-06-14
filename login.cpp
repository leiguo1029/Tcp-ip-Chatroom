#include "login.h"
#include "client.h"
#include "ui_login.h"
#include "register.h"
#include "csocket.h"
#include "datafamily.h"
#include <QMessageBox>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

extern bool state;
extern USERINFO uInfo;
extern CSocket* cs;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->imgLabel->setPixmap(QPixmap(":/img/img/title001.png"));
    this->setWindowIcon(QIcon(":/img/smile.ico"));
    connect(ui->loginButton,&QPushButton::clicked,this,&Login::loginButtondown);
    connect(ui->registerButton,&QPushButton::clicked,this,&Login::registerButtondown);
    connect(cs,&CSocket::recvForLogin,this,&Login::readData);

}

bool Login::checkInfo()
{
    QString acc=ui->accountEdit->text();
    if(acc=="")
        return false;
    QString pas=ui->passwordEdit->text();
    if(pas=="")
        return false;
    return true;
}

Login::~Login()
{
    delete ui;
}

void Login::loginButtondown()
{
    if(!checkInfo())
    {
        ui->checkLabel->setText("用户名和密码不能为空！！");
        return;
    }
    else
        ui->checkLabel->setText("");
    DATA dt={0};
    dt.type=LOGIN;
    LOGININFO li={0};
    strcpy(li.account,ui->accountEdit->text().toUtf8().data());
    strcpy(li.password,ui->passwordEdit->text().toUtf8().data());
    memcpy(&dt.info,&li,sizeof(LOGININFO));
    cs->send((char*)&dt,sizeof(DATA));
    qDebug()<<"发送成功！！";
}

void Login::registerButtondown()
{
    Register regDlg(this);
    regDlg.setModal(true);
    regDlg.exec();
}

void Login::readData(char* data)
{
    RESPONSE* rp=(RESPONSE*)data;
    if(rp->status)
    {
        state=true;
        strcpy(uInfo.account,ui->accountEdit->text().toUtf8().data());
        this->close();
    }
    else
        ui->checkLabel->setText("用户名或密码错误！！");
}
