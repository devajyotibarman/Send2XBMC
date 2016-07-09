#include "send2xbmcmainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
    Send2XBMCMainWindow w;
    w.setWindowIcon(QIcon(":/icons/icon.png"));
    w.show();

    return a.exec();
}
