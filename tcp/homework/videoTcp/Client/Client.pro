QT +=  core gui network

HEADERS += \
    clientmainwindow.h \
    clientsocket.h \
    admincontrolwidget.h \
    inputadminpassworddialog.h \
    inputhostaddressdialog.h \
    CommandType.h \
    recordavi.h

SOURCES += \
    clientmainwindow.cpp \
    clientsocket.cpp \
    admincontrolwidget.cpp \
    main.cpp \
    inputadminpassworddialog.cpp \
    inputhostaddressdialog.cpp \
    recordavi.cpp

FORMS += \
    clientmainwindow.ui \
    admincontrolwidget.ui \
    inputadminpassworddialog.ui \
    inputhostaddressdialog.ui


INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so
