#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QDesktopWidget>
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
    ui->IP->setText("10.99.14.0");
    ui->Port->setText("8010");

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
    mes = "Client:" + mes;
    //  socket->write(mes.toLatin1());
    socket->write(mes.toUtf8(),(mes.toUtf8().length()+1));

    socket->flush();
    // ui->messageList->addItem(mes.toLatin1());
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
        QString str = ui->receivemes->toPlainText();
        str+=tr(buffer);
        //刷新显示
        ui->receivemes->setText(str);

        ui->messageList->addItem(buffer);
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
