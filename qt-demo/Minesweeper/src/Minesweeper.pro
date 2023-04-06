#-------------------------------------------------
#
# Project created by QtCreator 2022-01-27T22:14:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Minesweeper
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
        ui/select_dialog.cpp \
        ui/main_window.cpp \
        ui/game_widget.cpp \
        ui/register_dialog.cpp \
         ui/ranking_dialog.cpp \
        db/db_manager.cpp \
    ui/about_dialog.cpp

HEADERS += \
        common.h \
        ui/select_dialog.h \
        ui/main_window.h \
        ui/game_widget.h \
        ui/register_dialog.h \
        ui/ranking_dialog.h \
        db/db_manager.h \
    ui/about_dialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resource.qrc
