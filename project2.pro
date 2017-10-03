#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T11:37:35
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
        mainwindow.cpp \
    character.cpp \
    commandwords.cpp \
    door.cpp \
    flashlight.cpp \
    item.cpp \
    key.cpp \
    Parser.cpp \
    Room.cpp \
    command.cpp

HEADERS  +=\ mainwindow.h \
    character.h \
    commandwords.h \
    door.h \
    flashlight.h \
    item.h \
    key.h \
    Parser.h \
    room.h \
    command.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
