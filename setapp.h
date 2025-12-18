#ifndef SETAPP_H
#define SETAPP_H

#include <QMainWindow>

namespace Ui {
class setApp;
}

class setApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit setApp(QWidget *parent = nullptr);
    ~setApp();

private:
    Ui::setApp *ui;
};

#endif // SETAPP_H
