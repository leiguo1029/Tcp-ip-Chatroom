#ifndef GROUPCHATDLG_H
#define GROUPCHATDLG_H

#include <QDialog>

namespace Ui {
class GroupChatDlg;
}

class GroupChatDlg : public QDialog
{
    Q_OBJECT

public:
    explicit GroupChatDlg(QWidget *parent = 0);
    ~GroupChatDlg();

private:
    Ui::GroupChatDlg *ui;

private slots:
    void initOLList(char*);
    void sendMsg();
    void readMsg(char*);
    void sbLeaveGroup(char*);
};

#endif // GROUPCHATDLG_H
