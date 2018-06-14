#include <QAbstractSocket>
#include "register.h"
#include "ui_register.h"
#include "datafamily.h"
#include "csocket.h"
#include <QTcpSocket>
#include <QStringList>
#include <QMessageBox>
#include <QRegExp>

extern CSocket* cs;

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register),
    sexgroup(new QButtonGroup(this))
{
    ui->setupUi(this);
    connect(cs,&CSocket::recvForRegister,this,&Register::readData);
    connect(ui->resetButton,&QPushButton::clicked,this,&Register::resetInfo);
    connect(ui->submitButton,&QPushButton::clicked,this,&Register::submitInfo);
    // connect(ui->nameEdit,&QLineEdit::textChanged,this,&Register::checkNamelen);
    // connect(ui->emailEdit,&QLineEdit::editingFinished,this,&Register::checkEmaillen);
    // connect(ui->passwordEdit2,&QLineEdit::textChanged,this,&Register::checkPasswordlen);
    sexgroup->addButton(ui->radioMan,1);
    sexgroup->addButton(ui->radioWoman,2);
    sexgroup->addButton(ui->radioUnknown,3);
}

Register::~Register()
{
    delete ui;
}

void Register::resetInfo()
{
    ui->nameEdit->setText("");
    ui->emailEdit->setText("");
    ui->passwordEdit->setText("");
    ui->passwordEdit2->setText("");
    ui->radioMan->setChecked(true);
    ui->radioWoman->setChecked(false);
    ui->radioUnknown->setChecked(false);
    ui->dateEdit->setDate(QDate(2000,1,1));
}

void Register::submitInfo()
{
    if(!checkInfo())
        return;

    DATA dt={0};
    dt.type=REGISTER;
    REGISTERINFO ri={0};
    strcpy(ri.name,ui->nameEdit->text().toUtf8().data());
    strcpy(ri.email,ui->emailEdit->text().toUtf8().data());
    strcpy(ri.password,ui->passwordEdit->text().toUtf8().data());
    ri.sex=sexgroup->checkedId();
    strcpy(ri.birthday,ui->dateEdit->text().toUtf8().data());
    memcpy(&dt.info,&ri,sizeof(REGISTERINFO));
    cs->send((char*)&dt,sizeof(DATA));
    qDebug()<<"send successfully!";
}

bool Register::checkName()
{
    QString text=ui->nameEdit->text();
    if(text=="")
    {
        ui->nameCheckLabel->setText("用户名不能为空！");
        return false;
    }
    else
        ui->nameCheckLabel->setText("");

    QRegExp re("[\u4E00-\u9FA5\\w]+");
    if(!re.exactMatch(text))
    {
        ui->nameCheckLabel->setText("用户名中含有无效字符，请重新输入！！");
        return false;
    }
    else
        ui->nameCheckLabel->setText("");
    return true;
}

bool Register::checkEmail()
{
    QString text=ui->emailEdit->text();
    if(text=="")
    {
        ui->emailCheckLabel->setText("邮箱不能为空！！");
        return false;
    }
    else
        ui->emailCheckLabel->setText("");

    QRegExp re("\\w+@\\w+.[a-zA-Z]+");
    if(!re.exactMatch(text))
    {
        ui->emailCheckLabel->setText("邮箱地址格式错误！！");
        return false;
    }
    else
        ui->emailCheckLabel->setText("");
    return true;
}

bool Register::checkPassword()
{
    QString str1=ui->passwordEdit->text();
    QString str2=ui->passwordEdit2->text();
    if(str1=="")
    {
        ui->psCheckLabel->setText("密码不能为空！！");
        return false;
    }
    if(str1!=str2)
    {
        ui->psCheckLabel->setText("两次密码输入不一致，请重新输入！");
        return false;
    }
    else
    {
        ui->psCheckLabel->setText("");
        return true;
    }

}

void Register::readData(char* data)
{
    RESPONSE* rp=(RESPONSE*)data;
    if(rp->status)
    {
        QMessageBox::information(this,"提示","注册成功！！");
        this->close();
    }
    else
    {
        if(!(rp->param&0x1))
            ui->nameCheckLabel->setText("该用户名已被使用，请重新输入！！");
        if(!(rp->param&0x10))
            ui->emailCheckLabel->setText("该邮箱已被注册，请重新输入！");
    }
}

bool Register::checkInfo()
{
    bool bl=checkName();
    bl=checkEmail()&&bl;
    bl=checkPassword()&&bl;
    return bl;
    //  return checkName()&&checkEmail()&&checkPassword();
}
