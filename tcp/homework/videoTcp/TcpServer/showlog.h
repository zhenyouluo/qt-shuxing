#ifndef SHOWLOG_H
#define SHOWLOG_H

#include <QWidget>
#include <QHBoxLayout>


namespace Ui {
class ShowLog;
}

class ShowLog : public QWidget
{
    Q_OBJECT
    
public:
    explicit ShowLog(const QString &dir,QWidget *parent = 0);
    ~ShowLog();
protected:
    void closeEvent(QCloseEvent *) {this->deleteLater();}
protected slots:
    void openFile_slots();
    void removeFile_slots();
private:
    Ui::ShowLog *ui;

    QString dirName;

    QString openFileName;

    QGridLayout *mainLayout;

    QAction *openFile;
    QAction *removeFile;

    void setcolor();


};

#endif // SHOWLOG_H
