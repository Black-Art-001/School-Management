#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QSqlDatabase> // data base
#include <QSqlQuery> // connector to data base

#include <QSqlQueryModel> // create a model for widget

#include <QMessageBox> // message box
#include <QDebug> // output data

#include "database.h"


#include <QFileDialog> // for creating dialog
#include <QDialog> // open new dialog

#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>

#define qout qDebug()


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isDataBaseOpened(false)
{
    ui->setupUi(this);

    QString path = "D:/dataBase" ;
    QString dataBaseName = "schoolDataBase.db" ;

    QObject::connect(ui->actionOpen , &QAction::triggered , this , &MainWindow::openDataBaseFile) ;
    QObject::connect(ui->show_table , &QPushButton::clicked , this , &MainWindow::showTable_); // show button
    QObject::connect(ui->insert_table, &QPushButton::clicked , this ,&MainWindow::Insert) ; // insert button
    QObject::connect(ui->remove, &QPushButton::clicked , this ,&MainWindow::removeByRow) ; // remove button
    QObject::connect(ui->select_table, &QComboBox::activated , this , &MainWindow::changeTable) ; // select table
    QObject::connect(ui->edit_cell , &QPushButton::clicked , this , &MainWindow::editTable) ; // select table


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
    case 0: return true ;
    case 1: return false;
    }
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

QStringList MainWindow::selectTable(int index)
{
    if(this->isDataBaseOpened){
        QStringList allTables = data->allTable() ;
        if(index >= 0 and index < allTables.size()) // if index be -1 jsut return list and if index is invalid do nothing !
        {
            data->setTableName(allTables[index]) ;
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

