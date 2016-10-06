#include "send2xbmcmainwindow.h"
#include "ui_send2xbmcmainwindow.h"

Send2XBMCMainWindow::Send2XBMCMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Send2XBMCMainWindow)
{
    ui->setupUi(this);
    qDebug() << QStandardPaths::locate(QStandardPaths::HomeLocation,
                                       QString(),
                                       QStandardPaths::LocateDirectory).append((".send2XBMC.ini"));

    iniFile = new QFile(QStandardPaths::locate(QStandardPaths::HomeLocation,
                                               QString(),
                                               QStandardPaths::LocateDirectory).append((".send2XBMC.ini")));
    if(!iniFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Cannot Open INI File";
    }

    QTextStream in(iniFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        xbmcList << line;
//        qDebug() << line;
        ui->comboBox->addItem(line);
    }

//    int i = 0;
//    while(i < xbmcList.size())
//    {
//        qDebug() << xbmcList.at(i++);
//    }

    ui->comboBox_2->addItem("Play");
    ui->comboBox_2->addItem("Enqueue");
}

Send2XBMCMainWindow::~Send2XBMCMainWindow()
{
    delete ui;
}

void Send2XBMCMainWindow::on_pushButton_clicked()
{
//    qDebug("Got A Button Click Event");
    if(!ui->comboBox->currentText().isEmpty())
    {
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest *request = new QNetworkRequest();
        QString *content = setJsonRequest();
//        qDebug() << "Content: " << *content;
        QUrl *requestUrl = new QUrl();
//        qDebug() << "Request is: "<< ui->comboBox->currentText();
        requestUrl->setScheme("http");
        requestUrl->setHost(ui->comboBox->currentText());
        requestUrl->setPort(8080);
        requestUrl->setPath("/jsonrpc");
        request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request->setUrl(*requestUrl);

//        qDebug() << "Sending Request: " << requestUrl->toString();
        connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
        manager->post(*request, content->toLocal8Bit());

    }
}

void Send2XBMCMainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->pushButton->setEnabled(true);
}

void Send2XBMCMainWindow::replyFinished(QNetworkReply* replyDone)
{
//    qDebug() << "Finished Request!" << ui->comboBox->currentText();
    if(xbmcList.contains(ui->comboBox->currentText()))
    {
//        qDebug() << "Found a child";
    }
    else
    {
        ui->comboBox->addItem(ui->comboBox->currentText());
        xbmcList << ui->comboBox->currentText();
        QTextStream out(iniFile);
        out << ui->comboBox->currentText() << endl;
    }
}

QString* Send2XBMCMainWindow::setJsonRequest()
{
    QString *content;
    if(ui->comboBox_2->currentText() == "Enqueue")
    {
//        qDebug() << "Current Selection: "<< ui->comboBox_2->currentText();
        content = new QString("{\"jsonrpc\": \"2.0\", \"method\": \"Playlist.Add\", \"params\":{\"playlistid\": 1, \"item\": {\"file\" : \"plugin://plugin.video.youtube/?action=play_video&videoid=");
    }
    else
    {
        content = new QString("{\"jsonrpc\": \"2.0\", \"method\": \"Player.Open\", \"params\":{\"item\": {\"file\" : \"plugin://plugin.video.youtube/?action=play_video&videoid=");
    }
    QString temp = ui->lineEdit->text();

    if(temp.contains("youtu.be"))
    {
        QRegularExpression rx("(youtu.be/)([a-zA-Z0-9\\_\\-])+&?");
        QRegularExpressionMatch match = rx.match(temp);
        temp = match.captured(0).remove(0, 9);
//        qDebug() << temp;
    }
    else
    {
        QRegularExpression rx("(v[/=])([a-zA-Z0-9\\_\\-])+&?");
        QRegularExpressionMatch match = rx.match(temp);
        temp = match.captured(0).remove(0, 2);
        if(temp.contains('&'))
        {
            temp.chop(1);
        }
    }
//    qDebug() << temp ;
    content->append(temp);
    content->append("\" }}, \"id\" : \"1\"}");
    return content;
}

void Send2XBMCMainWindow::on_pushButton_2_clicked()
{
    QMessageBox m;
    m.setText(QString("(c) Devajyoti Barman, 2016"));
    m.setWindowIcon(QIcon(":/icons/icon.png"));
    m.exec();
}
