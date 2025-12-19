#ifndef STARTPAGE_H
#define STARTPAGE_H

#include "datacapsul.h"

#include <QDialog>
#include <QLabel>

namespace Ui {
class StartPage;
}

class QMainWindow ;
class QTableWidget ;

enum StartPageResult{OpenSelected = 1000 , Continue = 1001} ;

class StartPage : public QDialog
{
    Q_OBJECT

public:
    StartPage(QWidget *parent = nullptr );
    ~StartPage();

    // action controll
    void updateRow() ;
    void setupui() ;

    // data control function
    void setHistory() ;
    void updateHistory() ;
    void updateTable() ;
    QString getSelectedAddress() ;
    // main control
    void setFont() ;

public slots :
    void clearHistory() ;

private slots:
    void on_select_btn_clicked();
    void on_cancle_btn_clicked();
    void on_without_btn_clicked();
    void getHelp() ;

private:
    Ui::StartPage *ui;
    historyData history ;
    QTableWidget *table ;
    QLabel *emptyLable ;

    // fonts
    QFont UIfont ;


} ;



#endif // STARTPAGE_H
