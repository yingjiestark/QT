#-------------------------------------------------
#
# Project created by QtCreator 2021-12-15T15:34:50
#
#-------------------------------------------------

QT       += core gui  multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTSPServer
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    live/AlsaAACDevFramedSource.cpp \
    live/AlsaAACDevMulticastServerMediaSubsession.cpp \
    live/AlsaAACDevUnicastServerMediaSubsession.cpp \
    live/AlsaDevFramedSource.cpp \
    live/DevFramedSource.cpp \
    live/DevMulticastServerMediaSubsession.cpp \
    live/DevUnicastServerMediaSubsession.cpp \
    live/MulticastServerMediaSubsession.cpp \
    live/UnicastServerMediaSubsession.cpp \
    live/V4l2.cpp \
    live/V4l2DevFramedSource.cpp \
    live/V4l2H264DevFramedSource.cpp \
    live/V4l2H264DevMulticastServerMediaSubsession.cpp \
    live/V4l2H264DevUnicastServerMediaSubsession.cpp

HEADERS += \
        mainwindow.h \
    live/AlsaAACDevFramedSource.h \
    live/AlsaAACDevMulticastServerMediaSubsession.h \
    live/AlsaAACDevUnicastServerMediaSubsession.h \
    live/AlsaDevFramedSource.h \
    live/DevFramedSource.h \
    live/DevMulticastServerMediaSubsession.h \
    live/DevUnicastServerMediaSubsession.h \
    live/MulticastServerMediaSubsession.h \
    live/UnicastServerMediaSubsession.h \
    live/V4l2.h \
    live/V4l2DevFramedSource.h \
    live/V4l2H264DevFramedSource.h \
    live/V4l2H264DevMulticastServerMediaSubsession.h \
    live/V4l2H264DevUnicastServerMediaSubsession.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH +=  /usr/include/groupsock  \
                /usr/include/UsageEnvironment \
                /usr/include/BasicUsageEnvironment
                /usr/include/x264
LIBS += -lliveMedia -lBasicUsageEnvironment -lgroupsock -lUsageEnvironment -lpthread -lx264 -lfaac -lasound
