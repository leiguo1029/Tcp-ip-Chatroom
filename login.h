#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QAbstractSocket>
#include <QTcpSocket>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    bool checkInfo();
    ~Login();

private:
    Ui::Login *ui;
    QString msg;

private slots:
    void loginButtondown();
    void registerButtondown();
    void readData(char*);
};

#endif // LOGIN_H
