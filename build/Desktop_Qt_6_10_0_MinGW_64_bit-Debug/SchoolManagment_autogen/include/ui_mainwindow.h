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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionnew;
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionUIFont;
    QAction *actionclear_all;
    QAction *actionInfo;
    QAction *actionAbout;
    QAction *actionShow_table;
    QAction *actionShow_ROWID;
    QAction *actionTable_font_edit;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionGet_backup;
    QAction *actionreset_UI_font;
    QAction *actionReset_Table_font;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *OpenDataBase;
    QPushButton *closeDataBase;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *renamTable;
    QPushButton *create;
    QPushButton *dropTable;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *show_table;
    QPushButton *pushButton;
    QComboBox *select_table;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *insert_table;
    QPushButton *edit_cell;
    QPushButton *remove;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *ColName;
    QComboBox *operation_tags;
    QLineEdit *key;
    QPushButton *searchBox;
    QTableView *tableView;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSlider *zoomSlider;
    QLabel *index;
    QLabel *zoomPercent;
    QLabel *tableName;
    QLabel *dataBaseName;
    QLabel *label_3;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionnew = new QAction(MainWindow);
        actionnew->setObjectName("actionnew");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));
        actionnew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
        actionOpen->setIcon(icon1);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        actionExit->setIcon(icon2);
        actionUIFont = new QAction(MainWindow);
        actionUIFont->setObjectName("actionUIFont");
        actionclear_all = new QAction(MainWindow);
        actionclear_all->setObjectName("actionclear_all");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::EditClear));
        actionclear_all->setIcon(icon3);
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName("actionInfo");
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout));
        actionInfo->setIcon(icon4);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionShow_table = new QAction(MainWindow);
        actionShow_table->setObjectName("actionShow_table");
        actionShow_ROWID = new QAction(MainWindow);
        actionShow_ROWID->setObjectName("actionShow_ROWID");
        actionTable_font_edit = new QAction(MainWindow);
        actionTable_font_edit->setObjectName("actionTable_font_edit");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName("actionSave_as");
        actionGet_backup = new QAction(MainWindow);
        actionGet_backup->setObjectName("actionGet_backup");
        actionreset_UI_font = new QAction(MainWindow);
        actionreset_UI_font->setObjectName("actionreset_UI_font");
        actionReset_Table_font = new QAction(MainWindow);
        actionReset_Table_font->setObjectName("actionReset_Table_font");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 0, 5, 2);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 10, 0, 10);
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName("groupBox_5");
        horizontalLayout_3 = new QHBoxLayout(groupBox_5);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        OpenDataBase = new QPushButton(groupBox_5);
        OpenDataBase->setObjectName("OpenDataBase");

        horizontalLayout_3->addWidget(OpenDataBase);

        closeDataBase = new QPushButton(groupBox_5);
        closeDataBase->setObjectName("closeDataBase");

        horizontalLayout_3->addWidget(closeDataBase);


        gridLayout->addWidget(groupBox_5, 0, 3, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        renamTable = new QPushButton(groupBox);
        renamTable->setObjectName("renamTable");

        horizontalLayout_2->addWidget(renamTable);

        create = new QPushButton(groupBox);
        create->setObjectName("create");

        horizontalLayout_2->addWidget(create);

        dropTable = new QPushButton(groupBox);
        dropTable->setObjectName("dropTable");

        horizontalLayout_2->addWidget(dropTable);


        gridLayout->addWidget(groupBox, 0, 4, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMaximumSize(QSize(250, 16777215));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        show_table = new QPushButton(groupBox_2);
        show_table->setObjectName("show_table");

        verticalLayout_3->addWidget(show_table);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName("pushButton");

        verticalLayout_3->addWidget(pushButton);

        select_table = new QComboBox(groupBox_2);
        select_table->setObjectName("select_table");

        verticalLayout_3->addWidget(select_table);


        gridLayout->addWidget(groupBox_2, 0, 0, 2, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setMaximumSize(QSize(300, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(9, -1, -1, -1);
        insert_table = new QPushButton(groupBox_3);
        insert_table->setObjectName("insert_table");

        verticalLayout_2->addWidget(insert_table);

        edit_cell = new QPushButton(groupBox_3);
        edit_cell->setObjectName("edit_cell");

        verticalLayout_2->addWidget(edit_cell);

        remove = new QPushButton(groupBox_3);
        remove->setObjectName("remove");

        verticalLayout_2->addWidget(remove);


        gridLayout->addWidget(groupBox_3, 0, 1, 2, 1);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        horizontalLayout = new QHBoxLayout(groupBox_4);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox_4);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        ColName = new QComboBox(groupBox_4);
        ColName->setObjectName("ColName");

        horizontalLayout->addWidget(ColName);

        operation_tags = new QComboBox(groupBox_4);
        operation_tags->setObjectName("operation_tags");

        horizontalLayout->addWidget(operation_tags);

        key = new QLineEdit(groupBox_4);
        key->setObjectName("key");

        horizontalLayout->addWidget(key);

        searchBox = new QPushButton(groupBox_4);
        searchBox->setObjectName("searchBox");

        horizontalLayout->addWidget(searchBox);


        gridLayout->addWidget(groupBox_4, 1, 3, 1, 2);


        verticalLayout->addLayout(gridLayout);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 5, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        zoomSlider = new QSlider(centralwidget);
        zoomSlider->setObjectName("zoomSlider");
        zoomSlider->setMaximumSize(QSize(200, 16777215));
        zoomSlider->setMinimum(50);
        zoomSlider->setMaximum(200);
        zoomSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(zoomSlider, 0, 6, 1, 1);

        index = new QLabel(centralwidget);
        index->setObjectName("index");

        gridLayout_2->addWidget(index, 0, 4, 1, 1);

        zoomPercent = new QLabel(centralwidget);
        zoomPercent->setObjectName("zoomPercent");
        zoomPercent->setMaximumSize(QSize(40, 16777215));

        gridLayout_2->addWidget(zoomPercent, 0, 7, 1, 1);

        tableName = new QLabel(centralwidget);
        tableName->setObjectName("tableName");

        gridLayout_2->addWidget(tableName, 0, 2, 1, 1);

        dataBaseName = new QLabel(centralwidget);
        dataBaseName->setObjectName("dataBaseName");

        gridLayout_2->addWidget(dataBaseName, 0, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

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
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionnew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionGet_backup);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionUIFont);
        menuEdit->addAction(actionTable_font_edit);
        menuEdit->addSeparator();
        menuEdit->addAction(actionreset_UI_font);
        menuEdit->addAction(actionReset_Table_font);
        menuEdit->addSeparator();
        menuEdit->addAction(actionclear_all);
        menuHelp->addAction(actionInfo);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionnew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionUIFont->setText(QCoreApplication::translate("MainWindow", "UI font edit", nullptr));
        actionclear_all->setText(QCoreApplication::translate("MainWindow", "clear all", nullptr));
        actionInfo->setText(QCoreApplication::translate("MainWindow", "Info", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionShow_table->setText(QCoreApplication::translate("MainWindow", "Show table", nullptr));
        actionShow_ROWID->setText(QCoreApplication::translate("MainWindow", "\342\234\223 Show ROWID", nullptr));
        actionTable_font_edit->setText(QCoreApplication::translate("MainWindow", "Table font edit", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as", nullptr));
        actionGet_backup->setText(QCoreApplication::translate("MainWindow", "Get backup", nullptr));
        actionreset_UI_font->setText(QCoreApplication::translate("MainWindow", "reset UI font", nullptr));
        actionReset_Table_font->setText(QCoreApplication::translate("MainWindow", "Reset Table font", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Data Base", nullptr));
        OpenDataBase->setText(QCoreApplication::translate("MainWindow", "\360\237\223\202Open Data Base", nullptr));
        closeDataBase->setText(QCoreApplication::translate("MainWindow", "\342\234\226Close Data Base", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Row operations", nullptr));
        renamTable->setText(QCoreApplication::translate("MainWindow", "\342\234\216 Rename", nullptr));
        create->setText(QCoreApplication::translate("MainWindow", "\357\274\213 Create", nullptr));
        dropTable->setText(QCoreApplication::translate("MainWindow", "\342\234\226 Delete Table", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Selector", nullptr));
        show_table->setText(QCoreApplication::translate("MainWindow", "\342\237\262 Reset", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "show RoID", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Edit Table", nullptr));
        insert_table->setText(QCoreApplication::translate("MainWindow", "\342\206\247 Insert", nullptr));
        edit_cell->setText(QCoreApplication::translate("MainWindow", "\342\234\216 Edit Cell", nullptr));
        remove->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221 Remove ", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Search", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Find where : ", nullptr));
        searchBox->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Search", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "::", nullptr));
        index->setText(QCoreApplication::translate("MainWindow", "No index selected", nullptr));
        zoomPercent->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tableName->setText(QCoreApplication::translate("MainWindow", "No table is open", nullptr));
        dataBaseName->setText(QCoreApplication::translate("MainWindow", "No database is open", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "::", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
