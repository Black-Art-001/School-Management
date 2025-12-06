#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QSqlDatabase> // data base
#include <QSqlQuery> // connector to data base

#include <QSqlQueryModel> // create a model for widget

#include <QMessageBox> // message box
#include <QDebug> // output data

#include "database.h"
#include "addtable.h"

#include <QFileDialog> // for creating dialog
#include <QDialog> // open new dialog

#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout> // vertical box
#include <QHBoxLayout> // horizontally box
#include <QLineEdit>

#define qout qDebug()


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isDataBaseOpened(false)
{
    ui->setupUi(this);

    this->setTableFont() ; // set font for all texts

    QString path = "D:/dataBase" ;
    QString dataBaseName = "schoolDataBase.db" ;

    QObject::connect(ui->actionOpen , &QAction::triggered , this , &MainWindow::openDataBaseFile) ;
    QObject::connect(ui->show_table , &QPushButton::clicked , this , &MainWindow::showTable_); // show button
    QObject::connect(ui->insert_table, &QPushButton::clicked , this ,&MainWindow::Insert) ; // insert button
    QObject::connect(ui->remove, &QPushButton::clicked , this ,&MainWindow::removeByRow) ; // remove button
    QObject::connect(ui->select_table, &QComboBox::activated , this , &MainWindow::changeTable) ; // select table
    QObject::connect(ui->edit_cell , &QPushButton::clicked , this , &MainWindow::editTable) ; // select table
    QObject::connect(ui->actionclear_all , &QAction::triggered , this , &MainWindow::clearAll ) ; // clear all data in table
    QObject::connect(ui->actionShow_ROWID, &QAction::triggered , this , &MainWindow::RoidVisibilty ) ; // change roid visible or unvisible
    QObject::connect(ui->create , &QPushButton::clicked , this ,&MainWindow::addNewTable) ; // create new table
    QObject::connect(ui->dropTable , &QPushButton::clicked , this , &MainWindow::DropTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// get data base location in system
void MainWindow::getAddress(QString filePath)
{

    int lastDOT = filePath.lastIndexOf(".") ;
    int lastSlash = filePath.lastIndexOf("/" , lastDOT) ;
    file_name = filePath.mid( lastSlash + 1 , lastDOT) ;
    file_path = filePath.left(lastSlash) ;
    qDebug() << "file path : " << file_path ;
    qDebug() << "file name : " << file_name ;
}

// fill in data
void MainWindow::openDataBase()
{

    if(this->isDataBaseOpened == false){
        data = new DataBase(file_path , file_name) ;
        this->isDataBaseOpened = true ;
    }
    else
        qDebug() << "data base is opend " << data ;
}

void MainWindow::closeDataBase()
{
    if(this->isDataBaseOpened == true){
        this->isDataBaseOpened = false ;
        delete data ;
    }
    else
        qDebug()<< "data base does not open " ;
}

void MainWindow::newFiledb()
{
    QString fileCaption = "create new file" ;

    if(this->isDataBaseOpened == true){
        fileCaption = "save file" ;
    }
    QString filePath = QFileDialog::getSaveFileName(this , fileCaption , "/home" , "Database Files (*.db);;All Files (*)") ;

    if(not filePath.isEmpty() and not filePath.endsWith(".db") ){
        filePath += ".db" ;
    }
    qDebug() << filePath ;
    this->getAddress(filePath) ;
}

void MainWindow::openFiledb()
{
    QString filePath = QFileDialog::getOpenFileName(this , "open file" , "/home" , "Data Base (*.db)") ;
    qDebug() <<  filePath ;
    this->getAddress(filePath) ;
}

bool MainWindow::areYouSure(QWidget *parent, QString title, QString text , QMessageBox::Icon icon)
{
    QMessageBox  w(icon , title , text , QMessageBox::Ok | QMessageBox::Cancel , parent) ;
    int index = w.exec() ;
    switch (index) {
    case QMessageBox::Ok: return true ;
    case QMessageBox::Cancel: return false;
    }
    qDebug() << "result of message box is out of range : " << index ;
    return false  ;
}

void MainWindow::setTablesInComboBox()
{
    if(ui->select_table->count() != 0 )
        ui->select_table->clear() ; // clear all items in combo box
    QStringList allTables = data->allTable() ;

    ui->select_table->addItems(allTables) ;

    int index = allTables.indexOf(data->getTable()) ; // find curent index
    ui->select_table->setCurrentIndex(index) ; // set curent index in combo box

}

void MainWindow::DropTable()
{
    if(this->isDataBaseOpened){
        if(this->areYouSure(this , "Delete Table" , "Do you want delete current table ?" , QMessageBox::Question)){
            int index = data->allTable().indexOf(data->getTable()) ;
            if(index > 0) index-- ;
            data->deleteTable() ;
            selectTable(index);
            this->setTablesInComboBox() ;
            this->showTable_() ;
        }
    }
}

QStringList MainWindow::selectTable(int index)
{
    if(this->isDataBaseOpened){
        QStringList allTables = data->allTable() ;
        if(index >= 0 and index < allTables.size()) // if index be -1 jsut return list and if index is invalid do nothing !
        {
            data->setTableName(allTables[index]) ; // select true table
            data->setTableInfo() ; // extract all name and type of this table ! we can access it with name and type
        }
        return allTables ;
    }
    else
        return QStringList();
}

void MainWindow::Insert()
{
    QDialog * insertDialog = new QDialog(this) ;

    QStringList allIndexeName = data->getName() ; // get names
    QStringList allIndexType = data->getType() ; // get type

    int size = allIndexeName.size() ;

    QGridLayout *layout = new QGridLayout(insertDialog) ;

    QVector<QLineEdit*> lines ;  // get a line edits

    // add widgets
    for(int i = 0 ; i < size ; i++)
    {
        QLabel * label = new QLabel(allIndexeName[i] , insertDialog) ;

        QLineEdit * lineEdit = new QLineEdit(insertDialog) ;
        lineEdit->setPlaceholderText(allIndexeName[i]) ;

        if(allIndexType[i] == "INTEGER"){
            QIntValidator * validator = new QIntValidator(insertDialog); // create a validator
            lineEdit->setValidator(validator) ;
        }

        lines.append(lineEdit) ;

        layout->addWidget(label , i , 0) ;
        layout->addWidget(lineEdit , i , 1) ;
        qDebug()<< "we add " << allIndexeName[i] ;

    }

    QDialogButtonBox * btns = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel , insertDialog) ;
    layout->addWidget(btns , size , 0 , 1 , 2) ;

    insertDialog->setLayout(layout) ;

    QObject::connect(btns , &QDialogButtonBox::accepted , insertDialog , &QDialog::accept) ;
    QObject::connect(btns , &QDialogButtonBox::rejected , insertDialog , &QDialog::reject) ;

    if(insertDialog->exec() == QDialog::Accepted)
    {
        QString Values ;
        // make a valuse for SQL
        for(int i = 0 ; i < size ; i++){
            QString val = lines[i]->text() ;
            if( allIndexType[i] == "TEXT"){
                if(val.size() == 0)
                    val = "'NULL'" ;
                else {
                    val = "'" + val + "'" ;
                }
            }
            else{
                if(val.size() == 0)
                    val = "0" ;
            }
            Values.append(val) ;
            if( i < size - 1)
                Values.append(",") ;
        }

        qDebug() << Values ;
        data->Insert(Values) ;
        showTable_() ;
    }

}

void MainWindow::removeByRow()
{
    if(isDataBaseOpened){
        int row = ui->tableView->currentIndex().row() ;
        qDebug()<<" selected row is : " <<  row ;
        data->removeRow(row) ;
    }
    this->showTable_() ;
}

void MainWindow::changeTable(int index)
{
    QStringList alltable = data->allTable() ; // get all table
    data->setTableName(alltable[index]); // set table name
    this->showTable_() ; // show table again
    data->setTableInfo(); // get table info again

}

void MainWindow::editTable()
{
    int row = ui->tableView->currentIndex().row() ;
    int col = ui->tableView->currentIndex().column() ;

    if(row == -1 or col == -1)
        return;
    else{
        QDialog *editWindow = new QDialog(this) ;
        QGridLayout *layout = new QGridLayout(editWindow) ;

        editWindow->setWindowTitle("Edit Cell") ;

        QString index_name = data->getName()[col] ;
        QString index_type = data->getType()[col] ;
        QLabel * name = new QLabel( index_name + " : " , editWindow ) ;
        QLineEdit *lineEdit = new QLineEdit(editWindow) ;
        lineEdit->setPlaceholderText("new data") ;

        bool cellIsInteger = (index_type == "INTEGER") ;

        if(cellIsInteger){
            QIntValidator* validator = new QIntValidator(editWindow) ;
            lineEdit->setValidator(validator) ;
        }

        QDialogButtonBox *btns = new QDialogButtonBox(editWindow) ;
        btns->addButton(QDialogButtonBox::Save ) ;
        btns->addButton(QDialogButtonBox::Cancel);

        QObject::connect(btns , &QDialogButtonBox::accepted , editWindow , &QDialog::accept) ;
        QObject::connect(btns , &QDialogButtonBox::rejected , editWindow , &QDialog::reject) ;

        layout->addWidget(name , 0 , 0 ) ;
        layout->addWidget(lineEdit , 0 , 1) ;
        layout->addWidget(btns , 1 , 0 , 1 , 2) ;

        editWindow->setLayout(layout) ;

        if(editWindow->exec() == QDialog::Accepted){
            QString newVal= lineEdit->text() ;
            if(cellIsInteger and newVal.size() == 0)
                newVal = "0" ;
            else if (not cellIsInteger){
                if(newVal.size() == 0)
                    newVal = "NULL" ;
                newVal = "'" + newVal + "'" ;
            }
            qDebug()<<newVal ;
            data->editCell(col , row , newVal) ;
        }

        this->showTable_() ;
        ui->tableView->selectRow(row) ;
    }
}

void MainWindow::clearAll()
{
    if(this->isDataBaseOpened){
        qDebug()<< "clear all message inserted ! " ;
        if(this->areYouSure(this , "clear all data" , "Do you want delete all data in table : " + data->getTable() , QMessageBox::Warning))
        {
            if(this->areYouSure(this , "Warning" , "If you delete data , you never be able to restore it !\nStill Are you sure ?" , QMessageBox::Critical))
            {
                data->ClearAll() ;
            }
        }
        this->showTable_() ;
    }
}

void MainWindow::RoidVisibilty()
{
    static bool roidVisibilty = false ; // in starting we do not need to show all row id to users
    if(roidVisibilty) // if it visible
        ui->tableView->setModel(data->getQueryModel(this , false)) ; // make ROWIDSelector parameter false
    else
        ui->tableView->setModel(data->getQueryModel(this , true)) ; // make ROWIDSelector parameter true

    roidVisibilty = not roidVisibilty ; // reverse it value
    ui->actionShow_ROWID->setText(roidVisibilty ? "✗ Hide ROWID" : "✓ Show ROWID"); // update text in it
}

// this will let you to add new table
void MainWindow::addNewTable()
{
    if(this->isDataBaseOpened){
        AddTable * w = new AddTable(this , this->data , UIfont) ; // we share parent and data
        QObject::connect(w , &AddTable::dataReady , this , &MainWindow::readNewTable) ;
        if(w->exec() == QDialog::Accepted){
            this->setTablesInComboBox() ;
            this->showTable_() ;
            this->data->setTableInfo() ;
        }
    }
}

void MainWindow::readNewTable(TableData td)
{
    int size = td.names.size() ; // number of all column
    QString col ;
    QString Pkeys ;

    for(int i = 0 ; i < size ; i++){
        QString type , name;
        name = td.names[i] ;
        switch (td.types[i]) {
        case 0: type = "TEXT" ;
            break;
        case 1 : type = "INTEGER" ;
            break ;
        default:
            break;
        }

        col.append(" '" + name + "' " + type + " ") ; // ' 'name' TYPE '
        if(i != size - 1)
            col.append(',') ; // add comma to end of col
        if(td.Pk[i])
        {
            Pkeys.append("'" + name + "'") ;
            Pkeys.append(",") ;
        }
    }
    if(not Pkeys.isEmpty())
        Pkeys.removeLast();


    qDebug()<< "sended name : " << td.tableName ;
    qDebug()<< "sended column " << col ;
    qDebug()<< "sended primary keys :" << Pkeys ;

    this->data->createTable(td.tableName , col , Pkeys) ;
}

void MainWindow::setUIfont()
{

}

void MainWindow::setTableFont()
{
    ui->tableView->setFont(UIfont) ;
}



// in debug !
void MainWindow::showTable_()
{
    ui->tableView->setModel(data->getQueryModel(this)) ;
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems) ; // these are not work very well together !
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectColumns) ;
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows) ;
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection) ;
    qDebug()<< "table model is set to shown " ;
}

void MainWindow::openDataBaseFile()
{
    if(this->isDataBaseOpened == true)
        if(not this->areYouSure(this , "Try to open new data base" , "Are you want to open new Data Base ?" , QMessageBox::Information))
            return ; // stop this progress
    this->openFiledb() ; // get address
    this->openDataBase() ; // open data base with this address
    this->selectTable(0) ; // if we have some table select first one as default
    this->showTable_();
    this->setTablesInComboBox() ;
    data->setTableInfo() ;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tableView->setModel(data->getQueryModel(this , true)) ;
}

