/********************************************************************************
** Form generated from reading UI file 'servermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERMAINWINDOW_H
#define UI_SERVERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerMainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ServerMainWindow)
    {
        if (ServerMainWindow->objectName().isEmpty())
            ServerMainWindow->setObjectName(QStringLiteral("ServerMainWindow"));
        ServerMainWindow->resize(800, 600);
        centralwidget = new QWidget(ServerMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(140, 40, 651, 191));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(150, 280, 621, 191));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 40, 71, 451));
        ServerMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ServerMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        ServerMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ServerMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ServerMainWindow->setStatusBar(statusbar);

        retranslateUi(ServerMainWindow);

        QMetaObject::connectSlotsByName(ServerMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ServerMainWindow)
    {
        ServerMainWindow->setWindowTitle(QApplication::translate("ServerMainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("ServerMainWindow", "\345\256\242\346\210\267\347\272\277\347\250\213", 0));
        groupBox_2->setTitle(QApplication::translate("ServerMainWindow", "\350\256\276\345\244\207\347\272\277\347\250\213", 0));
        groupBox_3->setTitle(QApplication::translate("ServerMainWindow", "\350\256\276\345\244\207", 0));
    } // retranslateUi

};

namespace Ui {
    class ServerMainWindow: public Ui_ServerMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERMAINWINDOW_H
