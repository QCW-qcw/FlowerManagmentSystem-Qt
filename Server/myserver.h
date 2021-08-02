#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QList>

#include "widget.h"
#include "mythread.h"
#include "debugonoroff.h"
#include "clientaddress.h"
class Widget;
class Mythread;
class Myserver : public QTcpServer
{
    Q_OBJECT
public:
    Myserver(QObject *parent);
    ~Myserver();
    /*存储建立链接的客户端套接字*/
    QList<int >socketList;
    /*存储线程*/
    QList<Mythread *>threadList;
    /*存储客户端IP地址*/
    QList<QString>socketIP;
    /*记录客户端数量*/
    int socketNum;
protected:
    void incomingConnection(qintptr socketDescriptor);
signals:
    /*客户端被动断开连接信号*/
    void clientDisconnectSignal();
public slots:
    /*客户端被动断开连接槽函数*/
    void clientDisconnectSlot(int ID);
private:
    Widget *widget;                 //指向GUI的指针
};

#endif // MYSERVER_H
