#ifndef CHATROOMLISTDLG_H
#define CHATROOMLISTDLG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class ChatRoomListDlg;
}

class ChatRoomListDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ChatRoomListDlg(QWidget *parent = 0);
    ~ChatRoomListDlg();

private:
    Ui::ChatRoomListDlg *ui;

private slots:
    void enterRoom(QTreeWidgetItem* item);
    void popMenu(QTreeWidgetItem* item);
};

#endif // CHATROOMLISTDLG_H
