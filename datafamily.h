#ifndef DATAFAMILY_H
#define DATAFAMILY_H

#define FLAG            tr("/xxoo/")
#define ADDRESS         "localhost"
#define PORT            7777
#define REGISTER        0
#define LOGIN           1
#define INITMW          2
#define INITMF          3
#define FRIENDMSG       4
#define FRIEND          5
#define ADDFRIEND       6
#define INITGD          7
#define GROUPMSG        8
#define VIEWRECORDMSG   9
#define LEAVEGROUP      10
#define FRIENDOFFLINE   11
#define FRIENDONLINE    12
#define READOFFLINEMSG  13
#define TRANSFERFILE    14
#define AGREEADDFRIEND  15
#define VIDEOCHAT       16

typedef struct _REGISTERINFO
{
    char name[40];
    char email[40];
    char password[20];
    int  sex;
    char birthday[20];
} REGISTERINFO;

typedef struct _RESPONSE
{
    int status;
    int param;
} RESPONSE;

typedef struct _LOGININFO
{
    char account[40];
    char password[20];
} LOGININFO;

typedef struct _REQUEST
{
    char account[40];
} REQUEST;

typedef struct _INITMWINFO
{
    char name[40];
    char email[40];
    char signature[40];
    char headimg[80];
} INITMWINFO;

typedef struct _INITMFINFO
{
    int status;
    char name[40];
    char email[40];
    char signature[40];
    char headimg[80];
} INITMFINFO;

typedef struct _FRIENDMSGINFO
{
    char s_account[40];
    char r_account[40];
    char msg[1024];
} FRIENDMSGINFO;

typedef struct _FRIENDINFO
{
    int  status;
    char name[40];
    char email[40];
    int  sex;
    char birthday[20];
    char signature[40];
    char headimg[80];
} FRIENDINFO;

typedef struct _AGREEADDFRIENDINFO
{
    char s_account[40];
    char r_account[40];
} AGREEADDFRIENDINFO;

typedef struct _INITGDINFO
{
    char name[40];
    char email[40];
} INITGDINFO;

typedef struct _GROUPMSGINFO
{
    int  type;
    char name[40];
    char account[40];
    char msg[1024];
} GROUPMSGINFO;

typedef struct _VIEWRECORDINFO
{
    char s_account[40];
    char r_account[40];
} VIEWRECORDINFO;

typedef struct _TRANSFERFILEDATA
{
    char s_account[40];
    char r_account[40];
    int flag;
    int size;
    char filename[60];
    char suffix[20];
    char data[1024];
} TRANSFERFILEDATA;

typedef struct _VIDEOCHATDATA
{
    char s_account[40];
    char r_account[40];
    int flag;
    int size;
    char data[1024];
} VIDEOCHATDATA;

typedef struct _DATA
{
    int type;
    union
    {
        char buf[2048];
        REGISTERINFO  ri;
        RESPONSE      rs;
        LOGININFO     li;
        REQUEST       rq;
        INITMWINFO    imw;
        INITMFINFO    imf;
        FRIENDMSGINFO fmi;
        FRIENDINFO    afi;
        INITGDINFO    igi;
        GROUPMSGINFO  gmi;
        VIEWRECORDINFO vri;
        AGREEADDFRIENDINFO aafi;
        TRANSFERFILEDATA tfd;
    } info;
} DATA;

typedef struct _USERINFO
{
    char name[40];
    char account[40];
} USERINFO;

#endif // DATAFAMILY_H
