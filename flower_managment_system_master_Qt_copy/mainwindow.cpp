#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QDateTime>
#include <QDesktopWidget>
#include<QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("client");
    socket =new QTcpSocket();
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::socket_Read_Data);
    connect(socket,&QTcpSocket::disconnected,this,&MainWindow::socket_Disconnected);
    ui->clientSend->setEnabled(false);
    ui->IP->setText("192.168.0.103");
    ui->Port->setText("8888");

    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

}

MainWindow::~MainWindow()
{
    delete this->socket;
    delete ui;
}


void MainWindow::on_clintConnect_clicked()
{
    if(ui->clintConnect->text() == "Connect"){
        QString ipadress;
        int portsorce;
        ipadress = ui->IP->text();
        portsorce = ui->Port->text().toInt();

        //取消已有的连接
        socket->abort();

        socket->connectToHost(ipadress,portsorce);

        if(!socket->waitForConnected(30000))
        {
            QMessageBox::warning(NULL, "Connection Error", "Please check the connection", QMessageBox::Yes );

            qDebug() << "Connection failed!";
            return;
        }
        QMessageBox::information(NULL, "Connection", " Connect successfully!", QMessageBox::Yes );

        qDebug() << "Connect successfully!";

        //发送按键使能
        ui->clientSend->setEnabled(true);
        ui->clintConnect->setText("disconnect");

    }else{
        socket->disconnectFromHost();
        //修改按键文字
        ui->clintConnect->setText("Connect");
        ui->clientSend->setEnabled(false);

    }


}

void MainWindow::on_clientSend_clicked()
{
    QString mes =ui->sendmes->toPlainText();
    QString ip = ui->IP->text();
    QString mes1 = ip + "_"  +  mes;
    socket->write(mes1.toUtf8(),(mes1.toUtf8().length()+1));
    socket->flush();
    QString current_date = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");

    mes = current_date + "      Client:" +  mes;
    ui->messageList->addItem(mes.toUtf8());
    ui->messageList->scrollToBottom();
    ui->sendmes->clear();
}
void MainWindow::socket_Read_Data(){
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        QString current_date = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");

        QString mes = current_date + "      Server:" +  buffer;
        ui->messageList->addItem(mes);
        ui->messageList->scrollToBottom();
    }

}

void MainWindow::socket_Disconnected(){
    ui->clientSend->setEnabled(false);
    //修改按键文字
    ui->clintConnect->setText("Connect");
    QMessageBox::information(NULL, "Connection", "Disconnected!", QMessageBox::Yes );
    qDebug() << "Disconnected!";

}

void MainWindow::on_getRecord_clicked()
{
    QString current_date = QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh时mm分ss秒");

    QFile file("./ "+ current_date +".txt");
    file.open( QIODevice::ReadWrite | QIODevice::Append);
    QTextStream out(&file);

    int row=0;
    while(row <(ui->messageList->count()))
    {
        QString line=ui->messageList->item(row)->text();

        qDebug()<<line;
        out<<line<<"\n";

        row++;
    }
        file.close();

}

void MainWindow::on_clearRecord_clicked()
{
    ui->messageList->clear();
}
