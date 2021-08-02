#include "mysocket.h"
#include <QDataStream>
#include "protocolcommand.h"
#include <QDir>
#include <QDirIterator>
Mysocket::Mysocket(int socket, int ID,QObject *parent)
    :QTcpSocket(parent), socketDescriptor(socket)
{
    socketID = ID;
    clearVariation();
    QObject::connect(this,&Mysocket::readyRead,this,&Mysocket::reveiveData);
}

Mysocket::~Mysocket()
{

}


void Mysocket::sendMSG(QString msg)
{
    emit sendStateDisplaySignal("服务器开始发送消息", msg);
    /*确保连接依然有效*/
    if(!isValid())
    {
        qDebug()<<"Already disconnected!";
        return;
    }

    qDebug() <<"要发送的消息是： "<< msg;

    /*发送命令内容*/
    write(msg.toUtf8(),(msg.toUtf8().length()+1));
    emit sendStateDisplaySignal("服务器发送消息成功", msg);


}

void Mysocket::reveiveData()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer =readAll();
    if(!buffer.isEmpty())
    {
        QString clientInfo = QString(buffer);
        qDebug()<<"接收的数据是 ： "<<clientInfo;
        QString ip = clientInfo.split("_")[0];
        QString mes = clientInfo.split("_")[1];
        emit sendInfoDisplaySignal(mes, ip);
        qDebug()<<"Receive info success!";

    }

}

void Mysocket::clientDisconnectSlot()
{
    this->disconnectFromHost();
    this->close();
    //    emit clientDisconnectSignal();
}

void Mysocket::clearVariation()
{
    transferData.totalBytes = 0;
    transferData.bytesReceived = 0;
    transferData.fileNameSize = 0;
    transferData.inOrOutBlock.resize(0);
    transferData.payloadSize = 1024 * 64; //每次发送64kb
    transferData.bytesWritten = 0;
    transferData.bytesToWrite = 0;
}

