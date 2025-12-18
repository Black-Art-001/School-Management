#include "SaveLoad.h"

#include <QDate>
#include <QFile>

void SaveLoad::saveFont(QFont &font, QString group)
{
    QSettings setting(AppDirName , Font) ;
    setting.beginGroup(group) ;
    setting.setValue("fontFamily" , font.family()) ;
    setting.setValue("fontSize" , font.pointSize()) ;
    setting.setValue("fontBold" , font.bold()) ;
    setting.setValue("fontItalic" , font.italic()) ;
    setting.endGroup() ;
    qDebug()<< "save font : " << font ;
}

void SaveLoad::loadFont(QFont &font, QString group)
{
    QSettings setting(AppDirName , Font) ;

    setting.beginGroup(group) ;
    font.setFamily(setting.value("fontFamily" , "Segoe UI").toString()) ;
    font.setPointSize(setting.value("fontSize" , 9).toInt()) ;
    font.setBold(setting.value("fontBold" , false).toBool()) ;
    font.setItalic(setting.value("fontItalic" , false).toBool()) ;
    setting.endGroup() ;

    qDebug()<< "load font : " << font  ;
}

void SaveLoad::saveHistory(QString path)
{

    if(path.isEmpty() or path == "/" or path == "\\")
        return  ;

    if(not QFile::exists(path)) // if file in save time exit store it
        return  ;

    qDebug() << "=== saveHistory called ===" ;
    // load number of
    QSettings setting(AppDirName , History) ;
    setting.beginGroup(History) ;

    historyData history ;
    history.historyDate = setting.value("Date").toStringList() ;
    history.historyPath = setting.value("Path").toStringList() ;

    // remove same path
    int index = history.historyPath.indexOf(path) ;
    if(index not_eq -1)
    {
        history.historyPath.remove(index) ;
        history.historyDate.remove(index) ;
    }
    // add file path

    history.historyPath.append(path) ;
    history.historyDate.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm")) ;

    // resize to 10
    while (history.historyPath.size() > 10){
        history.historyPath.removeAt(0) ; // remove old path
        history.historyDate.removeAt(0) ; // remove old Date
    }

    qDebug() << "files path : " << history.historyPath ;
    qDebug() << "files date : " << history.historyDate ;

    setting.setValue("Path" ,  history.historyPath) ;
    setting.setValue("Date" , history.historyDate) ;
    setting.endGroup() ;
}

historyData SaveLoad::loadHistory()
{
    qDebug() << "=== loadHistory called ===" ;
    historyData history ;
    QSettings setting(AppDirName , History) ;
    setting.beginGroup(History) ;
    history.historyPath = setting.value("Path").toStringList() ;
    history.historyDate = setting.value("Date").toStringList() ;
    qDebug() << "files path : " << history.historyPath ;
    qDebug() << "files date : " << history.historyDate ;
    return history ;
}

void SaveLoad::cleatHistory()
{
    QSettings setting(AppDirName , History) ;
    setting.beginGroup(History) ;
    setting.remove("Path");
    setting.remove("Date");
    setting.endGroup() ;
}



