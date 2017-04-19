#-------------------------------------------------
#
# Project created by QtCreator 2017-04-17T22:26:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BeeBeeChat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sender.cpp \
    receiver.cpp

HEADERS  += mainwindow.h \
    sender.h \
    receiver.h

FORMS    += mainwindow.ui

#-----------------activemq cpp lib-------------------
INCLUDEPATH += /usr/local/include/activemq-cpp-3.9.4
LIBS += /usr/local/lib/libactivemq-cpp.a

#--------------------apr lip-------------------------
INCLUDEPATH += /usr/local/apr/include/apr-1
LIBS += /usr/local/apr/lib/libapr-1.a

RESOURCES += \
    resources.qrc
