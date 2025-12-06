#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "datacapsul.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class DataBase ;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getAddress(QString filePath) ; // extract address and set in file path and file name
    void openDataBase() ; // open new data base
    void closeDataBase(); // close last data base
    void newFiledb() ; // save data base
    void openFiledb() ;
    bool areYouSure(QWidget *parent, QString title, QString text , QMessageBox::Icon icon) ; // make a question befor doing action !
    void setTablesInComboBox() ;
    void DropTable();
    friend class AddTable ;

    QFont getUIfont() const;

public slots :
    void showTable_() ;
    void openDataBaseFile() ;
    QStringList selectTable(int index = -1);
    void Insert() ;
    void removeByRow() ;
    void changeTable(int index) ;
    void editTable() ;
    void clearAll() ;
    void RoidVisibilty() ;
    void addNewTable() ;
    void readNewTable(TableData td) ;

private slots:
    void setUIfont() ; // this is for text that show on ui
    void setTableFont() ; // this is for text that show in table
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DataBase *data ;
    QString file_path , file_name ;
    bool isDataBaseOpened ;
    QFont UIfont ;
    QFont TableFont ;
;
};
#endif // MAINWINDOW_H
