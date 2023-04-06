#include "main_window.h"
#include <QApplication>
#include <QSslSocket>
#include <QDebug>

int main(int argc, char *argv[])
{
    //    qDebug()<< QSslSocket::sslLibraryBuildVersionString();
    //    return 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
