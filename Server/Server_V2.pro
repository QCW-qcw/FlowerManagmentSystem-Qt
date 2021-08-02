#-------------------------------------------------
#
# Project created by QtCreator 2018-08-06T18:00:22
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server_V2
TEMPLATE = app


SOURCES += main.cpp\
    clientaddress.cpp \
    qnchatmessage.cpp \
        widget.cpp \
    myserver.cpp \
    mysocket.cpp \
    mythread.cpp

HEADERS  += widget.h \
    clientaddress.h \
    myserver.h \
    mysocket.h \
    mythread.h \
    debugonoroff.h \
    protocolcommand.h \
    qnchatmessage.h

FORMS    += widget.ui

RESOURCES += \
    documents.qrc \
    img.qrc
msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
