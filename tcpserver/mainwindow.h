#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTcpServer>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Listen_clicked();

    void on_serverSend_clicked();

    void server_New_Connect();

     void socket_Read_Data();

    void socket_Disconnected();


private:
    Ui::MainWindow *ui;
    QTcpServer* server;
    QTcpSocket* socket;

};
#endif // MAINWINDOW_H
