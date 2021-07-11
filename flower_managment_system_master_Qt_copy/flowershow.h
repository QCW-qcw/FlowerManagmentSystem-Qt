#ifndef FLOWERSHOW_H
#define FLOWERSHOW_H

#include <QWidget>
#include<QSqlDatabase>
#include<QTextEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class flowershow; }
QT_END_NAMESPACE

class flowershow : public QWidget
{
    Q_OBJECT

public:
    flowershow(QWidget *parent = nullptr);
    ~flowershow();

        void showflower(QTextEdit* TextEdit,QString flowername);
int getnum(QString flowername);
int getcost(QString flowername);
std::tuple<QString,QString,QString> getcompany(QString flowername);


std::vector<std::pair<QString,int>> getgrowth(QString flowername);

std::vector<std::pair<QString,int>> getwater(QString flowername);

std::vector<std::pair<QString,int>> getfeiliao(QString flowername);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::flowershow *ui;
        QSqlDatabase db;
};
#endif // FLOWERSHOW_H
