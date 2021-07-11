#include "loginwindow.h"
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include "registerwindow.h"
#include <QtSql>
#include "ui_loginwindow.h"
#include "uidemo18.h"
#include"global.h"

LoginWindow::LoginWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    //登录界面初始化
    ui->setupUi(this);
    setWindowTitle("用户登陆");
    this->setWindowFlags (this->windowFlags () | Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);
    ui->label->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->label_2->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->label_5->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->label_6->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    //设置光标默认位置
    ui->lineEdit_UserID->setFocus();

    //连接信号与槽
    connect(ui->btn_login, SIGNAL(clicked()), this, SLOT(btn_Login_slots()));
    connect(ui->btn_Clear,SIGNAL(clicked()),this,SLOT(btn_Clear_slots()));

    connect(&u,SIGNAL(quit_Signal()),this,SLOT(Receive_slots()));
    connect(ui->btn_login, SIGNAL(clicked()), &u, SLOT(userinfo()));

}

//登录按钮槽函数实现
void LoginWindow::btn_Login_slots()
{
    //查询数据库内是否有账号
    QSqlQuery query;
    query.prepare("select UserId and Password from " + Global::dataBaseName  + ".operator_info where UserId=:UserID and Password=:Password");
    query.bindValue(":UserID", ui->lineEdit_UserID->text());
    query.bindValue(":Password", ui->lineEdit_Password->text());
    query.exec();
    if(!query.next()){
        qDebug()<< ui->lineEdit_UserID->text()<<"登录失败"<<endl;
        QMessageBox::warning(NULL,"Error","账号或密码错误，请重试！");
    }
    else{
        //提取操作人员信息
        QSqlQuery query1;
        query1.prepare("select  * from " + Global::dataBaseName  + ".operator_info where UserId=:IDNum");
        query1.bindValue(":IDNum", ui->lineEdit_UserID->text());
        query1.exec();
        if(query1.next()){
            QSqlRecord rec1 = query1.record();
            rec1 = query1.record();
            int indexofO = rec1.indexOf("type");
            int indexof1 = rec1.indexOf("UserName");

            //操作人员初始化
            u.user.userID = ui->lineEdit_UserID->text();
            u.user.password = ui->lineEdit_Password->text();
            u.user.userType = query1.value(indexofO).toInt();
            u.user.userName = query1.value(indexof1).toString();
            Global::username = ui->lineEdit_UserID->text();
            Global::type = QString::number( u.user.userType);
            qDebug()<< "用户 "<<Global::username  <<"登录成功";
            this->close();
            u.show();

        }

    }
}

//清除按钮槽函数实现
void LoginWindow::btn_Clear_slots()
{
    ui->lineEdit_UserID->clear();
    ui->lineEdit_Password->clear();
}

//退出系统槽函数实现
void LoginWindow::Receive_slots()
{
    u.hide();
    this->show();

    ui->lineEdit_UserID->clear();
    ui->lineEdit_Password->clear();
    qDebug()<< "用户 "<<Global::username  <<"退出系统";
}

LoginWindow::~LoginWindow()
{

}
