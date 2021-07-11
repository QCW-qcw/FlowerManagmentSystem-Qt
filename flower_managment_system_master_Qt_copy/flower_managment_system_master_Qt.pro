QT       += core gui sql
QT       += core gui  network
QT      += charts
QT      +=webenginewidgets

DEFINES += QT_MESSAGELOGCONTEXT

QT+=axcontainer
qtHaveModule(printsupport): QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = flower_managment_system_master_Qt
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR     = $$PWD/../bin

SOURCES     += main.cpp \
    browser.cpp \
    browserwindow.cpp \
    downloadmanagerwidget.cpp \
    downloadwidget.cpp \
    drilldownchart.cpp \
    drilldownslice.cpp \
    flowerclass.cpp \
    flowergrowth.cpp \
    flowershow.cpp \
    folwernumform.cpp \
    frmlunarcalendarwidget.cpp \
    global.cpp \
    loginwindow.cpp \
    lunarcalendarinfo.cpp \
    lunarcalendaritem.cpp \
    lunarcalendarwidget.cpp \
    mainwindow.cpp \
    registerwindow.cpp \
    selectwidget.cpp \
    sqldataread.cpp \
    tabwidget.cpp \
    webpage.cpp \
    webpopupwindow.cpp \
    webview.cpp \
    whetherwindow.cpp \
    widget.cpp
SOURCES     += iconhelper.cpp
SOURCES     += appinit.cpp
SOURCES     += uidemo18.cpp

HEADERS     += iconhelper.h \
    browser.h \
    browserwindow.h \
    downloadmanagerwidget.h \
    downloadwidget.h \
    drilldownchart.h \
    drilldownslice.h \
    flowergrowth.h \
    flowersclass.h \
    flowershow.h \
    folwernumform.h \
    frmlunarcalendarwidget.h \
    global.h \
    loginwindow.h \
    lunarcalendarinfo.h \
    lunarcalendaritem.h \
    lunarcalendarwidget.h \
    mainwindow.h \
    registerwindow.h \
    selectwidget.h \
    sqldataread.h \
    tabwidget.h \
    webpage.h \
    webpopupwindow.h \
    webview.h \
    whetherwindow.h \
    widget.h
HEADERS     += appinit.h
HEADERS     += uidemo18.h

FORMS       += uidemo18.ui \
    certificateerrordialog.ui \
    downloadmanagerwidget.ui \
    downloadwidget.ui \
    flowergrowth.ui \
    flowershow.ui \
    folwernumform.ui \
    frmlunarcalendarwidget.ui \
    loginwindow.ui \
    mainwindow.ui \
    passworddialog.ui \
    registerwindow.ui \
    selectwidget.ui \
    sqldataread.ui \
    whetherwindow.ui \
    widget.ui

RESOURCES   += main.qrc \
    data/simplebrowser.qrc
CONFIG      += qt warn_off
INCLUDEPATH += $$PWD
msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

