#include "chatroomlistdlg.h"
#include "ui_chatroomlistdlg.h"
#include "groupchatdlg.h"
#include "csocket.h"
#include <QtcpSocket>
#include <QDebug>
#include <QMenu>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

extern CSocket cs;

ChatRoomListDlg::ChatRoomListDlg(QWidget *parent) :
     QDialog(parent),
     ui(new Ui::ChatRoomListDlg)
{
     ui->setupUi(this);
     ui->chatroomTree->setColumnWidth(0,190);
     ui->chatroomTree->setColumnWidth(1,116);
     QTreeWidgetItem* item1=new QTreeWidgetItem(ui->chatroomTree);
     item1->setText(0,QString("电信专区"));
     QTreeWidgetItem* item2=new QTreeWidgetItem(ui->chatroomTree);
     item2->setText(0,QString("网通专区"));
     new QTreeWidgetItem(item1,{"黑色玫瑰","0"});
     new QTreeWidgetItem(item2,{"德玛西亚","0"});
     connect(ui->chatroomTree,&QTreeWidget::itemDoubleClicked,this,&ChatRoomListDlg::enterRoom);
     connect(ui->chatroomTree,&QTreeWidget::itemPressed,this,&ChatRoomListDlg::popMenu);
     ui->chatroomTree->show();
}

ChatRoomListDlg::~ChatRoomListDlg()
{
     delete ui;
}

void ChatRoomListDlg::enterRoom(QTreeWidgetItem* item)
{
     if(qApp->mouseButtons()!=Qt::LeftButton)
         return;
     if(item->parent()==NULL)
         return;
     GroupChatDlg* gcd=new GroupChatDlg(this);
     gcd->show();
}

void ChatRoomListDlg::popMenu(QTreeWidgetItem* item)
{
    if(qApp->mouseButtons()!=Qt::RightButton)
        return;
    if(item->parent()==NULL)
        return;
    QMenu mu(ui->chatroomTree);
    qDebug()<<item->text(0);
    mu.addAction("进入该聊天室");
    mu.show();
    mu.exec(QCursor::pos());
}
