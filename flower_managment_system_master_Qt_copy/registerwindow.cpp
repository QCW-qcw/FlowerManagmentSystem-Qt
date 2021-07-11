#include "registerwindow.h"
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QtSql>
#include "ui_registerwindow.h"
#include<global.h>
//#include "mainwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    //注册界面初始化
    setWindowTitle("用户注册");
    this->setWindowFlags (this->windowFlags () | Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);

    //下拉框初始化
    QStringList items;
    items.append(tr("管理员"));
    items.append(tr("用户"));
    ui->comboBox->addItems(items);
    ui->comboBox->setCurrentIndex(-1);

    //设置光标默认位置
    ui->lineEdit_ID->setFocus();

    connect(ui->btn_confirm,SIGNAL(clicked()),this,SLOT(Confirm_slots()));
    connect(ui->btn_reset,SIGNAL(clicked()),this,SLOT(ResetBtn_slots()));
}


void RegisterWindow::ResetBtn_slots()
{
    ui->lineEdit_ID->clear();
    ui->lineEdit_PWord->clear();
    ui->lineEdit_ReplyPWord->clear();
}

void RegisterWindow::Confirm_slots()
{

    QSqlQuery query;
    //判断输入信息是否为空
    if(ui->lineEdit_ID->text() == ""){
        QMessageBox::information(this,"Error","账号不能为空！",QMessageBox::Yes);
    }
    else if(ui->lineEdit_PWord->text() == "" || ui->lineEdit_ReplyPWord->text() == ""){
        QMessageBox::information(this,"Error","密码不能为空！",QMessageBox::Yes);
    }
    else if(ui->comboBox->currentText() == tr("")){
        QMessageBox::information(this,"Error","请选择操作人员类别",QMessageBox::Yes);
    }
    else{
        //判断两次输入密码是否一致
        if(ui->lineEdit_PWord->text() == ui->lineEdit_ReplyPWord->text()){
            query.prepare("select UserId from  "+Global::dataBaseName + ".operator_info where UserId=:UID");
            query.bindValue(":UID", ui->lineEdit_ID->text());
            query.exec();

            //判断账号是否注册
            if(query.next()){
                QMessageBox::warning(NULL,"Error","账号重复，请重试！ ");
            }
            else{
                query.prepare("insert into flowermanagment.operator_info(UserId,Password,type)"
                              "values(:UID,:PWord,:type)");
                query.bindValue(":UID", ui->lineEdit_ID->text());
                query.bindValue(":PWord",ui->lineEdit_PWord->text());
                query.bindValue(":type", ui->comboBox->currentIndex());
                query.exec();
                QMessageBox::information(NULL, "Success", "添加成功！", QMessageBox::Yes);

                ui->lineEdit_ID->clear();
                ui->lineEdit_PWord->clear();
                ui->lineEdit_ReplyPWord->clear();
                // ui->comboBox->clear();
                this->close();
            }
        }
        else{
            QMessageBox::warning(NULL,"Error","两次密码输入不一致，请重试！");
        }
    }
}

RegisterWindow::~RegisterWindow()
{

}


