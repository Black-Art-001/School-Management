#include "addtable.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QTableWidget>
#include <QHeaderView>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "database.h"

AddTable::AddTable(QWidget *parent , DataBase * db , QFont &font) : QDialog(parent) , numCol(4)
{
    numRow = 0 ; // number of row at firs time
    numAllRow = 0  ; // number all of row that created
    if(parent == nullptr or db == nullptr) throw std::invalid_argument("parent or data base can not be null") ;
    this->parent = parent ; // set inputed pparent in parent variable
    this->data = db ;
    this->font = font ; // set font

    this->setMinimumSize(480 , 360) ;

    setupUI() ;
    loadExistingTable() ;
}

void AddTable::setupUI()
{
    mainLayout = new QVBoxLayout(this) ;

    QGridLayout *baseDate = new QGridLayout(this) ;

    QLabel * TableLabel = new QLabel("table name " , this ) ;
    TableName = new QLineEdit(this) ;
    smallText  = new QLabel("table name can not be empty" , this) ;
    TableName->setPlaceholderText("Enter name of table") ;
    QFont smallFont = font ;

    qDebug() << "font pixel size" << font.pointSize() ;
    smallFont.setPointSize(qMax(8 , font.pointSize() - 2)) ; // if inputed font be 1 result come 0
    smallText->setFont(smallFont) ;
    smallText->setStyleSheet("color : yellow") ;

    connect(TableName , &QLineEdit::textChanged , this , &AddTable::onTextChanged) ; // if text changed work on small text and set true text

    baseDate->addWidget(TableLabel , 0 , 0) ;
    baseDate->addWidget(TableName , 0 , 1) ;
    baseDate->addWidget(smallText , 1 , 1) ; // add this text under the line edit

    QGroupBox * base_data = new QGroupBox("table info" , this) ;

    base_data->setLayout(baseDate) ;

    mainLayout->addWidget(base_data) ;

    this->mainFieldInit() ;
    this->addButtons() ;
    this->setLayout(mainLayout) ;
}

void AddTable::loadExistingTable()
{
    alltableNames = this->data->allTable() ;
}

//in development
void AddTable::addButtons()
{
    QHBoxLayout *btns = new QHBoxLayout(this) ;

    QPushButton *addBtn = new QPushButton("New" , this) ;
    QPushButton *saveBtn = new QPushButton("Save" , this) ;
    QPushButton *cancelBtn = new QPushButton("cancel" , this) ;

    QObject::connect(addBtn , &QPushButton::clicked , this , &AddTable::addRow) ;
    QObject::connect(addBtn , &QPushButton::clicked , this , &AddTable::isAllValid) ; // new added
    QObject::connect(cancelBtn , &QPushButton::clicked , this , &QDialog::reject) ;
    QObject::connect(saveBtn , &QPushButton::clicked , this , &AddTable::onSaveClicked) ; // try to save

    // connect save button to save progrecc
    // connect to cancel

    validate = new QLabel(this) ;
    validate->setStyleSheet("color : red") ;

    btns->addWidget(saveBtn) ;
    btns->addWidget(cancelBtn) ;


    mainLayout->addWidget(addBtn) ;
    mainLayout->addWidget(validate) ;
    mainLayout->addLayout(btns) ;
    qDebug()<< "add button executed" ;
}

void AddTable::mainFieldInit()
{
    table = new QTableWidget(this) ;

    table->setColumnCount(4) ;

    table->setColumnWidth(0 , 200) ;
    table->setColumnWidth(1 , 100) ;
    table->setColumnWidth(2 , 80) ;
    table->setColumnWidth(3 , 100) ;

    table->horizontalHeader()->setSectionResizeMode(0 , QHeaderView::Stretch) ;
    table->horizontalHeader()->setSectionResizeMode(1 , QHeaderView::Fixed) ;
    table->horizontalHeader()->setSectionResizeMode(2 , QHeaderView::Fixed) ;
    table->horizontalHeader()->setSectionResizeMode(3 , QHeaderView::Fixed) ;


    QStringList header ;
    header << "column name" <<  "column type"  << "is primery" << "remove";
    table->setHorizontalHeaderLabels(header) ;

    mainLayout->addWidget(table) ;
}

void AddTable::addRow()
{
    // we never this is independ on number of row , this is set number for each button with sum of all button
    long long ID = numAllRow++ ; // why Qt never accept class member as captured ?
    numRow++; // adding number of row
    table->setRowCount(numRow) ;

    pushBack(ID) ;

    QLineEdit * colName = new QLineEdit(this) ;
    QComboBox * colType = new QComboBox(this) ;
    QCheckBox * isColPK = new QCheckBox(this) ;
    QPushButton * removeBtn = new QPushButton("remove" , this) ;

    colType->addItems({"TEXT" , "INTEGER"}) ;
    colName->setPlaceholderText("Enter name of Column (can not be empty)") ;

    QWidget *items[4] = {colName , colType , isColPK , removeBtn} ;

    for(int i = 0 ; i < numCol ; i++)
        table->setCellWidget(numRow - 1 , i , items[i]) ;

    QObject::connect(removeBtn , &QPushButton::clicked ,  this , [this , ID](){this->removeRow(ID) ; }) ;
    QObject::connect(removeBtn , &QPushButton::clicked ,  this ,&AddTable::isAllValid) ;
    qDebug()<<"add row executed" << "ID : " << ID << " row " << numRow;
}

void AddTable::removeRow(int ID)
{
    table->removeRow(this->pop(ID)) ;
    numRow--;
}

int AddTable::pop(int ID)
{
    std::forward_list<int>::iterator it = code.before_begin() ;

    int counter = -1 ;

    while(std::next(it) != code.end()){
        counter ++ ;
        if(*std::next(it) == ID){
            code.erase_after(it) ;
            return counter ;
        }
        it++ ; // move forward
    }
    return -1 ; // not found
}

void AddTable::pushBack(int val)
{
    if(code.empty()){
        qDebug()<< "try to add front of code " ;
        code.push_front(val) ;
    }
    else{
        qDebug() << "try to add end of code " ;
        std::forward_list<int>::iterator it = code.begin() ;
        while(std::next(it) != code.end())
            it++ ;
        code.insert_after(it , val) ;
    }
}

QString AddTable::extractNames()
{
    for(int i = 0 ; i < numRow ; i++){
        QString name = this->extractLine(i)->text() ;
        int ListSize = tableData.names.size() ;
        qDebug() << "extraced name : " << name ;
        for(int j = 0 ; j < ListSize ; j++){
            if(tableData.names[j] == name)
            {
                tableData.names.clear() ;
                return name ; // this name has selected before
            }
        }
        // else
        this->tableData.names.append(name) ;
    }
    tableData.tableName = this->TableName->text() ;
    return QString() ; // means all name selected one time !
}

void AddTable::extractInfo()
{
    for(int i = 0 ; i < numRow ; i ++)
    {
        QWidget * type = table->cellWidget(i , 1) ; // type combo box
        QWidget * isPk = table->cellWidget(i , 2) ; // pk check box
        if(type == nullptr or isPk == nullptr) throw std::runtime_error("widget in table does not exit or deleted") ;

        QComboBox *box = qobject_cast<QComboBox*>(type) ;
        QCheckBox *pk = qobject_cast<QCheckBox*>(isPk) ;

        tableData.types.append(box->currentIndex()) ; // read all data in table !
        tableData.Pk.append(pk->isChecked()) ; // real all data in table ;
    }
}


//in development
bool AddTable::isAllValid()
{
    bool collector = false ;
    // first check table name exit aand true :
    collector = this->onTextChanged() ;

    if(not this->onTextChanged()){
        validate->setText("table name is invalid") ;
        return false  ;
    }
    if(numRow == 0){
        validate->setText("We need at least one row to make a new table") ;
        return false ;
    }

    for(int i = 0 ; i < numRow ; i++){
        if(extractLine(i)->text().size() == 0){
            validate->setText("All rows must have a name") ;
            return false ;
        }
    }

    QString name = this->extractNames() ;
    if(not name.isEmpty()) // if this not empty !
    {
        validate->setText("we have more that once of (" + name + ")") ;
        return false ;
    }
    return collector ;
}

bool AddTable::onTextChanged()
{
    if(TableName->text().size() == 0)
    {
        smallText->setText("table name can not be empty") ;
        smallText->setStyleSheet("color : yellow") ;
    }
    else
    {
        int index = alltableNames.indexOf(TableName->text()) ;
        if(index == -1){
            smallText->setText("name is valid") ;
            smallText->setStyleSheet("color : green") ;
            return true ;
        }
        else
        {smallText->setText("this table is exist") ;
            smallText->setStyleSheet("color : red") ;
        }
    }
    return false ;
}

void AddTable::onSaveClicked()
{
    if(isAllValid()){
        this->validate->setText("Saving...") ;
        this->validate->setStyleSheet("color : green") ;
        this->extractInfo() ; // extract all other info !
        emit dataReady(tableData) ;
        this->accept();
    }
}

QLineEdit *AddTable::extractLine(int row)
{

        QWidget * item = table->cellWidget(row , 0) ;
        if(item != nullptr)
            return qobject_cast<QLineEdit*>(item) ;
        return nullptr ; // we have a problem !
};

