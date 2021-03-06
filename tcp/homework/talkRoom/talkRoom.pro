#-------------------------------------------------
#
# Project created by QtCreator 2013-07-13T08:59:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = talkRoom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingdialog.cpp

HEADERS  += mainwindow.h \
    settingdialog.h

FORMS    += mainwindow.ui \
    settingdialog.ui

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/res/values-id/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values/strings.xml \
    android/res/values/libs.xml \
    android/res/values-nb/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-es/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-it/strings.xml \
    android/version.xml
