#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QFile>
#include <QString>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QString getIP() ;
private:
    Ui::Widget *ui;

    QTcpServer *server;
    QTcpSocket *receivedSocket;
    QFile *newFile;

    QByteArray inBlock;
    QString fileName;
    qint64 totalSize;  //总共需要发送的文件大小（文件内容&文件名信息）
    qint64 byteReceived;  //已经发送的大小

private slots:
    void acceptConnection();
    void readClient();
    void on_pushButton_clicked();
};

#endif // WIDGET_H
