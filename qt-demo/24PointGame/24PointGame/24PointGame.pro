#-------------------------------------------------
#
# Project created by QtCreator 2022-06-24T13:17:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TARGET = 24PointGame
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
    game_widget.cpp \
    level_widget.cpp \
    level_main_widget.cpp \
    main_widget.cpp \
    db/dbmanager.cpp \
    num_button.cpp \
    lnum.cpp \
    tools.cpp \
    level_button.cpp

HEADERS += \
    game_widget.h \
    level_widget.h \
    level_main_widget.h \
    main_widget.h \
    db/dbmanager.h \
    num_button.h    \
    lnum.h \
    tools.h \
    common.h \
    level_button.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
