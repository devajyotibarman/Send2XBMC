#ifndef SEND2XBMCMAINWINDOW_H
#define SEND2XBMCMAINWINDOW_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QLoggingCategory>
#include <QFile>
#include <QMessageBox>
#include <QList>
#include <QStandardPaths>

namespace Ui {
class Send2XBMCMainWindow;
}

class Send2XBMCMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit Send2XBMCMainWindow(QWidget *parent = 0);
    ~Send2XBMCMainWindow();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void replyFinished(QNetworkReply* replyDone);


    void on_pushButton_2_clicked();

private:
    Ui::Send2XBMCMainWindow *ui;
    QFile *iniFile;
    QString* setJsonRequest(void);
    QList<QString> xbmcList;
};

#endif // SEND2XBMCMAINWINDOW_H
