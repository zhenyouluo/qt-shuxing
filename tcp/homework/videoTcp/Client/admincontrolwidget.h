#ifndef ADMINCONTROLWIDGET_H
#define ADMINCONTROLWIDGET_H

#include <QWidget>

#include "CommandType.h"

class QListWidgetItem;

namespace Ui {
class AdminControlWidget;
}

class AdminControlWidget : public QWidget
{
    Q_OBJECT
signals:
    void cmdLogDir(const QByteArray& context);
    void cmdLogFile(const QByteArray& context);
    void cmdDevStates(const QByteArray& context);
    void cmdClientStates(const QByteArray& context);
    void sig_hide();
public slots:
    void getDirInfo_slots(const QByteArray& context);
    void getInfo_slots(const QByteArray& context);
public:
    explicit AdminControlWidget(QWidget *parent = 0);
    ~AdminControlWidget();
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void doCMDlogDir();
    void doCMDlogFile(QListWidgetItem* item);
    void doCMDDevstates();
    void doCMDClientStates();
    void slt_clear();
private:
    Ui::AdminControlWidget *ui;
    QAction *clearContextAction;

    void initUI();
    void initconnects();

    void cmdToByteArray(int flag,QByteArray &buffer);
};

#endif // ADMINCONTROLWIDGET_H
