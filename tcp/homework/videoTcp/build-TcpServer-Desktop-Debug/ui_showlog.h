/********************************************************************************
** Form generated from reading UI file 'showlog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWLOG_H
#define UI_SHOWLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowLog
{
public:
    QTextEdit *textEdit;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *ShowLog)
    {
        if (ShowLog->objectName().isEmpty())
            ShowLog->setObjectName(QStringLiteral("ShowLog"));
        ShowLog->resize(556, 426);
        textEdit = new QTextEdit(ShowLog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(140, 40, 381, 351));
        textEdit->setAutoFillBackground(false);
        textEdit->setReadOnly(true);
        treeWidget = new QTreeWidget(ShowLog);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(10, 40, 111, 341));

        retranslateUi(ShowLog);

        QMetaObject::connectSlotsByName(ShowLog);
    } // setupUi

    void retranslateUi(QWidget *ShowLog)
    {
        ShowLog->setWindowTitle(QApplication::translate("ShowLog", "Log", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("ShowLog", "\346\227\245\345\277\227\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class ShowLog: public Ui_ShowLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWLOG_H
