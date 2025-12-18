#ifndef SAVELOAD_H
#define SAVELOAD_H

#include <QFont>
#include <QSettings>
#include <QString>

#include "datacapsul.h"

#define UIFont "UIfont"
#define TableFonts "TableFont"
#define AppDirName "MySchool"
#define Font "Font"
#define History "History"


class SaveLoad
{
public:
    static void saveFont(QFont & font , QString group) ;
    static void loadFont(QFont & font , QString group) ;
    static void saveHistory(QString path) ;
    static historyData loadHistory() ; // return all history address
    static void cleatHistory(); // clear all last history !

};

#endif // SAVELOAD_H
