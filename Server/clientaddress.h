#ifndef CLIENTADDRESS_H
#define CLIENTADDRESS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
class clientAddress : public QWidget
{
    Q_OBJECT
public:
//    explicit clientAddress(QWidget *parent = nullptr);
    clientAddress(QString IP, int Port);

    int clientAddressIndex = 0; //保存该clientAddress的索引
    QLabel *isloadLabel;
    QString clientIP;
    int clientPort;

signals:
    void clientAddressSignal(QString IP, int clientPort);
};

#endif // CLIENTADDRESS_H
