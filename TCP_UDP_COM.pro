#-------------------------------------------------
#
# Project created by QtCreator 2012-01-09T11:10:15
#
#-------------------------------------------------

QT += core gui widgets
QT       +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCP_UDP_COM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    udp.cpp \
    com.cpp \
    qextserialport.cpp \
    qextserialbase.cpp \
    win_qextserialport.cpp \
    tcpclient.cpp \
    tcpserver.cpp \
    tcpudpcombase.cpp

HEADERS  += mainwindow.h \
    udp.h \
    com.h \
    win_qextserialport.h \
    qextserialport.h \
    qextserialbase.h \
    tcpclient.h \
    tcpserver.h \
    tcpudpcombase.h

FORMS    += mainwindow.ui \
    udp.ui \
    com.ui \
    tcpclient.ui \
    tcpserver.ui

























