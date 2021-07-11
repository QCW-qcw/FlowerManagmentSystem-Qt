#ifndef UIDEMO18_H
#define UIDEMO18_H

#include <QWidget>
#include "registerwindow.h"
#include"mainwindow.h"
#include"frmlunarcalendarwidget.h"
#include"selectwidget.h"
#include"flowershow.h"
#include"sqldataread.h"
#include "browser.h"
#include "browserwindow.h"
#include "tabwidget.h"
#include"whetherwindow.h"
#include"global.h"
class QToolButton;


typedef struct{
    int userType;
    QString userID;
    QString password;
    QString userName;
    QString ip;
}UserInfo;

namespace Ui {
class UIDemo18;
}

class UIDemo18 : public QWidget
{
    Q_OBJECT

public:
    explicit UIDemo18(QWidget *parent = 0);
    ~UIDemo18();
    int index;
    int indexofCombobox;
    RegisterWindow re;
    UserInfo user;
    MainWindow  m1;
    frmLunarCalendarWidget f1;
    selectWidget s1;
    sqldataread sqlfenxi;
    Browser browser;
       WhetherWindow tianqi;


    QString flowerName;
    QString plantTime;
    QString company;
    QString contactPerson;
    QString contactNum;
    int quantity;
    float costperPlant;

signals:
    void quit_Signal();

private:
    Ui::UIDemo18 *ui;
    QList<QToolButton *> btns;
    flowershow fshow;

private slots:
    void initForm();
    void initNav();
//    void buttonClicked();
     void on_whether_clicked();


private slots:
    void on_btnMsg_clicked();
    void on_btnReturn_clicked();
    void btn_Product_Clicked_slots();
    void btn_Info_Clicked_slots();
    void btn_Research_Clicked_slots();
    void btn_Map_Clicked_slots();
    void btn_Analysis_Clicked_slots();
    void btn_Settings_Clicked_slots();
    void on_btn_AddAcount_clicked();
    void on_help_clicked();
    void on_rili_clicked();
    void on_btnQuit_clicked();
    void on_btn_AddFlower_clicked();
    void on_btn_cleartext_clicked();
//    void on_pushButton_ip_clicked();
    void on_pushButton_clicked();
    void on_pushButton_map_clicked();
    void userinfo();
};

#endif // UIDEMO18_H
