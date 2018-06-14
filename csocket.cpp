#include "csocket.h"
#include <QWidget>
#include <QDataStream>
#include <chatwindow.h>
#include "datafamily.h"

CSocket::CSocket():
    tcpSocket(new QTcpSocket())
{
    tcpSocket->connectToHost(ADDRESS,PORT);
    connect(tcpSocket,&QTcpSocket::readyRead,this,&CSocket::recv);
}

void CSocket::send(char *data, int len)
{
//    for(int i=0;i<len-4;i++)
//    {
//        data[i+4]^=0xF;
//    }
    tcpSocket->write(data,len);
}

void CSocket::recv()
{
    int type=0;
    while(tcpSocket->read((char*)&type,4))
    {
        memset(m_data,0,2048);
        switch(type)
        {
            case REGISTER:
                tcpSocket->read(m_data,sizeof(RESPONSE));
                emit recvForRegister(m_data);
                break;
            case LOGIN:
                tcpSocket->read(m_data,sizeof(RESPONSE));
                emit recvForLogin(m_data);
                break;
            case INITMW:
                tcpSocket->read(m_data,sizeof(INITMWINFO));
                emit recvForInitMW(m_data);
                break;
            case INITMF:
                tcpSocket->read(m_data,sizeof(INITMFINFO));
                emit recvForInitMF(m_data);
                break;
            case FRIENDMSG:
                tcpSocket->read(m_data,sizeof(FRIENDMSGINFO));
                emit recvForFriendMsg(m_data);
                break;
            case FRIEND:
                tcpSocket->read(m_data,sizeof(FRIENDINFO));
                emit recvForFriendInfo(m_data);
                break;
            case ADDFRIEND:
                tcpSocket->read(m_data,sizeof(FRIENDMSGINFO));
                emit recvForAddFriend(m_data);
                break;
            case INITGD:
                tcpSocket->read(m_data,sizeof(INITGDINFO));
                emit recvForInitGD(m_data);
                break;
            case GROUPMSG:
                tcpSocket->read(m_data,sizeof(GROUPMSGINFO));
                emit recvForGroupMsg(m_data);
                break;
            case VIEWRECORDMSG:
                tcpSocket->read(m_data,sizeof(FRIENDMSGINFO));
                emit recvForViewRecord(m_data);
                break;
            case LEAVEGROUP:
                tcpSocket->read(m_data,sizeof(REQUEST));
                emit recvForLeaveGroupMsg(m_data);
                break;
            case FRIENDOFFLINE:
                tcpSocket->read(m_data,sizeof(REQUEST));
                emit recvForOffLineMsg(m_data);
                break;
            case FRIENDONLINE:
                tcpSocket->read(m_data,sizeof(REQUEST));
                emit recvForOnLineMsg(m_data);
                break;
            case READOFFLINEMSG:
                tcpSocket->read(m_data,sizeof(FRIENDMSGINFO));
                emit recvForReadOffLineMsg(m_data);
            case TRANSFERFILE:
                tcpSocket->read(m_data,sizeof(TRANSFERFILEDATA));
                emit recvforTransferFile(m_data);
                break;
            case VIDEOCHAT:
                tcpSocket->read(m_data,sizeof(TRANSFERFILEDATA));
                emit recvForVideoChat(m_data);
            default:
                break;
        }
    }
}

