#include "mainwindow.h"
#include "setupfont.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont ui_font , table_font ;
    setupFont font ;

    font.loadFont(ui_font , UIFont) ;
    font.loadFont(table_font , TableFont ) ;

    MainWindow w(nullptr , &ui_font , &table_font);
    w.show();
    return a.exec();
    font.saveFont(ui_font , UIFont) ;
    font.saveFont(table_font , TableFont) ; //
}
