#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QDateTime>
#include "mysocket.h"
#include "debugonoroff.h"

class Mythread : public QThread
{
    Q_OBJECT
public:
    Mythread(int socketDes,int ID,QObject *parent);
protected:
    void run();
signals:
    /*添加客户端IP地址到GUI*/
    void addClientIPToGUISignal(QString CIP, int CPort, int ID, int state);
    /*客户端主动断开连接信号*/
    void closeClientConnectSignal(QString clientIp, int clientPort, QDateTime current_date_time);
    /*客户端被动断开连接*/
    void clientDisconnectSignal();

    /*发送消息信号*/
    void sendInfoSignal(QString info);
    /*显示日志信号*/
    void displayInfoToGUISignal(QString CIP,int CPort,int state,QDateTime current_time);
    /*发送状态显示到GUI*/
    void sendStateDisplaySignal(QString msg, QString info);
    /*发送消息显示到GUI*/
    void sendInfoDisplaySignal(QString clientInfo, QString ip);
public slots:
    /*客户端主动断开连接槽*/
    void closeClientConnectSlot();
    /*客户端被动断开连接槽函数*/
    void clientDisconnectSlot();

    /*发送消息槽函数*/
    void sendInfoSlot(QString info);
    /*发送状态显示到GUI槽函数*/
    void sendStateDisplaySlot(QString msg, QString info);
    /*发送消息显示到GUI槽函数*/
    void sendInfoDisplaySlot(QString clientInfo, QString ip);
private:
    Mysocket *socket;
    /*记录客户端数量*/
    int clientID;
    /*记录客户端IP*/
    QString clientIp;
    /*记录客户端端口号*/
    int clientPort;
    quintptr socketDescriptor;
    QDateTime current_date_time;

    struct rcvOrSendDataPack{
        /*共用部分*/
        QFile *localFile;           //存放本地文件
        qint64 totalBytes;          //存放总大小信息
        QString fileName;           //存放文件名
        QByteArray inOrOutBlock;    //数据缓冲区
        /*发送相关*/
        qint64 bytesWritten;        //已经发送数据大小
        qint64 bytesToWrite;        //剩余数据的大小
        qint64 payloadSize;         //每次发送数据的大小
        /*接收相关*/
        qint64 bytesReceived;       //已收到数据的大小
        qint64 fileNameSize;        //文件名的大小信息
        qint64 command;            //接收的命令
    };
    struct rcvOrSendDataPack transferData; //数据结构体
};

#endif // MYTHREAD_H
