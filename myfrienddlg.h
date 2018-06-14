#ifndef MYFRIENDDLG_H
#define MYFRIENDDLG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QTcpSocket>
#include <vector>

namespace Ui {
class myFriendDlg;
}

class myFriendDlg : public QDialog
{
    Q_OBJECT

public:
    explicit myFriendDlg(QWidget *parent = 0);
    ~myFriendDlg();

private:
    Ui::myFriendDlg *ui;
    QTreeWidgetItem* curItem;
    std::vector<QTreeWidgetItem*> subItem;

private slots:
    void updateList(char*);
    void friendOffLine(char*);
    void friendOnLine(char*);
    void startChat(QTreeWidgetItem* item);
    void popMenu(QTreeWidgetItem* item);
    void addGroup();
    void deleteGroup();
    void _startChat();
    void viewInfo();
    void alterRemark();
    void modifyGroup();
    void toBlackList();
    void delFriend();
};

#endif // MYFRIENDDLG_H
