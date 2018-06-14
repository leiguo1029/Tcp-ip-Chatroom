#-------------------------------------------------
#
# Project created by QtCreator 2018-02-07T14:56:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    client.cpp \
    login.cpp \
    register.cpp \
    mainwindow.cpp \
    chatroomlistdlg.cpp \
    myfrienddlg.cpp \
    chatwindow.cpp \
    csocket.cpp \
    addfrienddlg.cpp \
    groupchatdlg.cpp \
    recordmsg.cpp \
    noticedlg.cpp \
    clicklabel.cpp

HEADERS += \
    client.h \
    login.h \
    register.h \
    mainwindow.h \
    chatroomlistdlg.h \
    myfrienddlg.h \
    chatwindow.h \
    datafamily.h \
    csocket.h \
    addfrienddlg.h \
    groupchatdlg.h \
    recordmsg.h \
    noticedlg.h \
    clicklabel.h

FORMS += \
    client.ui \
    login.ui \
    register.ui \
    mainwindow.ui \
    chatroomlistdlg.ui \
    myfrienddlg.ui \
    chatwindow.ui \
    addfrienddlg.ui \
    groupchatdlg.ui \
    recordmsg.ui \
    noticedlg.ui

QT    +=network

RESOURCES += \
    crc.qrc

RC_FILE = resource.rc

INCLUDEPATH += D:/opencv/opencv/build/include

CONFIG(debug, debug|release): {
LIBS += -LD:/opencv/opencv/build/x64/vc14/lib \
-lopencv_world320d \

} else:CONFIG(release, debug|release): {
LIBS += -LD:/opencv/opencv/build/x64/vc14/lib \
-lopencv_world320 \

}

QT   +=   core gui multimedia multimediawidgets
