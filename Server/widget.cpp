#include "widget.h"
#include "clientaddress.h"
#include "ui_widget.h"
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QEvent>
#include <stdio.h>
#include <string.h>
//#include <sys/io.h>
#include <iostream>
#include <QNetworkInterface>
//#include "seekfile.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(tr("局域网消息传输服务器"));

    server = new Myserver(this);
    server->listen(QHostAddress::Any, 8888);
    closeCommand = 0;
    ui->textEdit->document()->setMaximumBlockCount(100);

    /*服务器端主动断开连接*/
    connect(this,&Widget::clientDiconnectSignal,server, &Myserver::clientDisconnectSlot);
    connect(ui->InfoPushButton,&QPushButton::clicked,this,&Widget::infoTranferButtonSlot);
    connect(ui->DelInfoPB,&QPushButton::clicked,this,&Widget::deleteInfo);
//    connect(ui->listWidget,&QAbstractItemView::doubleClicked,this,&Widget::doubleClickedItem);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::infoTranferButtonSlot()
{
    info = ui->textEdit_2->toPlainText();
    qDebug() << info;
    if(info.size() > 0)
    {
        QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
        qDebug()<<"addMessage" << info << time << ui->listWidget->count();
        dealMessageTime(time);
        QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget(), ipAddress);
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, info, time, QNChatMessage::User_Me);

        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
       emit sendInfoWidgetSignal(info);
    }
    else
    {
        ui->textEdit->append("无消息输入，传输消息无效！");
    }
}


void Widget::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(ui->listWidget->width()-10);
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void Widget::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(ui->listWidget->width()-10, 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}

void Widget::closeClientConnectSlot(QString clientIp, int clientPort, QDateTime current_date_time)
{
    /*判断是哪个客户端断开，并做相应的清除工作*/
    qDebug() << "#";
    for(int i = 0; i < IPOrder.size(); i++)
    {
        qDebug() << IPOrder.at(i) << " ";
    }
    qDebug() << index << " ";
    qDebug() << clientIp << " ";
    closeFlag_current *= -1;
    int deleteIndex = IPOrder.indexOf(clientIp);
//                    qDebug() << QString::number(deleteIndex);
    QListWidgetItem *item = ui->clientListWidget->takeItem(deleteIndex);
    delete item;
    IPOrder.remove(deleteIndex);
    index--;
//    /*判断连接的客户端数量，并根据连接的客户端信息进行界面更新*/
//    ui->textEdit->append(current_date + " —— IP: " + clientIp + " 断开连接");
    if(closeFlag_previous * closeFlag_current == -1)
    {
        QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
        /*判断连接的客户端数量，并根据连接的客户端信息进行界面更新*/
        ui->textEdit->append(current_date + " —— IP: " + clientIp + "  Port: " + QString::number(clientPort) + "  客户端断开连接");
    }
    server->socketNum--;
    closeFlag_previous = closeFlag_current;
}

void Widget::deleteInfo()
{
    info.clear();
    ui->textEdit_2->setText("");
}


void Widget::displayInfoTGUISlot(QString CIP,int CPort,int state,QDateTime current_time)
{
    QString current_date = current_time.toString("yyyy.MM.dd hh:mm:ss");
    /*判断连接的客户端数量，并根据连接的客户端信息进行界面更新*/
    if(state==QAbstractSocket::ConnectedState)
    {
        ui->textEdit->append(current_date + " —— IP: " + CIP + "  Port: " + QString::number(CPort) + "  客户端成功连接");
    }
    IPOrder.append(CIP);
    index++;
    QListWidgetItem * item = new QListWidgetItem(ui->clientListWidget);
    QSize size = item->sizeHint();
    item->setSizeHint(QSize(300, 50));
    ui->clientListWidget->addItem(item);
    clientAddress * client = new clientAddress(CIP, CPort);
    client->setParent(ui->clientListWidget);
    client->setSizeIncrement(size.width(), 56);
    ui->clientListWidget->setItemWidget(item, client);
    connect(client, &clientAddress::clientAddressSignal, this, &Widget::clientAddressSlot);
}

void Widget::clientAddressSlot(QString IP, int clientPort)
{
    int deleteIndex = IPOrder.indexOf(IP);
    closeFlag_current *= -1;
    QString current_date = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    /*判断连接的客户端数量，并根据连接的客户端信息进行界面更新*/
    ui->textEdit->append(current_date + " —— IP: " + IP + "  Port: " + QString::number(clientPort) + "  服务器断开连接");
    emit clientAddressWidgetSignal(deleteIndex);
}

void Widget::sendStateDisplaySlot(QString msg, QString info)
{
    if(msg == "服务器开始发送消息")
    {

////        else {
////            if(clientInfo != "") {
////                dealMessageTime(time);

////                QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
////                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
////                dealMessage(messageW, item, clientInfo, time, QNChatMessage::User_She);
////            }
////        }
//        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }
    else if(msg == "服务器发送消息成功")
    {
        /*暂停发送消息状态*/
        qDebug() << ui->listWidget->count();
        qDebug() << info;
        for(int i = ui->listWidget->count() - 1; i > 0; i--) {
            QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
            if(messageW->text() == info) {
                qDebug() << "7777777";
                messageW->setTextSuccess();
            }
        }

        QString current_date = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
        /*判断连接的客户端数量，并根据连接的客户端信息进行界面更新*/
        ui->textEdit->append(current_date + " —— " + msg + "——" + info) ;
    }
    else
    {
        QString current_date = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
        /*判断连接的客户端数量，并根据连接的客户端信息进行界面更新*/
        ui->textEdit->append(current_date + " —— " + msg+ "——" + info);
    }
}

void Widget::sendInfoDisplaySlot(QString clientInfo, QString ip)
{

    /*消息框*/
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    qDebug()<<"addMessage" << clientInfo << time << ui->listWidget->count();
    if(clientInfo != "") {
        dealMessageTime(time);

        QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget(), ip);
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, clientInfo, time, QNChatMessage::User_She);
    }

    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    /*判断连接的客户端数量，并根据连接的客户端信息进行界面更新*/
    QString current_date = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEdit->append(current_date + " —— " + "服务器接收消息成功" + "——" + clientInfo);
//    QMessageBox::about(NULL, "客户端消息", clientInfo);
}

void Widget::on_rizhisave_clicked()
{
   QString str =  ui->textEdit->toPlainText();
   QString current_date = QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh时mm分ss秒");
   QFile file("./ "+ current_date +" 日志.txt");
   file.open( QIODevice::ReadWrite | QIODevice::Append);
   QTextStream out(&file);
   out<<str;
   file.close();
    QMessageBox::information(NULL, "日志输出", "日志已成功保存");
}

void Widget::on_riziclear_clicked()
{
    ui->textEdit->clear();
}
