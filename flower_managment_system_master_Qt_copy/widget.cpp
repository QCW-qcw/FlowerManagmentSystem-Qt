#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QTextCodec>
#include <QFileDialog>
#include<QMessageBox>
#include"global.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("client file send");


    QTextCodec *codec = QTextCodec::codecForName("System");    //获取系统编码
    QTextCodec::setCodecForLocale(codec);
    ui->sendStatusLabel->setText(tr("未连接..."));
    ui->sendProgressBar->setValue(0);


    //tcpClient = new QTcpSocket(this);

    //  connect(tcpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(goOnSend(qint64)));
    /*
   tcpClient->connectToHost(QHostAddress(Global::ipaddress), 10000);
    if(!tcpClient->waitForConnected(30000))
         {
                   QMessageBox::warning(NULL, "Connection Error", "Please check the connection", QMessageBox::Yes );
                qDebug() << "Connection failed!";
                return;
         }else{
            qDebug() << "Connect successfully!";
              ui->sendStatusLabel->setText("已连接...");
}

*/
}

void Widget::send()  //发送文件头信息
{
    byteToWrite = localFile->size();  //剩余数据的大小
    totalSize = localFile->size();

    loadSize = 4*1024;  //每次发送数据的大小

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);

    out<<qint64(0)<<qint64(0)<<currentFileName;

    totalSize += outBlock.size();  //总大小为文件大小加上文件名等信息大小
    byteToWrite += outBlock.size();

    out.device()->seek(0);  //回到字节流起点来写好前面连个qint64，分别为总大小和文件名等信息大小
    out<<totalSize<<qint64(outBlock.size());

    tcpClient->write(outBlock);  //将读到的文件发送到套接字


    ui->sendProgressBar->setMaximum(totalSize);
    ui->sendProgressBar->setValue(totalSize - byteToWrite);
}

void Widget::goOnSend(qint64 numBytes)  //开始发送文件内容
{
    byteToWrite -= numBytes;  //剩余数据大小
    outBlock = localFile->read(qMin(byteToWrite, loadSize));
    tcpClient->write(outBlock);

    ui->sendProgressBar->setMaximum(totalSize);
    ui->sendProgressBar->setValue(totalSize - byteToWrite);

    if(byteToWrite == 0)  //发送完毕
        ui->sendStatusLabel->setText(tr("文件发送完毕!"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_openPushButton_clicked()  //打开文件并获取文件名（包括路径）
{
    ui->sendStatusLabel->setText(tr("正在打开文件..."));
    ui->sendProgressBar->setValue(0);  //非第一次发送

    loadSize = 0;
    byteToWrite = 0;
    totalSize = 0;
    outBlock.clear();

    fileName = QFileDialog::getOpenFileName(this);
    localFile = new QFile(fileName);
    localFile->open(QFile::ReadOnly);

    ui->sendStatusLabel->setText(tr("已打开文件 %1").arg(fileName));
    qDebug()<<"用户 " << Global::username<<"选择要发送的文件："<<fileName<<endl;

}

void Widget::on_sendPushButton_clicked()
{

    send();

    ui->sendStatusLabel->setText(tr("正在发送文件 %1").arg(fileName));
    qDebug()<<"用户 " << Global::username<<"发送文件 ："<<fileName<<endl;

}
/*
void Widget::on_connect_clicked()
{
    tcpClient->connectToHost(QHostAddress("192.168.43.218"), 10000);
    if(!tcpClient->waitForConnected(30000))
         {
//                    QMessageBox::warning(NULL, "Connection Error", "Please check the connection", QMessageBox::Yes );
                qDebug() << "Connection failed!";
                return;
         }else{
            qDebug() << "Connect successfully!";
              ui->sendStatusLabel->setText("已连接...");
}

}
*/

void Widget::on_pushButton_clicked()
{
    tcpClient = new QTcpSocket(this);

    connect(tcpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(goOnSend(qint64)));
    if(Global::ipaddress !=""){
        tcpClient->connectToHost(QHostAddress(Global::ipaddress), 10000);
        if(!tcpClient->waitForConnected(30000))
        {
            QMessageBox::warning(NULL, "Connection Error", "连接超时，请检查ip地址是否正确", QMessageBox::Yes );
            qDebug() << "Connection failed!";
            return;
        }else{
            qDebug() << "Connect successfully!";
            ui->sendStatusLabel->setText("已连接...");
            qDebug()<<"用户 " << Global::username<<"进行文件传输ip地址连接，连接ip为 ："<<Global::ipaddress<<endl;

        }

    }else{
        qDebug()<<"用户 " << Global::username<<"未设置文件传输ip地址连接失败"<<endl;

        QMessageBox::warning(this, "Error", "请到系统设置中设置文件传输ip地址", QMessageBox::Yes );

    }

}
