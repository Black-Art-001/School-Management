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
#include <QFontDialog>

#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout> // vertical box
#include <QHBoxLayout> // horizontally box
#include <QLineEdit>

#include <QCloseEvent> // for closing event

#define qout qDebug()
#define selection_connection     QObject::connect(ui->tableView->selectionModel() , &QItemSelectionModel::currentChanged , this , &MainWindow::setSelectionIndex)


MainWindow::MainWindow(QWidget *parent , QFont *ui_font , QFont *table_font)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , INTfilter()
    , isDataBaseOpened(false)
{
    ui->setupUi(this);

    UIfont = ui_font ;
    TableFont = table_font ;

    somethingChanged = false ; // nothing to changed



    this->setTableFont() ; // set font for all texts
    this->setUIfont() ; // set font for all UI element

    this->filterMode = -1 ;

    this->setUpStatusBar() ;

    INTfilter = {"equals" , "not equal" , "greater than", "less than",  "at least", "at most"} ;
    TXTfilter = {"equals","contains","starts with","ends with","not contains"} ;

    QAction *openAction = new QAction(QIcon(":/icons/open.png"), tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);

    intValidator = new QIntValidator(this) ;

    ui->show_table->setIcon(style()->standardIcon(QStyle::SP_BrowserReload)) ;
    ui->insert_table->setIcon(style()->standardIcon(QStyle::SP_ArrowForward)) ;
    ui->remove->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton)) ;


    QObject::connect(ui->actionOpen , &QAction::triggered , this , &MainWindow::openFiledb) ; // open existen file
    QObject::connect(ui->actionnew , &QAction::triggered , this , &MainWindow::newFiledb) ; // new file
    QObject::connect(ui->show_table , &QPushButton::clicked , this , &MainWindow::showTable_); // show button
    QObject::connect(ui->insert_table, &QPushButton::clicked , this ,&MainWindow::Insert) ; // insert button
    QObject::connect(ui->remove, &QPushButton::clicked , this ,&MainWindow::removeByRow) ; // remove button
    QObject::connect(ui->select_table, &QComboBox::activated , this , &MainWindow::changeTable) ; // select table
    QObject::connect(ui->edit_cell , &QPushButton::clicked , this , &MainWindow::editTable) ; // edit in table
    QObject::connect(ui->actionclear_all , &QAction::triggered , this , &MainWindow::clearAll ) ; // clear all data in table
    QObject::connect(ui->actionShow_ROWID, &QAction::triggered , this , &MainWindow::RoidVisibilty ) ; // change roid visible or unvisible
    QObject::connect(ui->create , &QPushButton::clicked , this ,&MainWindow::addNewTable) ; // create new table
    QObject::connect(ui->dropTable , &QPushButton::clicked , this , &MainWindow::DropTable);
    QObject::connect(ui->ColName , &QComboBox::currentIndexChanged  , this , &MainWindow::setComboBoxTags) ; // get col num to generate mode (text , int)
    QObject::connect(ui->searchBox , &QPushButton::clicked  , this , &MainWindow::Search) ;
    QObject::connect(ui->actionUIFont , &QAction::triggered , this , &MainWindow::selectUIFont) ; // select ui font
    QObject::connect(ui->actionTable_font_edit , &QAction::triggered , this , &MainWindow::selectTableFont) ; // select table font
    QObject::connect(ui->OpenDataBase , &QPushButton::clicked , this , &MainWindow::openFiledb) ; //
    QObject::connect(ui->closeDataBase , &QPushButton::clicked , this , &MainWindow::closeDataBase) ; //
    QObject::connect(ui->renamTable , &QPushButton::clicked , this , &MainWindow::renameTable) ;
    QObject::connect(ui->actionSave , &QAction::triggered , this , &MainWindow::save) ; // save
    QObject::connect(ui->actionSave_as , &QAction::triggered , this , &MainWindow::saveAs) ; // save as
    QObject::connect(ui->actionGet_backup , &QAction::triggered , this , &MainWindow::getBackUp) ; // make new back up ;

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
        ui->tableView->setModel(nullptr) ;
        ui->dataBaseName->setText("No database is open") ;
        ui->tableName->setText("No table is open") ;
    }
    else
        qDebug()<< "data base does not open " ;
}

void MainWindow::newFiledb()
{
    if(this->isDataBaseOpened == true)
        if(not this->areYouSure(this , "Try to open new data base" , "Are you want to open new Data Base ?" , QMessageBox::Information))
            return ; // stop this progress

    QString filePath = QFileDialog::getSaveFileName(this , "Create new file" , "untitel" , "Database Files (*.db);") ;
    if(not filePath.isEmpty() and not filePath.endsWith(".db") ){
        filePath += ".db" ;
    }
    qDebug() << filePath ;
    this->getAddress(filePath) ;
    this->openDataBaseFile() ;
}

void MainWindow::openFiledb()
{
    if(this->isDataBaseOpened == true)
        if(not this->areYouSure(this , "Try to open new data base" , "Are you want to open new Data Base ?" , QMessageBox::Information))
            return ; // stop this progress

    QString filePath = QFileDialog::getOpenFileName(this , "open file" , "/home" , "Data Base (*.db)") ;
    qDebug() <<  filePath ;
    this->getAddress(filePath) ;
    this->openDataBaseFile() ;
}

bool MainWindow::areYouSure(QWidget *parent, QString title, QString text , QMessageBox::Icon icon)
{
    QMessageBox  w(icon , title , text , QMessageBox::Ok | QMessageBox::Cancel , parent) ;
    w.setFont(*UIfont) ;
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
    if(this->isDataBaseOpened){
        ui->select_table->clear() ;  // Clear existing items
        ui->select_table->addItems(this->data->allTable()) ;  // Add all tables
        int index = data->allTable().indexOf(data->getTable()) ;
        if(index >= 0) // set it to current table
            ui->select_table->setCurrentIndex(index) ;
    }
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
            this->somethingChanged = true ;
        }
    }
}

void MainWindow::setColTags()
{
    // clear all name
    ui->ColName->clear() ;
    // set table names
    ui->ColName->addItems(this->data->getName()) ;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(not somethingChanged){
        event->accept() ;
        return ;
    }

    QMessageBox w("Unsaved Changes" , "Save changes before closing?" , QMessageBox::Information , QMessageBox::Save , QMessageBox::Discard , QMessageBox::Cancel , this) ;
    int result = w.exec() ;
    switch (result) {
    case QMessageBox::Save:
        this->save() ;
        event->accept() ;
        break;
    case QMessageBox::Discard :
        this->discard() ;
        event->accept() ;
        break ;
    case QMessageBox::Cancel :
        event->ignore() ;
        break ;
    default:
        break;
    }
}

void MainWindow::setComboBoxTags(int index)
{
    if(index >= 0 and index < data->getType().size()){
        int mode ;
        // generate mode :
        QString type = data->getType()[index] ;
        if(type == "INTEGER")
            mode = 0 ;
        else
            mode = 1 ;

        if(this->filterMode != mode){
            this->ui->operation_tags->clear() ;
            switch (mode) {
            case 0:  this->ui->operation_tags->addItems(INTfilter) ;
                ui->key->setValidator(intValidator) ;
                break;
            case 1: this->ui->operation_tags->addItems(TXTfilter) ;
                ui->key->setValidator(nullptr) ;
                break;
            default:
                throw std::invalid_argument("inputed mode is not decleared") ;
                break;
            }
            ui->operation_tags->setCurrentIndex(0) ;
            this->filterMode = mode ; // updata last ;
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
        ui->tableName->setText(data->getTable()) ;
        return allTables ;
    }
    else
        return QStringList();
}

void MainWindow::Insert()
{
    QDialog * insertDialog = new QDialog(this) ;
    insertDialog->setFont(*UIfont) ;
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
            QString val = lines[i]->text() ; // danger code ! when exec finished it can delete all its chill
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
        this->somethingChanged = true ;
    }

}

void MainWindow::removeByRow()
{
    if(isDataBaseOpened){
        int row = ui->tableView->currentIndex().row() ;
        qDebug()<<" selected row is : " <<  row ;
        data->removeRow(row) ;
        this->somethingChanged = true ;
    }
    this->showTable_() ;
}

void MainWindow::changeTable(int index)
{
    QStringList alltable = data->allTable() ; // get all table
    data->setTableName(alltable[index]); // set table name
    this->showTable_() ; // show table again
    data->setTableInfo(); // get table info again
    this->setColTags() ;
    ui->tableName->setText(data->getTable()) ;
}

void MainWindow::editTable()
{
    int row = ui->tableView->currentIndex().row() ;
    int col = ui->tableView->currentIndex().column() ;

    if(row == -1 or col == -1)
        return;
    else{
        QDialog *editWindow = new QDialog(this) ;
        editWindow->setFont(*UIfont) ;
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
        this->somethingChanged = true ;
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
                this->somethingChanged = true ;
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
        AddTable * w = new AddTable(this , this->data , *UIfont) ; // we share parent and data
        w->setFont(*UIfont) ;
        QObject::connect(w , &AddTable::dataReady , this , &MainWindow::readNewTable) ;
        if(w->exec() == QDialog::Accepted){
            this->setTablesInComboBox() ;
            this->showTable_() ;
            this->data->setTableInfo() ;
            this->setColTags() ;
            this->somethingChanged = true ;
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

void MainWindow::Search()
{
    QString key = ui->key->text();
    if (key.isEmpty()) {
        this->showTable_();
        return;
    }

    QString operation = ui->operation_tags->currentText();
    QString col = ui->ColName->currentText();

    QString code;

    // SWITCH BETWEEN TEXT AND INT FILTER
    if (filterMode == 0)   // INTEGER MODE
    {
        if (operation == "equals")
            code = QString("%1 = %2").arg(col, key);

        else if (operation == "not equal")
            code = QString("%1 <> %2").arg(col, key);

        else if (operation == "greater than")
            code = QString("%1 > %2").arg(col, key);

        else if (operation == "less than")
            code = QString("%1 < %2").arg(col, key);

        else if (operation == "at least")
            code = QString("%1 >= %2").arg(col, key);

        else if (operation == "at most")
            code = QString("%1 <= %2").arg(col, key);
    }
    else    // TEXT MODE
    {
        QString quoted = "'" + key + "'";

        if (operation == "equals")
            code = QString("%1 = %2").arg(col, quoted);

        else if (operation == "contains")
            code = QString("%1 LIKE '%%2%'").arg(col).arg(key);

        else if (operation == "starts with")
            code = QString("%1 LIKE '%2%'").arg(col).arg(key + "%");

        else if (operation == "ends with")
            code = QString("%1 LIKE '%2%'").arg(col).arg("%" + key);

        else if (operation == "not contains")
            code = QString("%1 NOT LIKE '%%2%'").arg(col).arg(key);
    }

    ui->tableView->setModel(data->searchInTable(this,code));
    selection_connection ;
}

void MainWindow::setUpStatusBar()
{
    QObject::connect(ui->zoomSlider , &QSlider::valueChanged , this,  &MainWindow::updateZoomPercent) ;
    QObject::connect(ui->zoomSlider , &QSlider::valueChanged , this,  &MainWindow::setTableFont) ;
    ui->zoomSlider->setValue(100);
}


void MainWindow::setSelectionIndex(const QModelIndex selected, const QModelIndex deselected){

    if(not selected.isValid()){
        ui->index->setText("No index selected") ;
    }
    else {
        int row = selected.row() ;
        int col = selected.column() ;
        qDebug() << "Selected: Row" << row << "Column" << col;

        ui->index->setText("Selected: Row : " + QString::number(row) + " Column : " + QString::number(col)) ;
    }
}

void MainWindow::renameTable()
{
    if(isDataBaseOpened){
        QDialog * w = new QDialog(this) ;
        QString newName ;

        w->setWindowTitle("Rename Table");
        w->setFont(*UIfont);
        w->setAttribute(Qt::WA_DeleteOnClose);

        QVBoxLayout* main = new QVBoxLayout(w) ;

        QLabel *msg = new QLabel("Change : " + data->getTable() + " to : " , w) ;
        QLineEdit * nameEdit = new QLineEdit(w) ;
        nameEdit->setPlaceholderText("new name") ;

        QHBoxLayout *l = new QHBoxLayout(w) ;
        l->addWidget(msg) ;
        l->addWidget(nameEdit) ;
        QDialogButtonBox *btn = new QDialogButtonBox(w) ;
        btn->addButton(QDialogButtonBox::Ok) ;
        btn->addButton(QDialogButtonBox::Cancel) ;
        QObject::connect(btn , &QDialogButtonBox::accepted , w , &QDialog::accept) ;
        QObject::connect(btn , &QDialogButtonBox::rejected , w , &QDialog::reject) ;

        QObject::connect(w , &QDialog::accepted , nameEdit , [&newName , &nameEdit](){newName = nameEdit->text() ; }) ;
        main->addLayout(l) ;
        main->addWidget(btn);

        if(w->exec() == QDialog::Accepted)
        {
            if(newName.isEmpty()) {
                QMessageBox::warning(this, "Error", "Table name cannot be empty!");
                return;
            }

            if(newName == data->getTable()) {
                QMessageBox::information(this, "Info", "Table name unchanged.");
                return;
            }

            data->renameTable(newName) ;
            this->somethingChanged = true ;
            this->setTablesInComboBox() ;
            ui->tableName->setText(data->getTable()) ;

            qDebug()<< "new name : " + newName ;
            qDebug()<< data->allTable() ;
            this->somethingChanged = true ;
        }
    }
}

void MainWindow::save()
{
    fileH.discardBackup() ; // remove backup file
    fileH.createBackup(file_path + "/" + file_name) ; // make new back up
    this->somethingChanged = false ; // all changes saved
}

void MainWindow::discard()
{
    this->closeDataBase() ;
    fileH.restoreFromBackup() ;
}

void MainWindow::saveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this , "Create new file" , "untitel" , "Database Files (*.db);") ;
    if(not filePath.isEmpty() and not filePath.endsWith(".db") ){
        filePath += ".db" ;
    }

    fileH.saveAs(filePath) ;
}

void MainWindow::getBackUp()
{
    fileH.createBackup(file_path + "/" + file_name) ; // recreate back up
}

void MainWindow::setUIfont()
{
    QList<QWidget *> widgets = this->findChildren<QWidget*>() ;

    foreach (QWidget *widget, widgets) {
        if(qobject_cast<QPushButton*>(widget)) {
            widget->setFont(*UIfont);
        }
        else if(qobject_cast<QLabel*>(widget)) {
            widget->setFont(*UIfont);
        }
        else if(qobject_cast<QComboBox*>(widget)) {
            widget->setFont(*UIfont);
        }
        else if(qobject_cast<QLineEdit*>(widget)) {
            widget->setFont(*UIfont);
        }
        else if(qobject_cast<QGroupBox*>(widget)) {
            widget->setFont(*UIfont);
        }
    }
}

void MainWindow::setTableFont()
{
    QFont font = *TableFont ;
    font.setPointSize(font.pointSize() * ui->zoomSlider->value() / 100) ;
    qDebug()<< font ;
    ui->tableView->setFont(font) ;
}

void MainWindow::selectUIFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok , *UIfont , this , "Select UI font") ;
    if(ok)
        *UIfont = font ;
        this->setUIfont() ;
}

void MainWindow::selectTableFont()
{
    bool ok ;
    QFont font = QFontDialog::getFont(&ok , *TableFont ,  this , "select Table font") ;
    if(ok)
        *TableFont = font ;
        this->setTableFont() ;
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
    selection_connection ;
}

void MainWindow::openDataBaseFile()
{
    fileH.createBackup(file_path + "/" + file_name) ; // make back up
    this->openDataBase() ; // open data base with this address
    this->selectTable(0) ; // if we have some table select first one as default
    this->showTable_();
    this->setTablesInComboBox() ;
    data->setTableInfo() ;
    this->setColTags() ;
    ui->dataBaseName->setText(this->file_name) ;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tableView->setModel(data->getQueryModel(this , true)) ;
}

void MainWindow::updateZoomPercent(int size)
{
    ui->zoomPercent->setText(QString(" %1%").arg(size)) ;
    ui->zoomPercent->setMinimumWidth(40) ;
}

