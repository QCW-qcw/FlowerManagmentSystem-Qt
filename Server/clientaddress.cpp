#include "clientaddress.h"

clientAddress::clientAddress(QString IP, int Port)
{
    clientIP = IP;
    clientPort = Port;
    QLabel *clientImg = new QLabel(this);
    QPixmap pixmap(":/img/child.png");
    QPixmap scaledPixmap = pixmap.scaled(QSize(32,32), Qt::KeepAspectRatio);
    clientImg->setPixmap(scaledPixmap);
    clientImg->move(9,9);
    QLabel *clientIPLocation = new QLabel(this);
    clientIPLocation->setText("IP : " + IP);
    clientIPLocation->move(50,15);
    QLabel *clientPortLocation = new QLabel(this);
    clientPortLocation->setText("Port : " + QString::number(Port));
    clientPortLocation->move(210,15);
    QPushButton *disconnectionButton = new QPushButton(this);
    disconnectionButton->setText("断开连接");
    disconnectionButton->setFixedWidth(140);
    disconnectionButton->move(310,9);
    connect(disconnectionButton, &QPushButton::clicked, [=](){
        emit clientAddressSignal(IP, clientPort);
    });


}
