#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>


class DataBase
{
public:
    DataBase(const QString path , const QString file_name);
    // string should use "string" in text ( use \" to handle it )
    void Insert(QString values) ;
    // rows should be { name TYPE , }
    void createTable(QString table , QString rows , QString pk = "") ;
    // remove cell with info like : Index = Value
    void remove(QString Index_Value) ;
    // remove current file !
    void removeRow(int row) ;
    int findRowID(int row) ;
    // clear all value
    void ClearAll() ;
    // delete table
    void deleteTable() ;
    // change data target is index that we whant to change
    // new value is new data is set in index
    // info is condition to find true index
    void Update(QString target , QString new_value , QString info) ;
    // this is wrapper for update
    void editCell(int col , int row , QString new_value);
    void setTableName(QString table) ;
    void setTableInfo() ;
    QStringList allTable() ;
    QSqlDatabase const* dataBaseAddress() const ;
    QSqlQueryModel* getQueryModel(QObject * parent, bool ROWIDSelector = false) ;
    QSqlQueryModel* searchInTable(QObject * parent , QString condition) ;
    ~DataBase() ;
    QStringList getType() ;
    QStringList getName() ;
    int getPK() ;
    QString getTable() ; // return table name
    void renameTable(QString name) ;
    void saveDataBase() ;
private:
    QSqlQuery query ;
    QSqlDatabase dataBase ;
    QString _table ;
    QStringList IndexName ;
    QStringList IndexType ;
    int IndexPKName ;
};
#endif // DATABASE_H
