#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QFile>
#include <QDir>
#include <QString>

class fileHandler
{

public:
    bool createBackup(const QString& originalFullPath) ;
    QString getBackupPath() ;


    void discardFile() ;
    QString getOriginalFileName() ;
    QString getCopyFileName() ;
    bool restoreFromBackup() ;
    void discardBackup() ;
    bool saveAs(const QString& newFullPath) ;

private :

    QString originalPath;
    QString backupPath;
};

#endif // FILEHANDLER_H
