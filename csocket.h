#ifndef CSOCKET_H
#define CSOCKET_H
#include <QTcpSocket>

class CSocket:public QTcpSocket
{
    Q_OBJECT
public:
    CSocket();
    void send(char* data,int len);
    void recv();

private:
    char m_data[2048];
    QTcpSocket* tcpSocket;


signals:
    void recvForRegister(char*);
    void recvForLogin(char*);
    void recvForInitMW(char*);
    void recvForInitMF(char*);
    void recvForFriendMsg(char*);
    void recvForFriendInfo(char*);
    void recvForAddFriend(char*);
    void recvForInitGD(char*);
    void recvForGroupMsg(char*);
    void recvForViewRecord(char*);
    void recvForLeaveGroupMsg(char*);
    void recvForOffLineMsg(char*);
    void recvForOnLineMsg(char*);
    void recvforTransferFile(char*);
    void recvForReadOffLineMsg(char*);
    void recvForVideoChat(char*);
};

#endif // CSOCKET_H
