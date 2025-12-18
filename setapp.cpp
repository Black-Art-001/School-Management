#include "setapp.h"
#include "ui_setapp.h"

setApp::setApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::setApp)
{
    ui->setupUi(this);
}

setApp::~setApp()
{
    delete ui;
}
