#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QMediaRecorder>
#include <QTcpSocket>
#include <QThread>
#include <queue>

namespace Ui {
    class ChatWindow;
}

class VideoThread: public QThread
{
    Q_OBJECT

public:
};

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0,QString acc=NULL,QString name=NULL);
    ~ChatWindow();

private:
    Ui::ChatWindow *ui;
    QMediaRecorder* mr;
    QByteArray data;
    static bool isRecordVideo;
    QString f_account;
    QString f_name;
    std::queue<std::vector<uchar>> m_videoimgQueue;
    std::vector<uchar> m_videoBuf;
    int timerId;
    bool isVideoChat;

private:
    void showVideo();

protected:
    void timerEvent(QTimerEvent* event);

private slots:
    void sendVoice();
    void phoneChat();
    void videoChat();
    void sendFile();
    void sendMsg();
    void readMsg(char*);
    void recvFile(char*);
    void recvVideo(char*);
    void reqviewRecord();
};

#endif // CHATWINDOW_H
