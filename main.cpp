#include "mainwindow.h"
#include "startpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartPage startPage;
    int result = startPage.exec();
    qDebug() << "===== dialog closed =====" << ">> Result : " << result ;
    if (result == QDialog::Rejected) {
        return 0; // User canceled
    }
    MainWindow *mainWindow = nullptr;
    if (result == StartPageResult::OpenSelected) {
        qDebug() << "Opening selected file";
        mainWindow = new MainWindow();
        QString address = startPage.getSelectedAddress();
        qDebug()<< "we will open : " << address ;
        mainWindow->getAddress(address);
        mainWindow->openDataBaseFile();
    }
    else if (result == StartPageResult::Continue) {
        qDebug() << "Continuing without database";
        mainWindow = new MainWindow();
    }
    if (mainWindow) {
        mainWindow->show();
    }
    return a.exec();
}
