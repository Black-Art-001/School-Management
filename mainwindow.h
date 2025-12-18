#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "datacapsul.h"
#include "filehandler.h"
#include<QItemSelection>
#include "SaveLoad.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class DataBase ;
class QIntValidator ;

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
    void setColTags() ;

    QFont getUIfont() const;

protected :
    void closeEvent(QCloseEvent* event) override ;

public slots :
    void setComboBoxTags(int mode) ;
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
    void Search() ;
    void setUpStatusBar() ;
private slots:
    void setUIfont() ; // this is for text that show on ui
    void setTableFont() ; // this is for text that show in table
    void selectUIFont() ;
    void selectTableFont() ;
    void on_pushButton_clicked(); // what is this ?
    void updateZoomPercent(int) ;
    void setSelectionIndex(const QModelIndex selected, const QModelIndex ) ;
    void renameTable() ;
    void save() ;
    void discard() ;
    void saveAs() ;
    void getBackUp() ;
    void resetUiFont() ;
    void resetTableFont() ;

private:
    Ui::MainWindow *ui;
    DataBase *data ;
    QString file_path , file_name ;
    bool isDataBaseOpened ;
    QFont UIfont ;
    QFont TableFont ;
    QIntValidator *intValidator;
    QStringList INTfilter ;
    QStringList TXTfilter ;
    int filterMode ;
    fileHandler fileH ;
    bool somethingChanged ;

};
#endif // MAINWINDOW_H
