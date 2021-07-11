#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>
#include <string>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QTcpSocket *tcpClient;
    QFile *localFile;
    QString fileName;  //文件名

    QByteArray outBlock;  //分次传
    qint64 loadSize;  //每次发送数据的大小
    qint64 byteToWrite;  //剩余数据大小
    qint64 totalSize;  //文件总大小

    QString ipaddress;
    void getID(QString ip);

private slots:
    void send();  //传送文件头信息
    void goOnSend(qint64);  //传送文件内容
    void on_openPushButton_clicked();
    void on_sendPushButton_clicked();
 //   void on_connect_clicked();
    void on_pushButton_clicked();
};

#endif // WIDGET_H
