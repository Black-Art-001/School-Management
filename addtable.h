#ifndef ADDTABLE_H
#define ADDTABLE_H

#include "datacapsul.h"
#include <QDialog>
#include <forward_list>

class QLabel ;
class QLineEdit ;
class QVBoxLayout ;
class DataBase ;
class QFont ;
class QTableWidget ;


class AddTable : public QDialog
{
    Q_OBJECT
signals :
    void dataReady(TableData td) ;

public:
    // data tables name with assosiation through parent (main windiw who got data )
    AddTable(QWidget * parent , DataBase * db , QFont &font) ;
    int pop(int) ;
    void pushBack(int val) ;
    QString extractNames() ;
    void extractInfo() ;

public slots :
    bool isAllValid() ;
    void addRow() ;
    void removeRow(int row) ;

private slots:
    bool onTextChanged() ; // set true text in table
    void onSaveClicked() ; // return all data that collected

private :
    QLineEdit* extractLine(int row) ;
    void setupUI() ;
    void loadExistingTable() ;
    void addButtons() ;
    void mainFieldInit() ;

    std::forward_list<int> code ;
    long long int numAllRow ;
    const int numCol ;
    int numRow ;
    DataBase * data ;
    QLabel * smallText ;
    QLabel * validate ;
    QLineEdit*TableName ;
    QWidget * parent ;
    QVBoxLayout * mainLayout ; // main layout that all layout set on it
    QStringList alltableNames;
    QFont font ;
    QTableWidget * table ;
    TableData tableData ;
};

#endif // ADDTABLE_H
