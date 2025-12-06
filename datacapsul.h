#ifndef DATACAPSUL_H
#define DATACAPSUL_H

#include<QObject>
#include <QString>
#include <QVector>

struct TableData{
    QString tableName ;
    QStringList names ;
    QVector<int> types ;
    QVector<bool> Pk ;
};

Q_DECLARE_METATYPE(TableData) // for passing in signals !

#endif // DATACAPSUL_H
