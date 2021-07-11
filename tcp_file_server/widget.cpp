#include "widget.h"
#include "ui_widget.h"
#include <QTextCodec>
#include<QNetworkInterface>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("server file receive");
    //ui->progressLabel->hide();
    ui->receivedProgressBar->setValue(0);
    ui->receivedStatusLabel->setText(tr("未连接..."));

    QTextCodec *codec = QTextCodec::codecForName("System");    //获取系统编码
    QTextCodec::setCodecForLocale(codec);

}

void Widget::acceptConnection()
{
    ui->receivedStatusLabel->setText(tr("已连接，正在准备接收文件!"));

    receivedSocket = server->nextPendingConnection();
    connect(receivedSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void Widget::readClient()
{
    ui->receivedStatusLabel->setText(tr("正在接收文件..."));

    if(byteReceived == 0)  //才刚开始接收数据，此数据为文件信息
    {
        ui->receivedProgressBar->setValue(0);

        QDataStream in(receivedSocket);
        in>>totalSize>>byteReceived>>fileName;
        fileName = "Files/" + fileName;
        newFile = new QFile(fileName);
        newFile->open(QFile::WriteOnly);
        qDebug()<<fileName;
    }
    else  //正式读取文件内容
    {
        inBlock = receivedSocket->readAll();

        byteReceived += inBlock.size();
        newFile->write(inBlock);
        newFile->flush();
    }

  //  ui->progressLabel->show();
    ui->receivedProgressBar->setMaximum(totalSize);
    ui->receivedProgressBar->setValue(byteReceived);

    if(byteReceived == totalSize)
    {
        ui->receivedStatusLabel->setText(tr("%1接收完成").arg(fileName));

        inBlock.clear();
        byteReceived = 0;
        totalSize = 0;
        newFile->close();
    }
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::getIP()  //获取ip地址
{
    QString strIpAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        // 获取第一个本主机的IPv4地址
        int nListSize = ipAddressesList.size();
        for (int i = 0; i < nListSize; ++i)
        {
               if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
                   strIpAddress = ipAddressesList.at(i).toString();
                   break;
               }
         }
         // 如果没有找到，则以本地IP地址为IP
         if (strIpAddress.isEmpty())
            strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
         return strIpAddress;
}


void Widget::on_pushButton_clicked()
{
    totalSize = 0;
    byteReceived = 0;
    QString ip = getIP();
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 10000);

    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    ui->receivedProgressBar->setValue(0);
    ui->receivedStatusLabel->setText(tr("开始监听..."));
    ui->pushButton->setEnabled(false);
}
