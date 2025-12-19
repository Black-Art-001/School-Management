#include "mainwindow.h"
#include "startpage.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create on heap
    StartPage *startPage = new StartPage();
    startPage->setWindowTitle("SM 2026") ;
    int result = startPage->exec();
    qDebug() << "Result:" << result;

    MainWindow *mainWindow = nullptr;
    QString selectedAddress;

    if (result == QDialog::Rejected) {
        delete startPage;  // Clean up immediately
        return 0;
    }
    if (result == StartPageResult::OpenSelected) {
        selectedAddress = startPage->getSelectedAddress();
        qDebug() << "Opening:" << selectedAddress;
    }

    // delete start page before main window
    delete startPage;
    startPage = nullptr;

    // Now create main window
    if (result == StartPageResult::OpenSelected) {
        mainWindow = new MainWindow();
        mainWindow->getAddress(selectedAddress);
        mainWindow->openDataBaseFile();
    }
    else if (result == StartPageResult::Continue) {
        mainWindow = new MainWindow();
    }
    if (mainWindow) {
        mainWindow->setWindowTitle("School Management 2026");
        mainWindow->show();
    }
    return a.exec();
}
