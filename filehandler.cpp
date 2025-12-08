#include "filehandler.h"



bool fileHandler::createBackup(const QString &originalFullPath)
{
    originalPath = originalFullPath ;

    QFileInfo fileInfo(originalPath) ;

    if(not fileInfo.exists())
    {
        qDebug() << "Original file doesn't exist";
        return false;
    }

    QString backupDir = fileInfo.path() + "/backups";
    QDir fileHandler(backupDir) ;

    if(not fileHandler.exists())
    {
        fileHandler.mkdir(backupDir);
    }

    QString date = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") ;

    QString backupName = fileInfo.baseName() + "_" + date + ".db";
    backupPath = backupDir + "/" + backupName;

    // Copy file
    if(QFile::copy(originalPath, backupPath)) {
        qDebug() << "Backup created:" << backupPath;
        return true;
    }

    return false;
}

QString fileHandler::getBackupPath()
{
    return backupPath;
}

bool fileHandler::restoreFromBackup()
{
    if(!QFile::exists(backupPath)) {
        qDebug() << "Backup doesn't exist";
        return false;
    }

    // Replace original with backup
    QFile::remove(originalPath);
    return QFile::rename(backupPath, originalPath);
}

void fileHandler::discardBackup()
{
    QFile::remove(backupPath);
}

bool fileHandler::saveAs(const QString &newFullPath)
{
     return QFile::copy(backupPath, newFullPath);
}


