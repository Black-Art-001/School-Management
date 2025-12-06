#include "rowfield.h"

#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>


rowField::rowField(QWidget *parent) : QWidget(parent)
{
    this->parent = parent ;


    line = new QLineEdit(this) ; // create
    line->setPlaceholderText("Column name (cannot be empty)") ;

    comboBox = new QComboBox(this) ;
    comboBox->addItems({"TEXT" , "INTEGER"}) ;

    box = new QCheckBox(this) ;

    field = new QVBoxLayout(this) ;

    removeBtn = new QPushButton(this) ;
    removeBtn->setText("remove line") ;

    field->addWidget(line) ;
    field->addWidget(comboBox) ;
    field->addWidget(box) ;
    field->addWidget(removeBtn) ;

    QObject::connect(removeBtn , &QPushButton::clicked , this , &rowField::deleteLater) ;
}

QStringList rowField::getData()
{
    QStringList data ;
    data.append(line->text()) ;
    data.append(comboBox->currentIndex() == 0 ? "TEXT" : "INTEGER") ;
    data.append(box->isChecked() ? "pk" : "NULL") ;

    return data ;
}

QVBoxLayout *rowField::getElement()
{
    return field ;
}

bool rowField::isFilled()
{
    if(line->text().size() > 0)
        return true ;
    return false ;
}
