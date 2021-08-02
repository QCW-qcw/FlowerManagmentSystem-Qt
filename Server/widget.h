#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myserver.h"
#include "debugonoroff.h"
#include "qnchatmessage.h"
class string;
class QEvent;
class Myserver;
class QListWidgetItem;
namespace Ui {
class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    /*重新实现事件过滤器函数*/
//    bool eventFilter(QObject *watched, QEvent *event);
    /*消息框*/
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    /*客户端主动断开连接信号*/
    void closeClientConnectSignal(int disconnectCommand);
    /*客户端被动断开连接信号*/
    void clientDiconnectSignal(int ID);

    /*发送消息信号*/
    void sendInfoWidgetSignal(QString info);
    /*服务器发送断开信号*/
    void clientAddressWidgetSignal(int deleteIndex);
public slots:
    /*添加客户端连接信息到界面中*/
//    void addClientIPTGUISlot(QString CIP,int CPort,int ID,int state);
    /*客户端主动断开连接*/
    void closeClientConnectSlot(QString clientIp, int clientPort, QDateTime current_date_time);

    /*显示日志信息*/
    void displayInfoTGUISlot(QString CIP,int CPort,int state,QDateTime current_time);
//    void deleteFileListItem();
//    /*List Widget双击事件槽函数*/
//    void doubleClickedItem();
    /*删除消息内容*/
    void deleteInfo();

    /*消息传输按钮槽函数*/
    void infoTranferButtonSlot();
    /*发送状态在GUI中显示*/
    void sendStateDisplaySlot(QString msg, QString info);
    /*发送消息在GUI中显示*/
    void sendInfoDisplaySlot(QString clientInfo, QString ip);
    /*服务器主动断开槽函数*/
    void clientAddressSlot(QString IP, int clientPort);
private slots:

    
    void on_rizhisave_clicked();

    void on_riziclear_clicked();

private:
    Ui::Widget *ui;
    /*断开客户端连接命令，1表示断开*/
    int closeCommand;

    /*传输的消息内容*/
    QString info;
    /*本机IP*/
    QString ipAddress;
    QVector<QString> IPOrder; //记录listWidget_2里的客户端IP地址
    int index = 0; //记录listWidget_2当前索引
    /*断开连接 服务器 0 客户端 1*/
    int closeFlag_previous = 1;
    int closeFlag_current = 1;
    Myserver *server;


};

#endif // WIDGET_H
