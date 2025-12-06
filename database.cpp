#include "database.h"
#include <QDebug>
#include <QDir>
#include <QObject>

DataBase::DataBase(const QString path , const QString file_name) : IndexPKName(-1) // index -1 means no sell are primery key
{
    QDir dirHandler ;
    if(not dirHandler.exists(path)) // check for directory exist or not !
        dirHandler.mkdir(path);


    dataBase = QSqlDatabase::addDatabase("QSQLITE") ; // set data base engine
    dataBase.setDatabaseName(path + "/" + file_name); // find data base or if not exit create one

    qDebug() << path + "/" + file_name ;

    if(not dataBase.open()){
        qDebug() << "we can not open the query !" ;
    }

    query = QSqlQuery(dataBase) ; // send data base to query to work with it through a query
}

// string should use "string" in text ( use \" to handle it )
void DataBase::Insert(QString values)
{
    QString sqlCode = "INSERT INTO " + _table + " VALUES (" + values + ");" ;
    qDebug() << sqlCode ;
    this->query.exec(sqlCode) ;
}

// rows should be { name TYPE , }
void DataBase::createTable(QString table, QString rows, QString pk)
{
    _table = table ;
    QString sqlPkCode = ");" ;
    if(not pk.isEmpty())
        sqlPkCode = ", PRIMARY KEY (" + pk +  "));" ;

    QString sqlCode = "CREATE TABLE IF NOT EXISTS " + table + "(" + rows + sqlPkCode;
    qDebug() << sqlCode ;

    query.exec(sqlCode) ;
}

// remove cell with info like : Index = Value
void DataBase::remove(QString Index_Value)
{
    QString sqlCode = "DELETE FROM " + _table + " WHERE " +  Index_Value ;
    qDebug() << sqlCode ;
    this->query.exec(sqlCode) ;
}

// this is a wrapper for remove function
void DataBase::removeRow(int row)
{
    int id = this->findRowID(row);
    if(id == -1)
        qDebug()<< "ROWID does not found !" ;
    else {
        this->remove("ROWID = " + QString::number(id)) ;
    }
}

int DataBase::findRowID(int row)
{
    int index = row ;
    QString sqlCode = "SELECT ROWID FROM " + _table + " ORDER BY ROWID";
    qDebug()<<sqlCode ;
    query.exec(sqlCode) ;

    while(query.next()){
        if(index == 0)
            return  query.value(0).toInt() ;
        index -- ;
    }
    return -1 ; // does not exit
}

// delete all cell from table
void DataBase::ClearAll()
{
    query.exec("DELETE FROM " + _table );
    qDebug() <<"DELETE FROM " + _table  ;
}

void DataBase::deleteTable()
{
    query.exec("DROP TABLE " + this->_table );
    qDebug() <<"DROP TABLE " + this->_table  ;
}

void DataBase::Update(QString target , QString new_value , QString info)
{
    QString sqlCode = "UPDATE " + _table + " SET " + target + " = " + new_value +  " WHERE " + info ;
    qDebug() << sqlCode ;
    query.exec(sqlCode) ;
}

// wrapper function for update cells
void DataBase::editCell(int col, int row, QString new_value)
{
    int RowID = this->findRowID(row) ;
    QString type = IndexName[col] ;

    this->Update(type , new_value , " ROWID = " + QString::number(RowID)) ;

    qDebug() << "input row : " << row << " and ROWID : " << RowID << " condition : " <<  " ROWID = " + QString::number(RowID) ;
}

void DataBase::setTableName(QString table)
{
    this->_table = table ;
    qDebug() << _table ;
}

// data stored : name , type , pk !
void DataBase::setTableInfo()
{
    if(IndexName.size() != 0)
        IndexName.clear() ;
    if(IndexType.size() != 0)
        IndexType.clear() ;

    query.exec("PRAGMA TABLE_INFO(" + _table +") ") ;
    int counter = 0 ;
    while(query.next())
    {
        IndexName.append(query.value(1).toString()) ; // for name
        IndexType.append(query.value(2).toString()) ;  // for type
        if(query.value(5) == 1)
        {
            IndexPKName = counter++; // find PK
        }
    }
}

QStringList DataBase::allTable()
{
    query.exec("SELECT name FROM sqlite_master WHERE type = 'table'") ;

    QStringList allTableName ;
    while(query.next())
    {
        allTableName.append(query.value(0).toString()) ;
    }
    qDebug()<<allTableName ;
    return allTableName ;
}

QSqlDatabase const * DataBase::dataBaseAddress() const
{
    return &dataBase ;
}

QSqlQueryModel *DataBase::getQueryModel(QObject * parent , bool ROWIDSelector)
{
    QString rist = "*" ;
    if(ROWIDSelector)
        rist = "ROWID , *" ;
    query.exec("SELECT " + rist + " FROM " + _table + " ORDER BY ROWID" );
    qDebug() << "SELECT " + rist + " FROM " + _table + " ORDER BY ROWID" ;

    QSqlQueryModel * m = new QSqlQueryModel(parent) ;
    m->setQuery(query) ;

    return m;
}

DataBase::~DataBase()
{
    dataBase.close() ;
}

QStringList DataBase::getType()
{
    return IndexType ;
}

QStringList DataBase::getName()
{
    return IndexName ;
}

int DataBase::getPK()
{
    return IndexPKName ;
}

QString DataBase::getTable()
{
    return _table;
}


