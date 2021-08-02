#include "mythread.h"
#include <QHostAddress>
#include <QMessageBox>
#include "debugonoroff.h"
#include "protocolcommand.h"
Mythread::Mythread(int socketDes,int ID,QObject *parent):
    QThread(parent), socketDescriptor(socketDes)
{
    clientID = ID;
    socketDescriptor = socketDes;
}

void Mythread::run()
{
    /*保存客户端IP地址*/
    QString clientIP;
    /*保存客户端状态*/
    int clientState;
    /*创建套接字对象*/
    Mysocket *socket = new Mysocket(socketDescriptor,clientID,0);
    /*设置服务器监听到来的客户端的套接字描述符*/
    if(!socket->setSocketDescriptor(socketDescriptor))
        return;

    QObject::connect(socket,&Mysocket::disconnected,this,&Mythread::closeClientConnectSlot);
    QObject::connect(socket,&Mysocket::sendStateDisplaySignal,this,&Mythread::sendStateDisplaySlot);
    QObject::connect(socket,&Mysocket::sendInfoDisplaySignal,this,&Mythread::sendInfoDisplaySlot);
    QObject::connect(this,&Mythread::sendInfoSignal,socket,&Mysocket::sendMSG);
    QObject::connect(this,&Mythread::clientDisconnectSignal,socket,&Mysocket::clientDisconnectSlot);
    /*获得客户端的IP地址*/
    clientIP = socket->peerAddress().toString();
    /*获得客户端的端口号*/
    clientPort = socket->peerPort();
    clientState = socket->state();

    if(!clientIP.isEmpty())
    {
        /*只保留32位的点分十进制IP值*/
        clientIP = clientIP.right(clientIP.length()-7);
        clientIp = clientIP;
        current_date_time = QDateTime::currentDateTime();
        /*回传客户端IP地址和ID到GUI显示信号*/
        emit addClientIPToGUISignal(clientIP,clientPort,clientID,clientState);
        emit displayInfoToGUISignal(clientIP,clientPort,clientState,current_date_time);
    }
    else
    {
        qDebug()<< "Get client IP failed!";
    }

    exec();
}

void Mythread::closeClientConnectSlot()
{
    /*向GUI发射套接字断开连接信号更新界面*/
    current_date_time = QDateTime::currentDateTime();
    emit closeClientConnectSignal(clientIp, clientPort, current_date_time);
}

void Mythread::clientDisconnectSlot()
{
    /*关闭线程*/
//    this->quit();
    emit clientDisconnectSignal();
}

void Mythread::sendStateDisplaySlot(QString msg, QString info)
{
    emit sendStateDisplaySignal(msg, info);
}

void Mythread::sendInfoDisplaySlot(QString clientInfo, QString ip)
{
    emit sendInfoDisplaySignal(clientInfo, ip);
}


void Mythread::sendInfoSlot(QString info)
{
    emit sendInfoSignal(info);
}
