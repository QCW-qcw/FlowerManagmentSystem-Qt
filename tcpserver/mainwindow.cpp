#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("server");

    ui->port->setText("8010");
    ui->serverSend->setEnabled(false);

    server = new QTcpServer();
    connect(server,&QTcpServer::newConnection,this,&MainWindow::server_New_Connect);

}

MainWindow::~MainWindow()
{

    server->close();
    server->deleteLater();
    delete ui;
}


void MainWindow::on_Listen_clicked()
{
    if(ui->Listen->text() == "Monitor"){
        int portsorce = ui->port->text().toInt();
        if(!server->listen(QHostAddress::Any, portsorce))
                {
                QMessageBox::warning(NULL, "Monitor Error", server->errorString(), QMessageBox::Yes );

                    //若出错，则输出错误信息
                    qDebug()<<server->errorString();
                    return;
                }
                QMessageBox::information(NULL, "Monitor", "Monitor succeessfully ", QMessageBox::Yes );

                //修改按键文字
              ui->Listen->setText("Cancel Monitoring");
                qDebug()<< "Listen succeessfully!";
    }
    else{
        socket->abort();
                //取消侦听
                server->close();
                //修改按键文字
                ui->Listen->setText("Monitor");
                //发送按键失能
                ui->serverSend->setEnabled(false);
            }






}

void MainWindow::on_serverSend_clicked()
{
    QString mes = ui->textEdit->toPlainText();
    mes = "Server:"+ mes;
    qDebug() << "Send: " << mes;
        //获取文本框内容并以ASCII码形式发送
       // socket->write(mes.toLatin1());
        socket->write(mes.toUtf8());
        ui->messageList->addItem(mes.toUtf8());
        ui->messageList->scrollToBottom();
        socket->flush();
        ui->textEdit->clear();

}


void MainWindow::server_New_Connect(){
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socket_Disconnected);
    ui->serverSend->setEnabled(true);
    qDebug() << "A Client connect!";

}
void MainWindow::socket_Read_Data(){
    QByteArray buffer;
       //读取缓冲区数据
       buffer = socket->readAll();
       if(!buffer.isEmpty())
       {
           QString str = ui->textEdit_2->toPlainText();
           str+=tr(buffer);
           //刷新显示
           ui->textEdit_2->setText(str);

           ui->messageList->addItem(buffer);
           ui->messageList->scrollToBottom();
       }


}

void MainWindow::socket_Disconnected(){
    ui->serverSend->setEnabled(false);
    QMessageBox::information(NULL, "Connection", "Disconnected!", QMessageBox::Yes );
       qDebug() << "Disconnected!";

}



