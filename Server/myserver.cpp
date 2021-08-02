#include "myserver.h"

Myserver::Myserver(QObject *parent)
{
    socketNum = 0;
    /*获得当前widget对象*/
    widget = dynamic_cast<Widget *>(parent);
}

Myserver::~Myserver()
{

}

void Myserver::incomingConnection(qintptr socketDescriptor)
{
    /*添加连接的客户端到链表中*/
    socketList.append(socketDescriptor);
    /*每建立一个客户端请求客户端数量加一*/
    socketNum++;
    if(socketNum>3)
        socketNum = 1;

    /*创建一个线程用于执行与客户端的工作*/
    Mythread *thread = new Mythread(socketDescriptor,socketNum,0);
    threadList.append(thread);
    /*关联线程断开客户端连接信号和GUI更新界面槽函数*/
    connect(thread,&Mythread::closeClientConnectSignal,widget,&Widget::closeClientConnectSlot);
    /*添加客户端IP到GUI中进行显示*/
//    connect(thread,&Mythread::addClientIPToGUISignal,widget,&Widget::addClientIPTGUISlot);
    /*更改消息传输状态到GUI中进行显示*/
    connect(thread,&Mythread::sendStateDisplaySignal,widget,&Widget::sendStateDisplaySlot);
    /*添加客户端消息到GUI中进行显示*/
    connect(thread,&Mythread::sendInfoDisplaySignal,widget,&Widget::sendInfoDisplaySlot);

    /*发送消息信号发送至线程*/
    connect(widget,&Widget::sendInfoWidgetSignal,thread,&Mythread::sendInfoSlot);
    /*服务器端主动断开连接*/
//    connect(widget,&Widget::clientDiconnectSignal,this,&Myserver::clientDisconnectSlot);
    connect(widget,&Widget::clientAddressWidgetSignal,this,&Myserver::clientDisconnectSlot);
    /*启动线程*/
    thread->start();
    /*添加日志*/
    connect(thread,&Mythread::displayInfoToGUISignal,widget,&Widget::displayInfoTGUISlot);
}

void Myserver::clientDisconnectSlot(int ID)
{
    /*服务器端主动断开客户端的连接根据断开的客户端编号与其线程关联槽函数*/
//    qDebug() << "套接字";
//    qDebug() << ID;
//    for(int i = 0; i < threadList.size(); i++)
//    {
//        qDebug() << threadList.at(i);
//    }
    QMetaObject::Connection dis = QObject::connect(this,&Myserver::clientDisconnectSignal,
                     threadList[ID],&Mythread::clientDisconnectSlot);
    emit clientDisconnectSignal();
//    threadList[ID-1]->disconnect();
    /*取消信号槽*/
    disconnect(dis);
    /*从客户端套接字列表中移除套接字*/
    socketList.removeAt(ID);
    /*从线程列表中移除线程*/
    Mythread * deleteThread = threadList.takeAt(ID);
    /*关闭线程*/
    deleteThread->exit(0);
    deleteThread->wait();
//    qDebug() << socketList.size();
//    qDebug() << threadList.size();
//    qDebug() << "套接字now";
//    for(int i = 0; i < socketList.size(); i++)
//    {
//        qDebug() << socketList.at(i);
//    }
}
