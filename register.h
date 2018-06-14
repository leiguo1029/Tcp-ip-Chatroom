#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QTcpSocket>
#include <QButtonGroup>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private:
    Ui::Register *ui;
    QString msg;
    QButtonGroup* sexgroup;

private slots:
    void resetInfo();
    void submitInfo();
    bool checkName();
    bool checkEmail();
    bool checkPassword();
    void readData(char*);
    bool checkInfo();
};

#endif // REGISTER_H
