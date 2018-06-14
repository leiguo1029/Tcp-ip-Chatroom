#ifndef RECORDMSG_H
#define RECORDMSG_H

#include <QDialog>

namespace Ui {
class RecordMsg;
}

class RecordMsg : public QDialog
{
    Q_OBJECT

public:
    explicit RecordMsg(QWidget *parent = 0);
    ~RecordMsg();

private:
    Ui::RecordMsg *ui;

private slots:
    void viewRecordMsg(char*);
};

#endif // RECORDMSG_H
