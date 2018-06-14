#ifndef NOTICEDLG_H
#define NOTICEDLG_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class NoticeDlg;
}

class NoticeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit NoticeDlg(QWidget *parent = 0);
    ~NoticeDlg();

private:
    Ui::NoticeDlg *ui;
    QList<QStringList> m_slist;

private slots:
    void insertADDFriendMsg(char*);
    void insertOffLineMsgTip(char*);
    void dealMsg(QListWidgetItem* item);
};

#endif // NOTICEDLG_H
