/********************************************************************************
** Form generated from reading UI file 'startpage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTPAGE_H
#define UI_STARTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartPage
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *windowName;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *tablePlace;
    QWidget *page_5;
    QWidget *page_6;
    QVBoxLayout *verticalLayout;
    QPushButton *select_btn;
    QPushButton *clear_btn;
    QPushButton *help_btn;
    QPushButton *cancle_btn;
    QSpacerItem *verticalSpacer;
    QPushButton *without_btn;
    QLabel *appname;

    void setupUi(QDialog *StartPage)
    {
        if (StartPage->objectName().isEmpty())
            StartPage->setObjectName("StartPage");
        StartPage->resize(689, 477);
        verticalLayout_2 = new QVBoxLayout(StartPage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        windowName = new QLabel(StartPage);
        windowName->setObjectName("windowName");

        verticalLayout_2->addWidget(windowName);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        tablePlace = new QStackedWidget(StartPage);
        tablePlace->setObjectName("tablePlace");
        tablePlace->setFrameShape(QFrame::Shape::Box);
        tablePlace->setLineWidth(1);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        tablePlace->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        tablePlace->addWidget(page_6);

        horizontalLayout->addWidget(tablePlace);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        select_btn = new QPushButton(StartPage);
        select_btn->setObjectName("select_btn");
        select_btn->setMaximumSize(QSize(16777215, 50));

        verticalLayout->addWidget(select_btn);

        clear_btn = new QPushButton(StartPage);
        clear_btn->setObjectName("clear_btn");

        verticalLayout->addWidget(clear_btn);

        help_btn = new QPushButton(StartPage);
        help_btn->setObjectName("help_btn");

        verticalLayout->addWidget(help_btn);

        cancle_btn = new QPushButton(StartPage);
        cancle_btn->setObjectName("cancle_btn");
        cancle_btn->setMaximumSize(QSize(16777215, 50));

        verticalLayout->addWidget(cancle_btn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        without_btn = new QPushButton(StartPage);
        without_btn->setObjectName("without_btn");
        without_btn->setMaximumSize(QSize(16777215, 50));

        verticalLayout->addWidget(without_btn);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        appname = new QLabel(StartPage);
        appname->setObjectName("appname");

        verticalLayout_2->addWidget(appname);


        retranslateUi(StartPage);

        QMetaObject::connectSlotsByName(StartPage);
    } // setupUi

    void retranslateUi(QDialog *StartPage)
    {
        StartPage->setWindowTitle(QCoreApplication::translate("StartPage", "Dialog", nullptr));
        windowName->setText(QCoreApplication::translate("StartPage", "Get Started", nullptr));
        select_btn->setText(QCoreApplication::translate("StartPage", "Select File", nullptr));
        clear_btn->setText(QCoreApplication::translate("StartPage", "Clear HIstory", nullptr));
        help_btn->setText(QCoreApplication::translate("StartPage", "Get Help", nullptr));
        cancle_btn->setText(QCoreApplication::translate("StartPage", "Cancle", nullptr));
        without_btn->setText(QCoreApplication::translate("StartPage", "continue without dataBase", nullptr));
        appname->setText(QCoreApplication::translate("StartPage", "School Managment 2025", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartPage: public Ui_StartPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTPAGE_H
