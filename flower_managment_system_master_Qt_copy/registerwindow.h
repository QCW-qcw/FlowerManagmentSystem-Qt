#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include <QDialog>
#include <QtSql>

namespace Ui {
    class RegisterWindow;
}

class RegisterWindow:public QDialog
{
    Q_OBJECT

public:
    RegisterWindow(QWidget *parent = 0);
    ~RegisterWindow();


public slots:
    void Confirm_slots();
    void ResetBtn_slots();


private:
    Ui::RegisterWindow *ui;

};

#endif // REGISTERWINDOW_H
