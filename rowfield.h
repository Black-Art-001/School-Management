#ifndef ROWFIELD_H
#define ROWFIELD_H

#include <QWidget>

class QLineEdit ;
class QCheckBox ;
class QVBoxLayout ;
class QComboBox ;
class QPushButton ;

class rowField : public QWidget
{
    Q_OBJECT

public:
    rowField(QWidget * parent );
    QStringList getData() ;

public slots:
    QVBoxLayout * getElement() ;
    bool isFilled() ;

private :
    QWidget * parent ; // store parent address
    QLineEdit * line ; // read line as name
    QCheckBox * box ;  // add check box as primery key
    QVBoxLayout * field ; // layout to store data
    QComboBox * comboBox ; // select a type of data
    QPushButton * removeBtn ; // remove button
};

#endif // ROWFIELD_H
