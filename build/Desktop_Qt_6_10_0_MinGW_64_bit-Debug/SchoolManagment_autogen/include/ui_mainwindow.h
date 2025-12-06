/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionnew;
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionFont_edit;
    QAction *actionclear_all;
    QAction *actionInfo;
    QAction *actionAbout;
    QAction *actionShow_table;
    QAction *actionShow_ROWID;
    QWidget *centralwidget;
    QTableView *tableView;
    QPushButton *show_table;
    QPushButton *insert_table;
    QPushButton *remove;
    QPushButton *edit_cell;
    QComboBox *select_table;
    QPushButton *pushButton;
    QPushButton *create;
    QPushButton *dropTable;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionnew = new QAction(MainWindow);
        actionnew->setObjectName("actionnew");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
        actionOpen->setIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionFont_edit = new QAction(MainWindow);
        actionFont_edit->setObjectName("actionFont_edit");
        actionclear_all = new QAction(MainWindow);
        actionclear_all->setObjectName("actionclear_all");
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName("actionInfo");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionShow_table = new QAction(MainWindow);
        actionShow_table->setObjectName("actionShow_table");
        actionShow_ROWID = new QAction(MainWindow);
        actionShow_ROWID->setObjectName("actionShow_ROWID");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(10, 40, 651, 411));
        show_table = new QPushButton(centralwidget);
        show_table->setObjectName("show_table");
        show_table->setGeometry(QRect(10, 10, 80, 24));
        insert_table = new QPushButton(centralwidget);
        insert_table->setObjectName("insert_table");
        insert_table->setGeometry(QRect(90, 10, 80, 24));
        remove = new QPushButton(centralwidget);
        remove->setObjectName("remove");
        remove->setGeometry(QRect(170, 10, 80, 24));
        edit_cell = new QPushButton(centralwidget);
        edit_cell->setObjectName("edit_cell");
        edit_cell->setGeometry(QRect(250, 10, 80, 24));
        select_table = new QComboBox(centralwidget);
        select_table->setObjectName("select_table");
        select_table->setGeometry(QRect(580, 10, 81, 24));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(410, 10, 91, 24));
        create = new QPushButton(centralwidget);
        create->setObjectName("create");
        create->setGeometry(QRect(330, 10, 80, 24));
        dropTable = new QPushButton(centralwidget);
        dropTable->setObjectName("dropTable");
        dropTable->setGeometry(QRect(500, 10, 80, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionnew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionFont_edit);
        menuEdit->addAction(actionclear_all);
        menuHelp->addAction(actionInfo);
        menuHelp->addAction(actionAbout);
        menuView->addAction(actionShow_table);
        menuView->addAction(actionShow_ROWID);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionnew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionFont_edit->setText(QCoreApplication::translate("MainWindow", "Font edit", nullptr));
        actionclear_all->setText(QCoreApplication::translate("MainWindow", "clear all", nullptr));
        actionInfo->setText(QCoreApplication::translate("MainWindow", "Info", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionShow_table->setText(QCoreApplication::translate("MainWindow", "Show table", nullptr));
        actionShow_ROWID->setText(QCoreApplication::translate("MainWindow", "\342\234\223 Show ROWID", nullptr));
        show_table->setText(QCoreApplication::translate("MainWindow", "show", nullptr));
        insert_table->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        remove->setText(QCoreApplication::translate("MainWindow", "remove", nullptr));
        edit_cell->setText(QCoreApplication::translate("MainWindow", "update", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "debug", nullptr));
        create->setText(QCoreApplication::translate("MainWindow", "create", nullptr));
        dropTable->setText(QCoreApplication::translate("MainWindow", "Delete Table", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
