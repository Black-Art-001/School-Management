#include "startpage.h"
#include "ui_startpage.h"
#include "SaveLoad.h"

#include <QTableWidget>
#include <QHeaderView>
#include <QFile>
#include <QPushButton>
#include <QList>
#include <QLineEdit>

#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>

StartPage::StartPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartPage)
{
    ui->setupUi(this);
    table = nullptr ;
    SaveLoad::loadFont(UIfont , UIFont) ;
    this->setupui() ;

    this->setHistory() ; // get history
    this->updateHistory() ; // check history

    this->setFont() ;
    this->updateTable() ; // if size lesser that 0 show empty massage

    QObject::connect(ui->clear_btn , &QPushButton::clicked , this , &StartPage::clearHistory) ; // clear all history
    QObject::connect(ui->help_btn , &QPushButton::clicked , this , &StartPage::getHelp) ;
}

StartPage::~StartPage()
{
    delete ui;
}

void StartPage::updateRow()
{
    if(not table)
        return ;
    table->setRowCount(history.historyPath.size()) ;
    for(int i = 0 ; i < history.historyPath.size() ; i++){
        table->setItem(i , 0 ,new QTableWidgetItem(history.historyPath[i])) ;
        table->setItem(i , 1 ,new QTableWidgetItem(history.historyDate[i])) ;
    }
}

void StartPage::setupui()
{
    qDebug() << "=== setupui() called ===";

    table = new QTableWidget(this) ;
    table->setColumnCount(2) ;

    table->setHorizontalHeaderLabels({"path" , "date"}) ;
    table->setSelectionMode(QTableWidget::SingleSelection) ;
    table->setSelectionBehavior(QTableWidget::SelectRows) ;

    table->horizontalHeader()->setSectionResizeMode(0 , QHeaderView::Stretch) ;
    table->horizontalHeader()->setSectionResizeMode(1 , QHeaderView::Fixed) ;

    table->setColumnWidth(1 , 150) ;
    table->setMinimumWidth(300) ;

    ui->tablePlace->addWidget(table) ;
    qDebug() << "Added table to stacked widget. Page 0";



    QWidget *emptyWidget = new QWidget();
    QVBoxLayout *emptyLayout = new QVBoxLayout(emptyWidget);
    QLabel *emptyLabel = new QLabel("📭 No recent files");
    emptyLabel->setAlignment(Qt::AlignCenter);
    emptyLabel->setStyleSheet("font-size: 16px; color: gray;");
    emptyLayout->addWidget(emptyLabel);

    qDebug() << "Added empty widget to stacked widget. Page 1";
    qDebug() << "Total pages in stacked widget:" << ui->tablePlace->count();

    ui->tablePlace->addWidget(emptyWidget) ;

    // DELETE existing pages FIRST
    while (ui->tablePlace->count() > 2) {
        QWidget* widget = ui->tablePlace->widget(0);
        ui->tablePlace->removeWidget(widget);
        delete widget;
    }

}


void StartPage::setHistory()
{
    history = SaveLoad::loadHistory() ;
    std::reverse(history.historyPath.begin() , history.historyPath.end()) ;
    std::reverse(history.historyDate.begin() , history.historyDate.end()) ;
    qDebug() << "=== setHistory called ===" ;
    qDebug() << ">> Reult is : " << history.historyPath << history.historyDate ;
}

void StartPage::updateHistory()
{
    qDebug() << "=== updateHistory called ===";
    for(int index =  history.historyPath.size() - 1 ; index >= 0 ; index--){
        if (not QFile::exists(history.historyPath[index])){
            qDebug() << "we delete : " << history.historyPath[index] ;
            history.historyPath.remove(index) ;
            history.historyDate.remove(index) ;
        }
    } 
}

void StartPage::updateTable()
{
    qDebug() << "=== updateTable called ===";
    qDebug() << "History size:" << history.historyPath.size();
    qDebug() << "Stacked widget has" << ui->tablePlace->count() << "pages";

    if(not history.historyPath.empty())
    {
        qDebug() << "Showing TABLE (page 0)";
        this->updateRow() ;
        ui->tablePlace->setCurrentIndex(0) ;
    }
    else {
        qDebug() << "Showing EMPTY MESSAGE (page 1)";
        ui->tablePlace->setCurrentIndex(1) ;
    }
    qDebug() << "Current page index:" << ui->tablePlace->currentIndex();
}

QString StartPage::getSelectedAddress()
{
    return history.historyPath[table->currentRow()] ;
}

void StartPage::setFont()
{
    QList <QWidget *> widgets = this->findChildren<QWidget*>() ;
    for(auto widget : widgets)
    {
        if(qobject_cast<QPushButton*>(widget))
            widget->setFont(UIfont) ;
        else if(qobject_cast<QLabel*>(widget))
            widget->setFont(UIfont) ;
        if(qobject_cast<QLineEdit*>(widget))
            widget->setFont(UIfont) ;
        if(qobject_cast<QTableWidget*>(widget))
            widget->setFont(UIfont) ;
        if(qobject_cast<QStackedWidget*>(widget))
            widget->setFont(UIfont) ;
    }
}

void StartPage::clearHistory()
{
    SaveLoad::cleatHistory() ;
    this->setHistory() ;
    this->updateTable() ; // for showing empty message !
}

void StartPage::on_select_btn_clicked()
{
    qDebug() << "select btn clicked" ;
    done(OpenSelected) ;
}


void StartPage::on_cancle_btn_clicked()
{
    this->reject() ;
}


void StartPage::on_without_btn_clicked()
{
    done(Continue) ;
}

void StartPage::getHelp()
{
    qDebug() << "=== get Help called ===" ;
    QString helpPath = QDir::currentPath() + "/help/help.html" ;
    qDebug() << ">> File path : " << helpPath ;

    QFileInfo file(helpPath) ;
    if(file.exists()){
        QDesktopServices::openUrl(QUrl::fromLocalFile(helpPath)) ;
    }
    else {
        QMessageBox::warning(this, "Help Not Found",
                             "Help file not found at:\n" + helpPath +
                                 "\n\nMake sure 'help' folder exists with index.html");

    }
}

