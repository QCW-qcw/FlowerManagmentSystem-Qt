#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QDialog>
#include <QSqlQuery>
#include "uidemo18.h"


namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

    UIDemo18 u;

public slots:
   void btn_Clear_slots();
   void btn_Login_slots();
   void Receive_slots();



public:
//   MainWindow m;
//   QString ID;


private:
    Ui::LoginWindow *ui;
private:
    QSqlQuery query;
};

#endif // DIALOG_
