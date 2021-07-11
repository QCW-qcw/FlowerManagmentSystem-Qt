#ifndef WHETHERWINDOW_H
#define WHETHERWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WhetherWindow; }
QT_END_NAMESPACE

class WhetherWindow : public QMainWindow
{
    Q_OBJECT

public:
    WhetherWindow(QWidget *parent = nullptr);
    ~WhetherWindow();
    void gettext();
    void gethtml();
    QString getconnect();
    std::vector<std::map<QString,QString>> getwhether();
    QStringList getcity();

private slots:

    void on_pushButton_2_clicked();

private:
    Ui::WhetherWindow *ui;
};
#endif // WHETHERWINDOW_H
