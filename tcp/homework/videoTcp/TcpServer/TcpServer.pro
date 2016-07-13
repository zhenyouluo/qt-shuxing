# -------------------------------------------------
# Project created by QtCreator 2012-03-22T19:47:49
# -------------------------------------------------
QT += network
QT += widgets
TARGET = TcpServer
TEMPLATE = app
SOURCES += main.cpp \
    servermainwindow.cpp \
    tablewidget.cpp \
    showlog.cpp \
    tablewidgetitem.cpp \
    tablewidgetdev.cpp \
    ServerSocket.cpp \
    cameraThread.cpp \
    cameraV4L2.cpp \
    serversocketobject.cpp \
    cameraServer.cpp
HEADERS += \
    servermainwindow.h \
    tablewidget.h \
    showlog.h \
    LogInfo.h \
    tablewidgetitem.h \
    tablewidgetdev.h \
    Permission.h \
    ServerSocket.h \
    cameraThread.h \
    cameraV4L2.h \
    serversocketobject.h \
    cameraServer.h \
    CommandType.h \
    YUYVtoRGB.h
FORMS += serverwidget.ui \
    servermainwindow.ui \
    showlog.ui

#DEFINES+=QT_NO_DEBUG_OUTPUT

RESOURCES += \
    pic.qrc



OTHER_FILES += \
    备注
