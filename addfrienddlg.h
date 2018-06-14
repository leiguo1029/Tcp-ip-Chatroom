#ifndef ADDFRIENDDLG_H
#define ADDFRIENDDLG_H

#include <QDialog>

namespace Ui {
class AddfriendDlg;
}

class AddfriendDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddfriendDlg(QWidget *parent = 0);

    ~AddfriendDlg();

private:
    Ui::AddfriendDlg *ui;
    bool hasFriend;
    char f_account[40];

private slots:
    void sendAccount();
    void addFriend();
    void readData(char*);
};

#endif // ADDFRIENDDLG_H
