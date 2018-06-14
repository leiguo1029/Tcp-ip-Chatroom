#include "client.h"
#include "login.h"
#include "datafamily.h"
#include "mainwindow.h"
#include <csocket.h>
#include <QApplication>
#include <QTcpSocket>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

bool state=false;
USERINFO uInfo;
CSocket* cs;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cs=new CSocket();
    Login loginDlg;
    loginDlg.show();
    loginDlg.exec();

    if(state==true)
    {
        MainWindow mwDlg;
        mwDlg.show();
        a.exec();
    }
//    VideoCapture capture(0);
//        VideoWriter writer("VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480),1);
//        Mat frame;
//        while (1)
//        {
//           capture >> frame;  //capture >> frame与capture.read(frame)功能一样，但注销此句会出错，不知原因
//                              //在另一台电脑上测试程序，环境opencv2.4.4+win7_64+vs2010注销此句可以运行
//           if(!capture.read(frame))  // 读取下一帧图像
//                 break;
//           writer << frame;
//           imshow("video", frame);
//           if (cvWaitKey(1) == 27)   // 按下Esc退出程序
//                break;
//         }
    return a.exec();
}
